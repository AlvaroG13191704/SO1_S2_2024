# 3. Módulos de Kernel


## 3.1 ¿Qué son los módulos del kernel?

El kernel como ya vimos es el puente entre el hardware y el resto de funciones del sistema operativo, maneja el sistema de ficheros, el acceso a red y otras tareas de bajo nivel que son fundamentales.

El kernel está formado por un fichero principal que redice en `/boot` y que se carga en memoria al arrancar el sistema. Sin embargo, el kernel no puede tener todos los drivers y funciones necesarias para todos los dispositivos que existen, por lo que se pueden añadir módulos al kernel para añadir funcionalidades.


### 3.1.1 Definición y propósito

Los módulo de kernel son archivos que contienen código objeto que pueden extender las funcionalidades del kernel.

Estos módulo residen en `/lib/modules` y se pueden cargar y descargar en tiempo de ejecución.

Son generalmente utilizados para brindar soporte a nuevos dispositivos de hardware o nuevos sistemas de ficheros, así como para agregar llamadas al sistema.

Cuando la funcionalidad provista por un módulo del núcleo deja de ser requerida, normalmente éste puede ser descargado, liberando su memoria.

Un **ejemplo típico** de módulo cargable son los Controladores de Dispositivo (drivers).

Los módulos de kernel son una forma de extender el kernel sin tener que recompilarlo. Esto permite que el kernel sea más pequeño y que se puedan añadir funcionalidades en tiempo de ejecución.

El paquete kmod es el encargado de gestionar los módulos del kernel en sistemas. La mayoria de los sistemas estilo Unix y Microsoft Windows soportan módulos cargables del núcleo.

### 3.1.2 Tipos de módulos

Ya vimos que los módulos residen en `/lib/modules`. Estos se encuentran organizados en directorios que indican el tipo de dispositivo o el propósito del módulo.

Por ejemplo, podemos separar los módulos en dos grupos:

1. Módulos de hardware: Estos módulos son controladores de dispositivos que permiten al kernel interactuar con el hardware. Por ejemplo:
   1. `kernel/drivers` contiene los controladores de dispositivos.
   2. `kernel/net` contiene los controladores de red.
   3. `kernel/sound` contiene los controladores de sonido.

2. Módulos de software: Estos módulos añaden funcionalidades al kernel. Por ejemplo:
   1. `kernel/fs` contiene los sistemas de ficheros.
   2. `kernel/crypto` contiene los controladores de cifrado.
   3. `kernel/lib` contiene librerías que pueden ser utilizadas por otros módulos.

### Ejemplos

Vamos a listar los módulos de kernel en un sistema Linux. Para ello, podemos utilizar el comando `lsmod` que nos muestra los módulos cargados en el sistema.

```bash
lsmod
```

Obtener información sobre un módulo específico:

```bash
modinfo <nombre_modulo>
```

Vamos a ver tambíen que se encuentra en la carpeta `/lib/modules` de un sistema Linux.

```bash
ls /lib/modules/$(uname -r)
```

### Carpeta `/proc`

La carpeta `/proc` es un sistema de ficheros virtual que contiene información sobre el sistema. En esta carpeta se pueden encontrar información sobre los procesos, la memoria, los dispositivos y otros aspectos del sistema.

Cuando trabajemos con nuestros módulos de kernel, es posible que necesitemos crear archivos en la carpeta `/proc` para mostrar o leer información sobre el sistema facilmente.

## 3.2 Creación de módulos en Linux

### 3.2.1 Estructura básica de un módulo de kernel

Un módulo de kernel es un archivo fuente que contiene funciones que se pueden cargar y descargar en tiempo de ejecución. Estos archivos fuente tienen la extensión `.c` y se compilan en archivos objeto con la extensión `.o`.

Las funciones de inicialización y limpieza de un módulo de kernel son `init_module` y `cleanup_module` respectivamente.


### 3.2.2 Compilación de módulos

Para la compilación de módulos de kernel se utiliza el comando `make` que compila el archivo fuente y genera el archivo objeto.

Make es una herramienta que se utiliza para automatizar la compilación de programas. Se basa en un archivo llamado `Makefile` que contiene las reglas de compilación.

