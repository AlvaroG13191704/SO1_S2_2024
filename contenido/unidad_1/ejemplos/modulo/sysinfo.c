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

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tu Nombre");
MODULE_DESCRIPTION("Modulo para leer informacion de memoria y CPU en JSON");
MODULE_VERSION("1.0");

#define PROC_NAME "sysinfo"
#define MAX_CMDLINE_LENGTH 256
#define CONTAINER_ID_LENGTH 64

// Función para obtener la línea de comandos de un proceso y retornar un apuntador a la cadena
static char *get_process_cmdline(struct task_struct *task) {

    /* 
        Creamos una estructura mm_struct para obtener la información de memoria
        Creamos un apuntador char para la línea de comandos
        Creamos un apuntador char para recorrer la línea de comandos
        Creamos variables para guardar las direcciones de inicio y fin de los argumentos y el entorno
        Creamos variables para recorrer la línea de comandos
    */
    struct mm_struct *mm;
    char *cmdline, *p;
    unsigned long arg_start, arg_end, env_start;
    int i, len;


    // Reservamos memoria para la línea de comandos
    cmdline = kmalloc(MAX_CMDLINE_LENGTH, GFP_KERNEL);
    if (!cmdline)
        return NULL;

    // Obtenemos la información de memoria
    mm = get_task_mm(task);
    if (!mm) {
        kfree(cmdline);
        return NULL;
    }

    /* 
       1. Primero obtenemos el bloqueo de lectura de la estructura mm_struct para una lectura segura
       2. Obtenemos las direcciones de inicio y fin de los argumentos y el entorno
       3. Liberamos el bloqueo de lectura de la estructura mm_struct
    */
    down_read(&mm->mmap_lock);
    arg_start = mm->arg_start;
    arg_end = mm->arg_end;
    env_start = mm->env_start;
    up_read(&mm->mmap_lock);

    // Obtenemos la longitud de la línea de comandos y validamos que no sea mayor a MAX_CMDLINE_LENGTH - 1
    len = arg_end - arg_start;

    if (len > MAX_CMDLINE_LENGTH - 1)
        len = MAX_CMDLINE_LENGTH - 1;

    // Obtenemos la línea de comandos de  la memoria virtual del proceso
    /* 
        Por qué de la memoria virtual del proceso?
        La memoria virtual es la memoria que un proceso puede direccionar, es decir, la memoria que un proceso puede acceder
    */
    if (access_process_vm(task, arg_start, cmdline, len, 0) != len) {
        mmput(mm);
        kfree(cmdline);
        return NULL;
    }

    // Agregamos un caracter nulo al final de la línea de comandos
    cmdline[len] = '\0';

    // Reemplazar caracteres nulos por espacios
    p = cmdline;
    for (i = 0; i < len; i++)
        if (p[i] == '\0')
            p[i] = ' ';

    // Liberamos la estructura mm_struct
    mmput(mm);
    return cmdline;
}


/* 
    Función para mostrar la información en el archivo /proc en formato JSON
*/
static int sysinfo_show(struct seq_file *m, void *v) {
    /* 
        Creamos una estructura sysinfo para obtener la información de memoria
        creamos una estructura task_struct para recorrer los procesos
        total_jiffies para obtener el tiempo total de CPU
        first_process para saber si es el primer proceso
    */
    struct sysinfo si;
    struct task_struct *task;
    unsigned long total_jiffies = jiffies;
    int first_process = 1;

    // Obtenemos la información de memoria
    si_meminfo(&si);


    seq_printf(m, "{\n");
    seq_printf(m, "\"Processes\": [\n");

    // Iteramos sobre los procesos
    for_each_process(task) {
        if (strcmp(task->comm, "containerd-shim") == 0) {
            unsigned long vsz = 0;
            unsigned long rss = 0;
            unsigned long totalram = si.totalram * 4;
            unsigned long mem_usage = 0;
            unsigned long cpu_usage = 0;
            char *cmdline = NULL;

            // Obtenemos los valores de VSZ y RSS
            if (task->mm) {
                // Obtenemos el uso de vsz haciendo un shift de PAGE_SHIFT - 10, un PAGE_SHIFT es la cantidad de bits que se necesitan para representar un byte
                vsz = task->mm->total_vm << (PAGE_SHIFT - 10);
                // Obtenemos el uso de rss haciendo un shift de PAGE_SHIFT - 10
                rss = get_mm_rss(task->mm) << (PAGE_SHIFT - 10);
                // Obtenemos el uso de memoria en porcentaje
                mem_usage = (rss * 10000) / totalram;
            }

            /* 
                Obtenemos el tiempo total de CPU de un proceso
                Obtenemos el tiempo total de CPU de todos los procesos
                Obtenemos el uso de CPU en porcentaje
                Obtenemos la línea de comandos de un proceso
            */
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
            seq_printf(m, "    \"MemoryUsage\": %lu.%02lu,\n", mem_usage / 100, mem_usage % 100);
            seq_printf(m, "    \"CPUUsage\": %lu.%02lu\n", cpu_usage / 100, cpu_usage % 100);
            seq_printf(m, "  }");


            // Liberamos la memoria de la línea de comandos
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
    printk(KERN_INFO "sysinfo_json modulo cargado\n");
    return 0;
}

/* 
    Función de limpieza del módulo
*/
static void __exit sysinfo_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "sysinfo_json modulo desinstalado\n");
}

module_init(sysinfo_init);
module_exit(sysinfo_exit);
