# 2. Creación de Scripts en Bash

## 1.2.1. Introducción a Bash

Bash es el acrónimo de "Bourne Again SHell". Es el shell por defecto en muchas distribuciones de Unix y Linux, y es un lenguaje de comandos que permite a los usuarios interactuar con el sistema operativo para ejecutar comandos, realizar tareas de administración y automatizar procesos.

## 1.2.2. Estructura básica de un script

Un script de Bash es simplemente un archivo de texto que contiene una serie de comandos que se ejecutan secuencialmente. La estructura básica incluye:

- **Shebang**: Indica al sistema qué intérprete usar. Ejemplo: `#!/bin/bash`
- **Comentarios**: Empiezan con `#` y no son ejecutados. Ejemplo: `# Este es un comentario`
- **Comandos**: Cualquier comando de Bash. Ejemplo: `echo "Hola, mundo"`

```bash
#!/bin/bash
# Este es un script básico de Bash
echo "Hola, mundo"
```

## 1.2.3. Variables y control de flujo
En Bash, puedes definir variables y usar estructuras de control de flujo como bucles y condicionales.

- **Variables**: Las variables en Bash se definen simplemente asignando un valor a un nombre. Para acceder al valor de una variable, se utiliza el símbolo `$` seguido del nombre de la variable.

```bash
#!/bin/bash
# Definir una variable
nombre="Mundo"
echo "Hola, $nombre"
```

- **Condicionales**: Las estructuras condicionales en Bash permiten ejecutar comandos basados en ciertas condiciones. La estructura básica de un condicional `if` es la siguiente:

```bash
#!/bin/bash
# Condicional if-else
if [ "$nombre" = "Mundo" ]; then
  echo "Hola, Mundo"
else
  echo "Hola, desconocido"
fi
```

- **Bucles**: Los bucles permiten ejecutar repetidamente un bloque de código. Los bucles for y while son comúnmente usados en Bash.

 **Bucle For**

```bash
#!/bin/bash
# Bucle for
for i in {1..5}; do
  echo "Iteración $i"
done
```

 **Bucle While**

```bash
#!/bin/bash
# Bucle while
contador=1
while [ $contador -le 5 ]; do
  echo "Iteración $contador"
  contador=$((contador + 1))
done
```

## 1.2.4. Scripts para administración del sistema
Los scripts de Bash son muy útiles para tareas de administración del sistema, como la gestión de usuarios, la automatización de backups y la supervisión del sistema.

**Ejemplo de script para crear un backup**
Este script crea un archivo comprimido que contiene los archivos de un directorio específico.

```bash
#!/bin/bash
# Script para crear un backup de un directorio

# Directorio de origen
origen="/home/usuario/documentos"
# Directorio de destino
destino="/home/usuario/backup"

# Crear el backup
tar -czvf "$destino/backup_$(date +%Y%m%d).tar.gz" "$origen"
echo "Backup completado"
```

**Ejemplo de script para supervisar el uso de disco**
Este script comprueba el uso del disco y envía una advertencia si el uso supera un umbral especificado (80% en este caso).

```bash
#!/bin/bash
# Script para supervisar el uso del disco

# Obtener el uso del disco
uso_disco=$(df -h / | grep / | awk '{ print $5 }' | sed 's/%//g')

# Comprobar si el uso del disco supera el 80%
if [ "$uso_disco" -gt 80 ]; then
  echo "Advertencia: El uso del disco es del ${uso_disco}%"
fi
```

**Ejemplo de Script para gestionar usuarios**
Este script añade un nuevo usuario al sistema, asignándole un directorio home y un shell predeterminado.

```bash
#!/bin/bash
# Script para añadir un nuevo usuario

# Nombre del usuario
nuevo_usuario="nuevo_usuario"
# Contraseña del usuario
contraseña="contraseña123"
# Directorio home
home_dir="/home/$nuevo_usuario"
# Shell predeterminado
shell="/bin/bash"

# Crear el usuario con el directorio home y el shell predeterminado
useradd -m -d "$home_dir" -s "$shell" "$nuevo_usuario"
# Establecer la contraseña del usuario
echo "$nuevo_usuario:$contraseña" | chpasswd

echo "Usuario $nuevo_usuario creado con éxito"
```

**Ejemplo de Script para monitorear el uso de memoria**
Este script monitorea el uso de memoria y envía una advertencia si el uso de memoria libre es inferior a un umbral especificado (20% en este caso).

```bash
#!/bin/bash
# Script para monitorear el uso de memoria

# Obtener el porcentaje de memoria libre
mem_libre=$(free | grep Mem | awk '{print $4/$2 * 100.0}')

# Comprobar si la memoria libre es inferior al 20%
if (( $(echo "$mem_libre < 20" | bc -l) )); then
  echo "Advertencia: Memoria libre baja (${mem_libre}%)"
fi
```





