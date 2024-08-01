# 3. Módulos de Kernel


## 3.1 ¿Qué son los módulos del kernel?

El kernel como ya vimos es el puente entre el hardware y el resto de funciones del sistema operativo, maneja el sistema de ficheros, el acceso a red y otras tareas de bajo nivel que son fundamentales.

El kernel está formado por un fichero principal que redice en `/boot` y que se carga en memoria al arrancar el sistema. Sin embargo, el kernel no puede tener todos los drivers y funciones necesarias para todos los dispositivos que existen, por lo que se pueden añadir módulos al kernel para añadir funcionalidades.


### 3.1.1 Definición y proposito

Los modulos de kernel son archivos que contienen código objeto que pueden extender las funcionalidades del kernel.

Estos modulos residen en `/lib/modules` y se pueden cargar y descargar en tiempo de ejecución.

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
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

```

## 3.3 Comandos para administración de módulos de Kernel

### 3.3.1 Carga de módulos

### 3.3.2 Eliminar módulos

### 3.3.3 Listar módulos

## 3.4 Introducción a System Calls

### 3.4.1 Definición y propósito

### 3.4.2 Proceso de creación

## 3.5 Process Control Block (PCB)


### Recursos