Sino tienes instalado el paquete `make` puedes instalarlo con el siguiente comando:

```bash
sudo apt-get install make
```

#### Ejemplos

Vamos a crear un módulo de kernel sencillo para imprimir "Hola, mundo!" en la consola.

```c
#include <linux/init.h> // Este archivo contiene las macros __init y __exit
/*  
    Que son los macro?
    Los macros son una forma de definir constantes en C.
    En este caso, __init y __exit son macros que se utilizan para indicarle al kernel que funciones 
    se deben llamar al cargar y descargar el modulo.

*/
#include <linux/module.h> // Este archivo contiene las funciones necesarias para la creacion de un modulo
#include <linux/kernel.h> // Este archivo contiene las funciones necesarias para la impresion de mensajes en el kernel

/*  
    El modulo debe tener una licencia, una descripcion y un autor.
*/
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple Hello, World Module");
MODULE_AUTHOR("SGG");

static int __init hello_init(void) {
    printk(KERN_INFO "Hello, World!\n");
    return 0;

}

static void  __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, World!\n");
}

/* 
    Se debe indicarle al kernel que funciones se deben llamar al cargar y descargar el modulo.
*/
module_init(hello_init);
module_exit(hello_exit);
```

Su respectivo Makefile sería 
```Makefile
obj-m += basic.o # obj-m es una variable que contiene el nombre del modulo a compilar

all: # all es una regla que se ejecuta por defecto si no se especifica una regla
# Se compila el modulo
# Paso a paso:
# 1. Se ejecuta el comando make en el directorio /lib/modules/$(shell uname -r)/build
# 2. Se ejecuta el comando make en el directorio actual (PWD) con la regla modules
# 3. Se compila el modulo basic.c

	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 

clean: # clean es una regla que se ejecuta para limpiar los archivos generados por la compilacion
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

Para compilar ese archivo se hace lo siguiente:

```bash
make # se compila y genera los archivos para instalar
sudo insmod <file>.ko # instalar el modulo en kernel
sudo dmesg | tail -n 20 # para ver los logs del kernel

sudo rmmod <name> # desinstalar modulo
```

Ahora vamos a hacer un ejemplo intermedio, con el objetivo de cargar un módulo en kernel 
el cual cree un archivo en /proc/<name> que imprima las metricas del sistema operativo.

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h> // trae las funciones para crear archivos en /proc
#include <linux/seq_file.h> // trae las funciones para escribir en archivos en /proc
#include <linux/mm.h> // trae las funciones para manejar la memoria
#include <linux/sched.h> // trae las funciones para manejar los procesos
#include <linux/timer.h> // trae las funciones para manejar los timers
#include <linux/jiffies.h> // trae las funciones para manejar los jiffies, que son los ticks del sistema


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tu Nombre");
MODULE_DESCRIPTION("Modulo para leer informacion de memoria y CPU");
MODULE_VERSION("1.0");

#define PROC_NAME "sysinfo" // nombre del archivo en /proc

/* 
    Esta función se encarga de obtener la información de la memoria
    - si_meminfo: recibe un puntero a una estructura sysinfo, la cual se llena con la información de la memoria
*/
static int sysinfo_show(struct seq_file *m, void *v) {
    struct sysinfo si; // estructura que contiene la informacion de la memoria

    si_meminfo(&si); // obtiene la informacion de la memoria

    /*  
        El seq_printf se encarga de escribir en el archivo en /proc
        - m: es el archivo en /pro
    */

    seq_printf(m, "Total RAM: %lu KB\n", si.totalram * 4);
    seq_printf(m, "Free RAM: %lu KB\n", si.freeram * 4);
    seq_printf(m, "Shared RAM: %lu KB\n", si.sharedram * 4);
    seq_printf(m, "Buffer RAM: %lu KB\n", si.bufferram * 4);
    seq_printf(m, "Total Swap: %lu KB\n", si.totalswap * 4);
    seq_printf(m, "Free Swap: %lu KB\n", si.freeswap * 4);

    seq_printf(m, "Number of processes: %d\n", num_online_cpus());

    return 0;
};

/* 
    Esta función se ejecuta cuando se abre el archivo en /proc
    - single_open: se encarga de abrir el archivo y ejecutar la función sysinfo_show
*/
static int sysinfo_open(struct inode *inode, struct file *file) {
    return single_open(file, sysinfo_show, NULL);
}

/* 
    Esta estructura contiene las operaciones a realizar cuando se accede al archivo en /proc
    - proc_open: se ejecuta cuando se abre el archivo
    - proc_read: se ejecuta cuando se lee el archivo
*/

static const struct proc_ops sysinfo_ops = {
    .proc_open = sysinfo_open,
    .proc_read = seq_read,
};


/* 
    Esta macro se encarga de hacer dos cosas:
    1. Ejecutar la función proc_create, la cual recibe el nombre del archivo a guardar en /proc, permisos,
        y la estructura con las operaciones a realizar

    2. Imprimir un mensaje en el log del kernel
*/
static int __init sysinfo_init(void) {
    proc_create(PROC_NAME, 0, NULL, &sysinfo_ops);
    printk(KERN_INFO "sysinfo module loaded\n");
    return 0;
}

/* 
    Esta macro se encarga de hacer dos cosas:
    1. Ejecutar la función remove_proc_entry, la cual recibe el nombre del archivo a eliminar de /proc
*/
static void __exit sysinfo_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "sysinfo module unloaded\n");
}

module_init(sysinfo_init);
module_exit(sysinfo_exit);
```

