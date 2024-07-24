# 2. Procesos y Programación concurrente

## 2.1. Instalación/configuración de C y python en Linux

C y Python usualmente son lenguajes que ya vienen instalados en la mayoría de las distribuciones de Linux, sin embargo, es importante verificar que estén instalados y en caso de no estarlo, instalarlos.

### 2.1.1. Instalación de C

Para instalar C en Linux, se debe instalar el compilador de C, `gcc`. Para instalar `gcc` en Ubuntu o Fedora, se debe ejecutar el siguiente comando:

```bash
sudo apt-get/dnf install gcc

# ver versión
gcc --version
```

Además, se puede instalar `make` para facilitar la compilación de programas en C. Para instalar `make` en Ubuntu, se debe ejecutar el siguiente comando:

```bash
sudo apt-get install make
```

También será necesario instalar los essentials de desarrollo en Ubuntu, los essentials de desarrollo incluyen herramientas y bibliotecas necesarias para compilar programas en C, para ello se debe ejecutar el siguiente comando:

```bash
sudo apt-get install build-essential
```

### 2.1.2. Instalación de Python

Python usualmente viene instalado en la mayoría de las distribuciones de Linux, sin embargo, se puede verificar si está instalado ejecutando el siguiente comando:

```bash
python --version
```

En caso de que no esté instalado, se puede instalar Python en Ubuntu o Fedora ejecutando el siguiente comando:

```bash
sudo apt-get/dnf install python3
```

## 2.2. Manejo de procesos en Linux

### Introducción a los procesos en Linux

### Comandos básicos para la gestión de procesos

### Creación y finalización de procesos

### Ejemplos

1. **Ver información de procesos**
2. **Crear y matar procesos**
3. **Manejo de señales en C**

## 2.3. Diagrama de transición de procesos

### Estados de los procesos

### Transiciones de estados

### Colas de procesos y planificación (scheduling)

### Ejemplos

1. **Diagrama de transición de procesos**
2. **Simulación de transiciones de estados**
3. **Planificación de procesos en C**

## 2.4. Programación concurrente en Linux

### Introducción a la programación concurrente

### Herramientas y tecnicas de concurrencia en Linux

### Problemas clásicos de concurrencia 

### Ejemplos

1. **Crear hilos en C**
2. **Sincronización con Mutex**