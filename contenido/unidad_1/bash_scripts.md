# 2. Creación de Scripts en Bash

## 1.2.1. Introducción a Bash

####  Historia y evolución de Bash

Bash fue creado por Brian Fox en 1989 como una alternativa al shell Bourne original (sh). Bash es una mejora significativa sobre el shell Bourne, con características adicionales como la expansión de comandos, la historia de comandos y la finalización de comandos. Bash se ha convertido en el shell por defecto en muchas distribuciones de Unix y Linux, y es ampliamente utilizado por los administradores de sistemas y desarrolladores.

#### ¿Qué es Bash?

Bash es el acrónimo de "Bourne Again SHell". Es el shell por defecto en muchas distribuciones de Unix y Linux, y es un lenguaje de comandos que permite a los usuarios interactuar con el sistema operativo para ejecutar comandos, realizar tareas de administración y automatizar procesos.

En términos básicos la Bash es un intérprete de línea de comandos que generalmente se ejecuta en una ventana donde se puede ingresar texto donde interpreta lo que el usuario ingresa al momento de realizar alguna acción. La combinación de estos comandos termina siendo un Script que de igual manera puede ser ejecutado en una Shell Script. 

#### ¿Qué es Shell?

La shell es un intérprete de comandos que permite a los usuarios interactuar con el sistema operativo. La shell toma los comandos ingresados por el usuario y los ejecuta, permitiendo al usuario realizar tareas como navegar por el sistema de archivos, ejecutar programas y automatizar tareas. La Shell es como el intermediario entre lo interior y exterior.

#### Diferencias entre Bash y otros shells (sh, zsh, ksh)

- **Bash vs. sh**: Bash es una mejora del shell Bourne original (sh) y es compatible con la mayoría de los scripts de shell Bourne. Bash incluye características adicionales como la expansión de comandos, la historia de comandos y la finalización de comandos.
- **Bash vs. zsh**: Zsh es otro shell popular que incluye características avanzadas como la finalización de comandos más inteligente, la expansión de comandos más avanzada y una sintaxis más flexible. Zsh es más personalizable y tiene una curva de aprendizaje más pronunciada que Bash.
- **Bash vs. ksh**: Ksh (Korn shell) es otro shell popular que es compatible con la mayoría de los scripts de shell Bourne. Ksh incluye características avanzadas como la finalización de comandos y la expansión de comandos más avanzada. Ksh es más rápido y más eficiente que Bash en algunos casos.


## 1.2.2. Estructura básica de un script

### Comandos

Los comandos en Bash son instrucciones que se ejecutan en la línea de comandos o en un script. Los comandos pueden ser comandos internos del shell, comandos externos del sistema operativo o scripts de shell.

##### Comandos de navegación en el sistema de archivos

```bash
pwd                       # Imprime el directorio actual
ls                        # Lista los archivos y directorios en el directorio actual
ls -a|--all               # Lista los archivos y directorios, incluyendo los ocultos
ls -l                     # Lista los archivos y directorios en formato largo
ls -l -h|--human-readable # Lista los archivos y directorios en formato largo y legible
ls -t                     # Lista los archivos y directorios ordenados por fecha de modificación
stat foo.txt              # Lista el tamaño, la fecha de creación y la fecha de modificación de un archivo
stat foo                  # Lista el tamaño, la fecha de creación y la fecha de modificación de un directorio
tree                      # Lista el árbol de directorios y archivos
cd foo                    # Ir al directorio foo
cd                        # Ir al directorio raíz
cd -                      # Ir al directorio anterior
```

