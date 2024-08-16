# 4. Contenedores con Docker

### 4.1.1 Definición de contenedores

Los contenedores son una forma de empaquetar, distribuir e implementar aplicaciones de software de forma rápida y eficiente. 

Un contenedor es una unidad de software que empaqueta una aplicación y todas sus dependencias, de modo que la aplicación se pueda ejecutar de forma fiable y rápida en cualquier entorno. Los contenedores aíslan el software de su entorno y garantizan que funcione de la misma manera en cualquier lugar.

Los contenedores son una solución ligera y portátil que hace que el desarrollo, la implementación y la administración de aplicaciones sean más rápidos y fáciles. Los contenedores son ideales para aplicaciones y servicios basados en microservicios, ya que permiten a los equipos de desarrollo dividir las aplicaciones en componentes más pequeños y fáciles de gestionar.

Para conocer un poco más sobre los contenedores y su historia, les recomiendo una conferencia donde se explica la historia de los contenedores y su evolución. [Conferencia](https://www.youtube.com/watch?v=cUygIN0MRUc&t=1566s)

### 4.1.2 Comparación con máquinas virtuales

Los contenedores son similares a las máquinas virtuales, pero son más ligeros y portátiles. Mientras que las máquinas virtuales emulan hardware físico, los contenedores emulan el sistema operativo del host. Esto significa que los contenedores virtualizan el sistema operativo, pero no el hardware subyacente.

![Contenedores vs VMs](./img/convsvm.webp)

En esta imagen podemos ver la diferencia entre una máquina virtual y un contenedor. 

En la máquina virtual, cada máquina virtual tiene su propio sistema operativo y su propia copia de la aplicación, todo esto a nivel de hardware. Esto nos permite tener varias sistemas operativos en un mismo hardware físico, pero con mayor consumo de recursos que quiza no se estén utilizando.

En el contenedor, estos son levantandos en un mismo sistema operativo, compartiendo el kernel del sistema operativo, lo que permite que los contenedores sean más ligeros y portátiles que las máquinas virtuales. Cada uno de los contenedores tiene su propia copia de la aplicación y sus dependencias, pero comparten el sistema operativo del host.


### 4.1.3 Beneficios de los contenedores

Con lo anterior, podemos ver que los contenedores tienen varias ventajas y beneficios sobre las máquinas virtuales y en general sobre la virtualización de sistemas. Algunos de estos beneficios son:

1. **Reduce los recursos de administración de IT**
2. **Tamaño reducido lo que permite mayor densidad**
3. **Reduce y simplifica las actualizaciones seguras**
4. **Agilidad tanto en desarollo como en producción**

## 4.2. Instalación y configuración de Docker

### 4.2.1 ¿Qué es Docker?

Docker es una plataforma de código abierto que permite a los desarrolladores empaquetar, distribuir y ejecutar aplicaciones en contenedores. Los contenedores son unidades de software que empaquetan una aplicación y todas sus dependencias, de modo que la aplicación se pueda ejecutar de forma fiable y rápida en cualquier entorno.

Docker fue lanzado en 2013 y desde entonces se ha convertido en una de las herramientas de desarrollo más populares. Docker es una solución ligera y portátil que hace que el desarrollo, la implementación y la administración de aplicaciones sean más rápidos y fáciles.

Docker no solo se encarga de la creación de contenedores, sino que viene con una serie de herramientas para el manejo de imagenes, red, volumentes, entre otros.

Tomar en cuenta que docker no es el único software que permite la creación de contenedores, pero es el más popular y el que se ha convertido en el estándar de facto en la industria. Existen otras alternativas como Podman, LXC, LXD, entre otros.

Este es el [enlace](https://www.docker.com/) de la **página oficial** de Docker.

### 4.2.2 Instalación de Docker Linux

Para instalar Docker en Linux, se recomienda seguir la documentación oficial de Docker, ya que la instalación puede variar dependiendo de la distribución de Linux que se esté utilizando.

Platform |	x86_64 / amd64
------------ | -------------
[Ubuntu](https://docs.docker.com/engine/install/ubuntu/)	 |✅
Debian	|✅
Red Hat Enterprise Linux (RHEL) |	✅
[Fedora](https://docs.docker.com/desktop/install/fedora/)	| ✅


### 4.2.3 Instalación de Docker Windows

Para instalar Docker en Windows, como tal no se instala Docker en Windows, sino que se instala Docker Desktop, que es una aplicación que permite a los desarrolladores empaquetar, distribuir y ejecutar aplicaciones en contenedores. Docker Desktop es instalar WSL 2 (Windows Subsystem for Linux) y Docker Engine.

## 4.3. Explicación del Docker Engine

### 4.3.1 Arquitectura del Docker Engine

El Docker Engine es una aplicación cliente-servidor con estos componentes:

- Un servidor que es un tipo de demonio que se ejecuta en la máquina host.
- Una API REST que especifica interfaces que los programas pueden usar para hablar con el demonio y darle instrucciones.

**¿Qué es un Deamon (demonio)?**

Un demonio es un programa que se ejecuta en segundo plano, sin interacción directa con el usuario. Los demonios se utilizan para realizar tareas de mantenimiento y administración del sistema, como la gestión de servicios, la programación de tareas y la monitorización del sistema.

En el caso de Docker, el demonio es el servidor de Docker que se ejecuta en la máquina host y se encarga de gestionar los contenedores y las imágenes de Docker.

### 4.3.2 Ciclo de vida de un contenedor

El ciclo de vida de un contenedor es administrado por un runtime de contenedores, que es un software que se encarga de ejecutar y gestionar los contenedores. Docker utiliza un runtime de contenedores llamado containerd, que es un proyecto de código abierto que proporciona una API para la gestión de contenedores.

El ciclo de vida de un contenedor consta de los siguientes pasos:

1. **Creación**: En este paso, se crea un contenedor a partir de una imagen de Docker. Una imagen de Docker es un paquete de software que contiene una aplicación y todas sus dependencias. 

2. **Inicio**: En este paso, se inicia el contenedor y se ejecuta la aplicación que contiene. 

3. **Ejecución**: En este paso, se ejecuta la aplicación que contiene el contenedor. 

4. **Detención**: En este paso, se detiene el contenedor y se detiene la aplicación que contiene.

![Arquitectura de docker engine](./img/dockerengine.png)

En la imagen de arriba podemos ver la arquitectura de Docker Engine. Se divide en varias partes las cuales explicaremos a continuación:

- **Docker Client**: Es la interfaz de línea de comandos que se utiliza para interactuar con el servidor de Docker. El cliente de Docker envía comandos al servidor de Docker a través de la API REST.
- **Docker deamon**: Es el servidor de Docker que se ejecuta en la máquina host y se encarga de gestionar los contenedores y las imágenes de Docker. El demonio de Docker escucha en un socket UNIX o en un puerto TCP para recibir comandos del cliente de Docker.
- **containerd**: Es un runtime de contenedores que se encarga de ejecutar y gestionar los contenedores. Docker utiliza containerd como su runtime de contenedores. Esta ligado a el ciclo de vida que detalla arriba.
- **shim**: Es un componente que actúa como intermediario entre containerd y el contenedor. El shim se encarga de iniciar y detener el contenedor y de redirigir la entrada y la salida estándar del contenedor.
- **runc**: Es un ejecutor de contenedores que se encarga de ejecutar el contenedor. Runc es un proyecto de código abierto que proporciona una implementación de la especificación de contenedores de la Open Container Initiative (OCI).

Hay algo que debemos tomar muy en cuenta y es que existen dos tipos de runtime de contenedores.
- Los high-level runtime, como containerd, que proporcionan una API de alto nivel para la gestión de contenedores, temas de red, volúmenes, etc.
- Los low-level runtime, como runc, que proporcionan una implementación de bajo nivel utilizando los cgroups y namespaces del kernel de Linux.
  

### 4.3.3 Imágenes y contenedores

**¿Qué es una imagen de Docker?**

Una imagen de Docker **es un paquete de software** que contiene una aplicación y todas sus dependencias. Una imagen de Docker **se utiliza para crear contenedores** de Docker, que **son instancias** en ejecución de una imagen de Docker.

Usualmente estas imagenes las podemos encontrar en el [Docker Hub](https://hub.docker.com/), que es un repositorio de imágenes de Docker que se pueden utilizar para crear contenedores de Docker.

![Imagenes y contenedores](./img/imagesdocker.png)
https://community.sap.com/t5/technology-blogs-by-sap/use-private-registry-for-containerize-a-cap-application-part-1/ba-p/13541667 

En esta imagen podemos observar dos flujos de como el registry, imagenes y contenedores de docker interactuan entre si.

En el primer flujo observamos como desde el registry se hace un pull a nuestra computadora de que imagen queremos utilizar, luego de esto se crea un contenedor con la imagen que se descargo.

En el segundo flujo observamos como se crea una imagen a partir de un Dockerfile, luego con este archivo se crea la imagen y se sube al registry para que otros usuarios puedan utilizarla. Por último, podemos descargar o hacer pull de la imagen que subimos al registry.

### 4.3.4 Comandos de Docker

Ahora vamos a ver de forma agrupada los comandos de Docker más utilizados. 

#### Comandos de Docker para la gestión de imágenes

- **Buscar una imagen en Docker Hub: `docker search`**
    ```bash
      # Busca una imagen en Docker Hub
      docker search ubuntu
    ```
- **Descargar una imagen de Docker Hub: `docker pull`**
    ```bash
      # Descarga una imagen de Docker Hub
      docker pull ubuntu
    ```
- **Listar imágenes de Docker: `docker images`**
    ```bash
      # Lista las imágenes de Docker
      docker images
    ```
- **Eliminar una imagen de Docker: `docker rmi`**
    ```bash
      # Elimina una imagen de Docker
      docker rmi ubuntu
      # -f: Fuerza la eliminación de una imagen
      docker rmi -f ubuntu
    ```

#### Comandos de Docker para la gestión de contenedores

- **Crear y Ejecutar un contenedor: `docker run`**
    ```bash
      # -d: Corre el contenedor en segundo plano
      # --name: Asigna un nombre al contenedor
      # ubuntu: Imagen de Docker que se va a utilizar
      docker run -d --name mi_contenedor ubuntu
    ```
- **Listar contenedores en ejecución: `docker ps`**
    ```bash
      # lista los contenedores en ejecución
      docker ps 
      # -a: Muestra todos los contenedores, incluyendo los que no están en ejecución
      docker ps -a
      # -eq: Muestra los últimos contenedores que se han ejecutado
      docker ps -eq
    ```
- **Inspeccionar un contenedor `docker inspect`**
    ```bash
      # Inspecciona un contenedor
      docker inspect mi_contenedor
    ```
- **Detener un contenedor: `docker stop`**
    ```bash
      # Detiene un contenedor
      docker stop mi_contenedor
    ```
- **Iniciar un contenedor: `docker start`**
    ```bash
      # Inicia un contenedor
      docker start mi_contenedor
    ```
- **Eliminar un contenedor: `docker rm`**
    ```bash
      # Elimina un contenedor
      docker rm mi_contenedor
      # -f: Fuerza la eliminación de un contenedor en ejecución
      docker rm -f mi_contenedor
    ```
- **Logs de un contenedor: `docker logs`**
    ```bash
      # Muestra los logs de un contenedor
      docker logs mi_contenedor
    ```
- **Ejecutar un comando en un contenedor: `docker exec`**
    ```bash
      # Ejecuta un comando en un contenedor
      docker exec mi_contenedor ls -la
    ```
- **Entrar a un contenedor: `docker exec -it`**
    ```bash
      # -it: Permite interactuar con el contenedor
      docker exec -it mi_contenedor bash
    ```

Acá pueden ver la hoja de referencia de los comandos de Docker que les dejo para que la tengan a la mano. 
- [Hoja de referencia](https://docs.docker.com/get-started/docker_cheatsheet.pdf)
- [Hoja de referencia 2](https://dockerlabs.collabnix.com/docker/cheatsheet/)

## 4.4. Dockerfile y Multistages

### 4.4.1 ¿Qué es un Dockerfile?

Un Dockerfile es un archivo de texto que contiene una serie de instrucciones que se utilizan para construir una imagen de Docker. Un Dockerfile se utiliza para automatizar el proceso de creación de imágenes de Docker y para definir cómo se debe construir una imagen de Docker.

Usualmente los Dockerfile se utilizan para definir configuraciones específicas de una aplicación, como las dependencias, las variables de entorno, los comandos de inicio, etc. 

Un Dockerfile se compone de una serie de instrucciones que se ejecutan en orden para construir una imagen de Docker. Algunas de las instrucciones más comunes de un Dockerfile son:

- **FROM**: Especifica la imagen base que se va a utilizar para construir la imagen de Docker.
- **RUN**: Ejecuta un comando en la imagen de Docker.
- **COPY**: Copia archivos desde el sistema de archivos del host a la imagen de Docker.
- **CMD**: Especifica el comando que se va a ejecutar cuando se inicie un contenedor a partir de la imagen de Docker.
- **EXPOSE**: Expone un puerto en el contenedor.
- **ENV**: Define una variable de entorno en el contenedor.

### 4.4.2 Sintaxis y estructura de un Dockerfile

Un Dockerfile se compone de una serie de instrucciones que se ejecutan en orden para construir una imagen de Docker. Cada instrucción de un Dockerfile se compone de una palabra clave y uno o más argumentos.

Ahora analizaremos un Dockerfile para la ejecución de una aplicación en Python, en este caso usando Flask.

```Dockerfile
# Usar una imagen base de Python
FROM python:3.9-slim

# Establecer el directorio de trabajo dentro del contenedor
WORKDIR /app

# Copiar el archivo de requisitos (dependencies)
COPY requirements.txt .

# Instalar las dependencias necesarias
RUN pip install --no-cache-dir -r requirements.txt

# Copiar el código de la aplicación en el contenedor
COPY . .

# Exponer el puerto en el que la aplicación va a correr
EXPOSE 5000

# Comando para ejecutar la aplicación
CMD ["python", "app.py"]

```

Ahora vamos a analizar otro Dockerfile que se encarga de construir una imagen de Docker para una aplicación en Node.js.

```Dockerfile
# Usar una imagen base de Node.js
FROM node:18-alpine

# Establecer el directorio de trabajo dentro del contenedor
WORKDIR /usr/src/app

# Copiar package.json y package-lock.json
COPY package*.json ./

# Instalar las dependencias
RUN npm install --production

# Copiar todo el código de la aplicación
COPY . .

# Compilar la aplicación para producción
RUN npm run build

# Exponer el puerto de la aplicación
EXPOSE 8080

# Comando para ejecutar la aplicación
CMD ["node", "dist/server.js"]
```
### 4.4.3 Multistage Builds

Los multistage builds son una característica de Docker que permite construir imágenes de Docker en varias etapas. Los multistage builds se utilizan para reducir el tamaño de las imágenes de Docker y para mejorar el rendimiento de la construcción de imágenes.

Ahora vamos analizar dos ejemplos de Dockerfile con multistage builds.

**El primer ejemplo** es un Dockerfile que se encarga de construir una imagen de Docker de un compilado de una aplicación en Go.

```Dockerfile
# Etapa de compilación
FROM golang:1.22rc1-bullseye AS build 

# Establecer el directorio de trabajo dentro del contenedor
WORKDIR /app

# Copiar el código de la aplicación en el contenedor
COPY go.mod go.sum ./

# Descargar las dependencias
RUN go mod download

# Copiar el código de la aplicación en el contenedor
COPY . .

# Compilar la aplicación
RUN go build \
  -ldflags="-linkmode external -extldflags -static" \
  -tags netgo \
  -o server-payment

# Etapa de producción
FROM scratch

# Copiar el binario de la aplicación de la etapa de compilación
COPY --from=build /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/
COPY --from=build /app/server-payment server-payment

# Comando para ejecutar la aplicación
CMD ["/server-payment"]
```

**El segundo ejemplo** es un Dockerfile que se encarga de construir una imagen de Docker para construir una aplicación web en React con un backend en Node.js. La primera etapa compila el frontend y la segunda prepara el backend con el frontend embebido.

```Dockerfile
# Etapa 1: Compilar el Frontend
FROM node:18-alpine as build

# Establecer el directorio de trabajo
WORKDIR /app

# Instalar dependencias y compilar el frontend
COPY frontend/package*.json ./
RUN npm install
COPY frontend/ ./
RUN npm run build

# Etapa 2: Preparar el Backend con el Frontend
FROM node:18-alpine

# Establecer el directorio de trabajo
WORKDIR /app

# Instalar dependencias del backend
COPY backend/package*.json ./
RUN npm install

# Copiar el backend
COPY backend/ ./

# Copiar el build del frontend desde la etapa 1
COPY --from=build /app/build ./public

# Exponer el puerto de la aplicación
EXPOSE 5000

# Comando para ejecutar el servidor backend
CMD ["node", "server.js"]

```

## 4.5. Network y volumenes de contenedores

El networking de los contenedores se refiere a la habilidad de conectar y comunicar otros contenedores o trabajos no relacionados a estos. 

### 4.5.1 Redes en Docker

Los contenedores tienen la red habilitada de forma predeterminada y pueden realizar conexiones salientes. Un contenedor no tiene información sobre a qué tipo de red está conectado. Un contenedor solo ve una interfaz de red con una dirección IP, una puerta de enlace, una tabla de enrutamiento, servicios DNS y otros detalles de red.

Dentro de Docker se manejan varios tipos de redes, como la red bridge, la red host, la red overlay, la red macvlan, la red none, entre otras. Vamos a ver a detallar las más comunes y las que se utilizan con mayor frecuencia.

- **Red bridge**: Es la red predeterminada de Docker. Los contenedores conectados a la red bridge pueden comunicarse entre sí y con el host. Los contenedores en la red bridge tienen una dirección IP privada y pueden exponer puertos a la red host.
- **Red host**: Los contenedores conectados a la red host comparten la interfaz de red del host. Los contenedores en la red host pueden comunicarse con el host y con otros contenedores en la red host. Los contenedores en la red host no tienen una dirección IP privada y no pueden exponer puertos a la red host.
- **Red overlay**: La red overlay es una red de superposición que se utiliza para conectar contenedores en diferentes hosts. Los contenedores en la red overlay pueden comunicarse entre sí y con otros contenedores en la red overlay.
- **Red macvlan**: La red macvlan es una red de nivel 2 que se utiliza para conectar contenedores a la red física del host. 
- **Red none**: La red none es una red aislada que se utiliza para conectar contenedores que no necesitan conectividad de red.

Docker proporciona una serie de comandos para administrar las redes de contenedores. Algunos de los comandos más comunes son:

- **docker network ls**: Lista las redes de Docker.
```bash
  # Lista las redes de Docker
  docker network ls
```
- **Comando para crear nueva red**: Crea una nueva red
```bash
  # Crea una nueva red
  docker network create -d <driver> <network_name>
  # Ejemplo
  docker network create -d bridge my_network
```

En el siguiente ejemplo vamos a correr un contenedor de redis y vamos ahcer un bind de un puerto del contenedor al puerto del host.

```bash
  # Correr un contenedor de redis
  docker run -d --name redis example/redis --bind 127.0.0.1
  # Correr un contenedor de redis-cli y conectarse al contenedor de redis
  docker run --rm -it --network container:redis example/redis-cli -h 127.0.0.1
```

Por defecto cuando se crea o corre un contenedor usando el `docker create` or `docker run`, el contenedor se conecta a la red bridge. Pero estos no exponen los puertos al mundo exterior. Para hacer esto posible se usan las banderas `--publish` o `-p` para hacer los puertos accesibles fuera del bridge. Esto crea una regla de firewall en el host, redirigiendo el tráfico del puerto del host al puerto del contenedor.

| Bandera | Descripción|
|---------|------------|
| `-p 8080:80` | Publica el puerto 80 del contenedor en el puerto 8080 del host |
| `-p 192.168.1.100:8080:80` | Publica el puerto 80 del contenedor en el puerto 8080 del host en la dirección IP

Por último, para comunicar contenedores entre si, basta y sobra que esten en la misma red que usualmente es la red bridge. 

```bash
  # Crear una red
  docker network create my_network
  # Correr un contenedor de nginx en la red my_network
  docker run -d --name nginx --network my_network nginx
  # Correr un contenedor de alpine en la red my_network
  docker run -it --network my_network alpine
```

### 4.5.2 Volúmenes en Docker

Los volúmenes son el mecanismo preferido para persistir datos generados por y usados por contenedores. Si bien los volúmenes son independientes de la vida del contenedor, los datos que se almacenan en un volumen persisten incluso después de que el contenedor se detiene o se elimina.

La ventajas de usar volúmenes son:
- Los volúmenes son faciles de respaldar y restaurar.
- Se pueden administrar con la CLI de docker
- Los volumenes funcionan tanto para Linux como Windows
- Los volumenes pueden ser compartidos entre contenedores

Los volúmenes se pueden no aumentan el tamaño de la imagen de Docker, ya que los volúmenes se almacenan fuera del sistema de archivos de la imagen de Docker. Los volúmenes se pueden montar en cualquier directorio del sistema de archivos del contenedor.

![Volumenes en Docker](./img/types-of-mounts-volume.webp)

**Comandos para crear y manejar volúmenes**

- **docker volume ls**: Lista los volúmenes de Docker.
```bash
  # Lista los volúmenes de Docker
  docker volume ls
```
- **docker volume create**: Crea un nuevo volumen de Docker.
```bash
  # Crea un nuevo volumen de Docker
  docker volume create my_volume
```

- **docker volume inspect**: Inspecciona un volumen de Docker.
```bash
  # Inspecciona un volumen de Docker
  docker volume inspect my_volume
```

- **docker volume rm**: Elimina un volumen de Docker.
```bash
  # Elimina un volumen de Docker
  docker volume rm my_volume
```

Ahora vamos a iniciar un contenedor con un volumen

```bash
  # Correr un contenedor con un volumen
docker run -d \
  --name devtest \
  -v myvol2:/app \
  nginx:latest
```

## 4.6. Docker Compose

### 4.6.1 ¿Qué es Docker Compose?

Docker Compose es una herramienta que se utiliza para definir y ejecutar aplicaciones de varios contenedores de Docker. Docker Compose utiliza un archivo YAML para definir la configuración de la aplicación y los servicios que se van a ejecutar en los contenedores de Docker.

Compose trabaja en todos los entornos: producción, staging, desarrollo, pruebas, así como en máquinas locales.

Por defecto Docker Compose no viene instalado con Docker, por lo que se debe instalar por separado. Para instalar Docker Compose, se recomienda seguir la documentación oficial de Docker Compose.

**Comandos esenciales para el manejo de la CLI**

- **docker-compose up**: Crea y arranca los contenedores de la aplicación.
```bash
  # Crea y arranca los contenedores de la aplicación
  docker compose up
```

- **docker-compose down**: Detiene y elimina los contenedores de la aplicación.
```bash
  # Detiene y elimina los contenedores de la aplicación
  docker compose down
```

- **docker-compose ps**: Lista los contenedores de la aplicación.
```bash
  # Lista los contenedores de la aplicación
  docker compose ps
```

- **docker-compose logs**: Muestra los logs de los contenedores de la aplicación.
```bash
  # Muestra los logs de los contenedores de la aplicación
  docker compose logs
```

### 4.6.2 Sintaxis y estructura de un archivo docker-compose.yml

La sintaxis de un archivo docker-compose.yml es muy similar a la de un Dockerfile. Un archivo docker-compose.yml se compone de una serie de servicios que se van a ejecutar en los contenedores de Docker. Cada servicio se compone de una serie de opciones y configuraciones que se utilizan para definir cómo se va a ejecutar el servicio en el contenedor de Docker. 

Dentro de un archivo docker-compose.yml se pueden definir varias opciones y configuraciones, como el nombre del servicio, la imagen de Docker que se va a utilizar, los puertos que se van a exponer, las variables de entorno, los volúmenes, etc.

Ahora vamos a analizar un archivo docker-compose.yml que se encarga de definir la configuración de una aplicación de varios contenedores de Docker.

```yaml
version: '3.8'

services:
  # MongoDB Service
  mongodb:
    image: mongo:latest
    container_name: mongodb_container
    ports:
      - "27017:27017"
    volumes:
      - mongo-data:/data/db
    environment:
      MONGO_INITDB_ROOT_USERNAME: root
      MONGO_INITDB_ROOT_PASSWORD: example

  # Node.js Web Application Service
  webapp:
    image: node:14
    container_name: webapp_container
    working_dir: /app
    volumes:
      - .:/app
    ports:
      - "3000:3000"
    command: sh -c "npm install && npm start"
    depends_on:
      - mongodb
    environment:
      MONGO_URL: mongodb://root:example@mongodb:27017/mydatabase

# Volumes
volumes:
  mongo-data:
```

Comencemoz a analizar el archivo docker-compose.yml.

- **version**: Especifica la versión de la sintaxis de Docker Compose que se va a utilizar. La versión más reciente de Docker Compose es la 3.8.
- **services**: Especifica los servicios que se van a ejecutar en los contenedores de Docker. Cada servicio se compone de una serie de opciones y configuraciones que se utilizan para definir cómo se va a ejecutar el servicio en el contenedor de Docker.

  ```yaml
  services:
    # MongoDB Service
    mongodb:
      image: mongo:latest
      container_name: mongodb_container
      ports:
        - "27017:27017"
      volumes:
        - mongo-data:/data/db
      environment:
        MONGO_INITDB_ROOT_USERNAME: root
        MONGO_INITDB_ROOT_PASSWORD: example
  ```
  Aquí se define un servicio de MongoDB que se va a ejecutar en un contenedor de Docker. El servicio de MongoDB se compone de las siguientes opciones y configuraciones:
  - **image**: Especifica la imagen de Docker que se va a utilizar para el servicio de MongoDB.
  - **container_name**: Especifica el nombre del contenedor de Docker que se va a crear para el servicio de MongoDB.
  - **ports**: Especifica los puertos que se van a exponer en el contenedor de Docker.
  - **volumes**: Especifica los volúmenes que se van a montar en el contenedor de Docker.
  - **environment**: Especifica las variables de entorno que se van a definir en el contenedor de Docker.

  ```yaml
    # Node.js Web Application Service
    webapp:
      image: node:14
      container_name: webapp_container
      working_dir: /app
      volumes:
        - .:/app
      ports:
        - "3000:3000"
      command: sh -c "npm install && npm start"
      depends_on:
        - mongodb
      environment:
        MONGO_URL: mongodb://root:example@mongodb:27017/mydatabase
  ```
  Aquí se define un servicio de una aplicación web en Node.js que se va a ejecutar en un contenedor de Docker. El servicio de la aplicación web en Node.js se compone de las siguientes opciones y configuraciones:
  - **image**: Especifica la imagen de Docker que se va a utilizar para el servicio de la aplicación web en Node.js.
  - **container_name**: Especifica el nombre del contenedor de Docker que se va a crear para el servicio de la aplicación web en Node.js.
  - **working_dir**: Especifica el directorio de trabajo en el contenedor de Docker.
  - **volumes**: Especifica los volúmenes que se van a montar en el contenedor de Docker. El punto (.) se refiere al directorio actual y los :/app se refiere al directorio /app en el contenedor.
  -  **ports**: Especifica los puertos que se van a exponer en el contenedor de Docker.
  -  **command**: Especifica el comando que se va a ejecutar cuando se inicie el contenedor de Docker.
  -  **depends_on**: Especifica los servicios en los que depende el servicio de la aplicación web en Node.js.
  -  **environment**: Especifica las variables de entorno que se van a definir en el contenedor de Docker.
  
- **volumes**: Especifica los volúmenes que se van a utilizar en los contenedores de Docker. Los volúmenes se definen en una sección de volúmenes y se pueden montar en los contenedores de Docker.
  
    ```yaml
    # Volumes
    volumes:
      mongo-data:
    ```
    Aquí se define un volumen de Docker llamado mongo-data que se va a utilizar en los contenedores de Docker.


### Ejemplo

Por útlimo, vamos a realizar un ejemplo, vamos a construir un servicio con FastAPI y un volumen que guarde los datos recibidos por el servicio en formato JSON.

Todo el código de este ejemplo lo pueden encontrar en la carpeta de ejemplos de la unidad 1

Para iniciar, vamos a crear un entorno virtual y vamos a instalar las dependencias necesarias para el servicio.

```bash
  # Crear un entorno virtual
  python3 -m venv venv
  # Activar el entorno virtual
  source venv/bin/activate
  # Instalar las dependencias
  pip install "fastapi[standard]"
```

Ahora vamos a crear el Dockerfile para el servicio de FastAPI.