Su respectivo Makefile sería 
```Makefile
obj-m += sysinfo.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

Para compilar ese archivo se hace lo siguiente:

```bash
make # se compila y genera los archivos para instalar
sudo insmod <file>.ko # instalar el modulo en kernel
sudo dmesg | tail -n 20 # para ver los logs del kernel

cat /proc/sysinfo # imprime lo escrito en el archivo 

sudo rmmod <name> # desinstalar modulo
```

## 3.3 Introducción a System Calls

### 3.3.1 Definición y propósito

Las llamadas al sistema (system calls) son una interfaz entre el software de usuario y el kernel. Permiten a los programas de usuario acceder a las funciones del kernel.

Las llamadas al sistema son utilizadas para realizar tareas como la creación de procesos, la lectura y escritura de archivos, la gestión de memoria y la comunicación entre procesos.

Las llamadas al sistema son una forma de comunicación entre el software de usuario y el kernel. Cuando un programa de usuario necesita realizar una tarea que requiere privilegios de kernel, utiliza una llamada al sistema para solicitar al kernel que realice la tarea en su nombre.

Para ver la lista de llamadas al sistema en un sistema Linux, podemos utilizar el comando `man syscalls`.

### Ejemplo

Vamos hacer un programa sencillo en C para imprimir el id del proceso actual.

```c
#include <unistd.h>
#include <sys/syscall.h> // contiene las llamadas al sistema
#include <stdio.h>

int main() {
    long id = syscall(SYS_gettid); // obtiene el id del proceso actual
    printf("Thread ID: %ld\n", id);
    return 0;
}
```

## 3.4 Process Control Block (PCB)

### 3.4.1 Definición y propósito

Este tema no lo pudimos ver en el tema anterior, pero es importante mencionarlo.

El PCB (Process Control Block) es una estructura de datos que contiene información sobre un proceso en un sistema operativo. El PCB se utiliza para almacenar información sobre el estado del proceso, la prioridad del proceso, los recursos asignados al proceso y otros datos relacionados con el proceso.

El PCB se crea cuando se crea un proceso y se destruye cuando se termina el proceso. El PCB se almacena en la memoria del sistema operativo y se utiliza para gestionar el proceso.

El PCB contiene información como:

- El identificador del proceso.
- El estado del proceso (en ejecución, listo, bloqueado).
- La prioridad del proceso.
- Los registros del procesador.
- La información de la memoria.
- Los recursos asignados al proceso.
- Otros datos relacionados con el proceso.

Como ejemplo vamos analizar la estructura `task_struct` que es la estructura que representa un proceso en el kernel de Linux.

En el siguiente link pueden encontrar todos los atributos de la estructura [task_struct](https://docs.huihoo.com/doxygen/linux/kernel/3.7/structtask__struct.html)