[Referencia a más comandos](https://github.com/RehanSaeed/Bash-Cheat-Sheet)

#### Scripts

Un script de Bash es simplemente un archivo de texto que contiene una serie de comandos que se ejecutan secuencialmente. La estructura básica incluye:

- **Shebang**: Indica al sistema qué intérprete usar. Ejemplo: `#!/bin/bash`. Podemos usar otros intérpretes como `#!/bin/sh`, `#!/bin/zsh`, etc.
- **Comentarios**: Empiezan con `#` y no son ejecutados. Ejemplo: `# Este es un comentario`
- **Comandos**: Cualquier comando de Bash. Ejemplo: `echo "Hola, mundo"`

```bash
#!/bin/bash
# Este es un script básico de Bash
echo "Hola, mundo"
```

### Ejecución de un script

Para ejecutar un script de Bash, se debe dar permisos de ejecución al archivo y luego ejecutarlo con el comando `./nombre_script.sh`.
 
```bash
chmod +x nombre_script.sh  # Dar permisos de ejecución al script
./nombre_script.sh         # Ejecutar el script
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
  while [ $contador -le 5 ]; do # Mientras contador sea menor o igual a 5
    echo "Iteración $contador"
    contador=$((contador + 1)) # Incrementar el contador0
  done
  ```

#### Super usuario vs Usuario

El superusuario es el usuario con permisos de administrador en un sistema Unix o Linux. El superusuario tiene acceso a todos los archivos y recursos del sistema y puede realizar tareas de administración como instalar software, configurar el sistema y modificar archivos de configuración. El superusuario se identifica por el nombre de usuario `root` y tiene permisos especiales que le permiten realizar tareas que otros usuarios no pueden hacer.

Si deseamos ejecutar un comando como superusuario, podemos usar el comando `sudo` seguido del comando que queremos ejecutar. Por ejemplo, para ejecutar el comando `apt-get update` como superusuario, podemos usar `sudo apt-get update`.

O si queremos ejecutar un script como superusuario, podemos usar `sudo ./nombre_script.sh`.

Siempre que no se tenga los permisos se nos solicitará la contraseña de superusuario para poder ejecutar el comando o bien mostrar un error de permisos.

**Ejemplo de un Script para capturar teclas y escribir en un archivo cada 5 segundos**
Este script captura las teclas presionadas por el usuario y las escribe en un archivo cada 5 segundos.

```bash
#!/bin/bash

# Script para capturar las teclas y escribir en un archivo cada 5 segundos

# Creamos el archivo donde vamos a guardar las teclas
archivo="teclas.log"

# Limpiamos el archivo
> $archivo

# Mosgtramos un mensaje

echo "Presiona las teclas que quieres capturar. Presiona Ctrl+C para salir"

# Creamos un bucle infinito 
while true; do

    # capturar la entrada
    read -n 1 -s tecla # -n 1 captura solo un caracter, -s no muestra la tecla, tecla es la variable donde se guarda la tecla

    # escribimos y guardamos 
    # El comando >> conocido como redirección de salida, se utiliza para redirigir la salida de un comando a un archivo
    # Existen dos tipos de redirección de salida: >> y >
    # >> se utiliza para redirigir la salida de un comando a un archivo, pero si el archivo ya existe, el comando añadirá la salida al final del archivo
    # > se utiliza para redirigir la salida de un comando a un archivo, pero si el archivo ya existe, el comando sobrescribirá el archivo
    
    echo -n "$tecla" >> $archivo # -n no añade un salto de línea al final 

done
```

**Ejemplo de un script que utiliza los comandos más importantes de Bash**
En este ejemplo vamos a procesar un archivo de texto y extraer la información específica.

Vamos a procesa un archivo de tipo log para extraer las líneas que contienen errores y contar cuántos errores de cada tipo hay. Luego guardar los resultados en un archivo de salida.

Vamos a crear un archivo de texto llamado `sistema.log` con el siguiente contenido:

```bash
INFO: El sistema ha iniciado.
ERROR: Falla en el módulo de red.
INFO: Conexión establecida.
ERROR: Tiempo de espera agotado.
INFO: Operación completada.
ERROR: Falla en el módulo de red.
WARNING: Uso de memoria alto.
ERROR: Disco lleno.
INFO: Backup completado.
ERROR: Falla en el módulo de red.
```

El script para procesar el archivo `sistema.log` y extraer los errores es el siguiente:

```bash
#!/bin/bash

# Script para supervisar el uso de disco y mostrar advertencia

# Archivo de entrada
archivo_entrada="sistema.log"

# Archivo de salida
archivo_salida="reporte.txt"


# Procesar el archivo de entrada y guardar los resultados en el archivo de salida

# Explicación de comandos a utilizar
# grep <patron> <archivo> : Busca un patron en un archivo
# | : Pipe, redirige la salida de un comando a la entrada de otro
# cut -d <delimitador> -f <campo> : Extrae un campo de un archivo delimitado
# sort : Ordena las lineas de un archivo
# uniq -c : Cuenta las lineas repetidas de un archivo
# > : Redirige la salida de un comando a un archivo

grep "ERROR" $archivo_entrada | cut -d':' -f 2 - | sort | uniq -c > $archivo_salida

echo "Reporte generado en $archivo_salida"
```



## 1.2.4. Scripts para administración del sistema
Los scripts de Bash son muy útiles para tareas de administración del sistema, como la gestión de usuarios, la automatización de backups y la supervisión del sistema.


**Ejemplo de script para crear un backup**
Este script crea un archivo comprimido que contiene los archivos de un directorio específico.

```bash
#!/bin/bash
# Un script para crea un archivo comprimido que contiene los archivos de un directorio espeficio

# origen (este directorio)
origen="."
# destino un archivo comprimido afuera de este
destino="../"

# checamos si el destino existe, sino lo creamos

if [ ! -d "$destino" ]; then # -d es un flag para verificar si un directorio existe
    mkdir "$destino"
fi

# checamos si tenemos permisos pñara escribir en el destino

if [ ! -w "$destino" ]; then # -w es un flag para verificar si tenemos permisos de escritura
    echo "No tienes permisos para escribir en $destino"
    exit 1
fi

# creamos el backup
# tar -> es un comando para crear archivos comprimidos
# -czvf -> c: crea un archivo, z: comprime, v: verbose, f: nombre del archivo
# "$destino/backup_$(date +%Y%m%d).tar.gz" -> nombre del archivo
# "$origen" -> directorio a comprimir
tar -czvf "$destino/backup_$(date +%Y%m%d).tar.gz" "$origen"

echo "Backup creado en $destino/backup_$(date +%Y%m%d).tar.gz"


## Agregar notas de ERROR
```

**Ejemplo de script para supervisar el uso de disco**
Este script comprueba el uso del disco y envía una advertencia si el uso supera un umbral especificado (80% en este caso).

```bash
#!/bin/bash

# Script para supervisar el uso de disco y mostrar advertencia

# Obtener el uso del disco

# Comandos a utilizar
# $() : Ejecuta un comando y guarda su salida
# df -h  / : Muestra el uso de disco de la partición raíz
# | : Pipe, redirige la salida de un comando a la entrada de otro
# grep / : Filtra las lineas que contienen la partición raíz
# awk '{print $5}' : Imprime la quinta columna de un archivo
# sed 's/%//g' : Elimina los caracteres '%' de un archivo

uso_disco=$(df -h / | grep / | awk '{print $5}' | sed 's/%//g')

echo "Uso de disco: $uso_disco%"

# Comprobar si el uso de disco supera el 80%

if [ "$uso_disco" -gt 80 ]; then # Si el uso de disco supera el 80%
    echo "Advertencia: El uso de disco supera el 80%"
else
    echo "Uso de disco normal"
fi
```

**Ejemplo de Script para gestionar usuarios**
Este script añade un nuevo usuario al sistema, asignándole un directorio home y un shell predeterminado.

Con el nuevo usuario se puede asignar una contraseña, crear un directorio home y establecer un shell predeterminado. La utilidad de hacer esto es para poder tener un control de los usuarios que se crean en el sistema y que de manera encapsulada se pueda tener un control de los permisos y accesos que se le otorgan a cada usuario.

```bash
#!/bin/bash

# Script para añadir un nuevo usuario

# nombre de usuario
nombre_usuario="usuario2"

# contraseña
contrasena="123"

# Directorio home
home_dir="/home/$nombre_usuario"

# shell predeterminado
shell="/bin/bash"


# Crear el usuario con el directorio home y el shell predeterminado
# Comandos a utilizar
# useradd -m -d <directorio_home> -s <shell> <nombre_usuario> : Crea un usuario con un directorio home y un shell
useradd -m -d $home_dir -s $shell $nombre_usuario

# Establecer la contraseña del usuario
echo "$nombre_usuario:$contrasena" | chpasswd

echo "Usuario creado: $nombre_usuario"

# Comprobar si el usuario se ha creado correctamente
if [ $? -eq 0 ]; then # $? contiene el código de salida del último comando ejecutado 
    echo "Usuario creado correctamente"
else
    echo "Error al crear el usuario"
fi

# abrir la bash con el usuario creado
su - $nombre_usuario
```

Si deseamos borrar el usuario hay que ejecutar este comando

```bash
sudo userdel -r <nombre_usuario>
```



**Ejemplo de Script para monitorear el uso de memoria**
Este script monitorea el uso de memoria y envía una advertencia si el uso de memoria libre es inferior a un umbral especificado (20% en este caso).

```bash
#!/bin/bash

# Script para monitorear el uso de memoria y enviar una advertencia

# Obtener el uso de memoria
# Comandos a utilizar
# free -m : Muestra el uso de memoria en MB
# grep Mem : Filtra las lineas que contienen la palabra Mem
# awk '{print $4/$2 * 100.0}' : Imprime la tercera columna de un archivo

mem_libre=$(free  | grep Mem | awk '{print $4/$2 * 100.0}')

# Comprobar si la memoria libre es inferior al 20%
# (( )) : Evalua una expresión aritmética
# |  : Pipe, redirige la salida de un comando a la entrada de otro
# bc -l : Calculadora de precisión arbitraria
if (( $(echo "$mem_libre < 20" | bc -l) )); then 
    echo "Advertencia: La memoria libre es de $mem_libre%"
else
    echo "Memoria libre normal"
fi
```





