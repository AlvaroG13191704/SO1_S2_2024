#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h> 
#include <linux/init.h>
#include <linux/proc_fs.h> 
#include <linux/seq_file.h> 
#include <linux/mm.h> 
#include <linux/sched.h> 
#include <linux/timer.h> 
#include <linux/jiffies.h> 
#include <linux/uaccess.h>
#include <linux/tty.h>
#include <linux/sched/signal.h>
#include <linux/fs.h>        
#include <linux/slab.h>      
#include <linux/sched/mm.h>
#include <linux/binfmts.h>
#include <linux/timekeeping.h>
#include <linux/timekeeping.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tu Nombre");
MODULE_DESCRIPTION("Modulo para leer informacion de memoria y CPU en JSON");
MODULE_VERSION("1.0");

#define PROC_NAME "sysinfo"
#define MAX_CMDLINE_LENGTH 256
#define CONTAINER_ID_LENGTH 64

// Función para obtener la línea de comandos de un proceso
static char *get_process_cmdline(struct task_struct *task) {
    struct mm_struct *mm;
    char *cmdline, *p;
    unsigned long arg_start, arg_end, env_start;
    int i, len;

    cmdline = kmalloc(MAX_CMDLINE_LENGTH, GFP_KERNEL);
    if (!cmdline)
        return NULL;

    mm = get_task_mm(task);
    if (!mm) {
        kfree(cmdline);
        return NULL;
    }

    down_read(&mm->mmap_lock);
    arg_start = mm->arg_start;
    arg_end = mm->arg_end;
    env_start = mm->env_start;
    up_read(&mm->mmap_lock);

    len = arg_end - arg_start;

    if (len > MAX_CMDLINE_LENGTH - 1)
        len = MAX_CMDLINE_LENGTH - 1;

    if (access_process_vm(task, arg_start, cmdline, len, 0) != len) {
        mmput(mm);
        kfree(cmdline);
        return NULL;
    }

    cmdline[len] = '\0';

    // Reemplazar caracteres nulos por espacios
    p = cmdline;
    for (i = 0; i < len; i++)
        if (p[i] == '\0')
            p[i] = ' ';

    mmput(mm);
    return cmdline;
}


/* 
    Función para mostrar la información en el archivo /proc en formato JSON
*/
static int sysinfo_show(struct seq_file *m, void *v) {
    struct sysinfo si;
    struct task_struct *task;
    unsigned long total_jiffies = jiffies;
    int first_process = 1;

    si_meminfo(&si);

    // Convert from KB to MB
    unsigned long totalram_mb = (si.totalram * 4) / 1024;
    unsigned long freeram_mb = (si.freeram * 4) / 1024;
    unsigned long usedram_mb = totalram_mb - freeram_mb;


    seq_printf(m, "{\n");
    seq_printf(m, "\"TotalRAM\": %lu,\n", totalram_mb);
    seq_printf(m, "\"FreeRAM\": %lu,\n", freeram_mb);
    seq_printf(m, "\"UsedRAM\": %lu,\n", usedram_mb);
    seq_printf(m, "\"Processes\": [\n");

    for_each_process(task) {
        if (strcmp(task->comm, "containerd-shim") == 0) {
            unsigned long vsz = 0;
            unsigned long rss = 0;
            unsigned long totalram = si.totalram * 4;
            unsigned long mem_usage = 0;
            unsigned long cpu_usage = 0;
            char *cmdline = NULL;

            if (task->mm) {
                vsz = task->mm->total_vm << (PAGE_SHIFT - 10);
                rss = get_mm_rss(task->mm) << (PAGE_SHIFT - 10);
                mem_usage = (rss * 10000) / totalram;
            }

            unsigned long total_time = task->utime + task->stime;
            cpu_usage = (total_time * 10000) / total_jiffies;
            cmdline = get_process_cmdline(task);

            if (!first_process) {
                seq_printf(m, ",\n");
            } else {
                first_process = 0;
            }

            seq_printf(m, "  {\n");
            seq_printf(m, "    \"PID\": %d,\n", task->pid);
            seq_printf(m, "    \"Name\": \"%s\",\n", task->comm);
            seq_printf(m, "    \"Cmdline\": \"%s\",\n", cmdline ? cmdline : "N/A");
            seq_printf(m, "    \"VSZ\": %lu,\n", vsz);
            seq_printf(m, "    \"RSS\": %lu,\n", rss);
            seq_printf(m, "    \"MemoryUsage\": %lu.%02lu,\n", mem_usage / 100, mem_usage % 100);
            seq_printf(m, "    \"CPUUsage\": %lu.%02lu\n", cpu_usage / 100, cpu_usage % 100);
            seq_printf(m, "  }");

            if (cmdline) {
                kfree(cmdline);
            }
        }
    }

    seq_printf(m, "\n]\n}\n");
    return 0;
}

/* 
    Función que se ejecuta al abrir el archivo /proc
*/
static int sysinfo_open(struct inode *inode, struct file *file) {
    return single_open(file, sysinfo_show, NULL);
}

/* 
    Estructura que contiene las operaciones del archivo /proc
*/
static const struct proc_ops sysinfo_ops = {
    .proc_open = sysinfo_open,
    .proc_read = seq_read,
};

/* 
    Función de inicialización del módulo
*/
static int __init sysinfo_init(void) {
    proc_create(PROC_NAME, 0, NULL, &sysinfo_ops);
    printk(KERN_INFO "sysinfo_json module loaded\n");
    return 0;
}

/* 
    Función de limpieza del módulo
*/
static void __exit sysinfo_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "sysinfo_json module unloaded\n");
}

module_init(sysinfo_init);
module_exit(sysinfo_exit);
