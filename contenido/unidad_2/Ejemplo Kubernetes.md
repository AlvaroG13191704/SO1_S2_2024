## EJEMPLO PRACTICO EN KUBERNETES

## 1. Crear el archivo YAML del Deployment y el Service

- **Primero, crea un archivo llamado `nginx-deployment.yaml` con el siguiente contenido:**

```bash
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.19.2
        ports:
        - containerPort: 80

---

apiVersion: v1
kind: Service
metadata:
  name: nginx-service
spec:
  selector:
    app: nginx
  ports:
    - protocol: TCP
      port: 80
      targetPort: 80
  type: LoadBalancer
```

### Descripción del archivo YAML:
 - **1. Deployment:**

    - **Crea 3 réplicas de la aplicación `nginx.`**
    - **Utiliza la imagen de `nginx:1.19.2.`**
    - **Cada pod expone el puerto 80 para servir contenido HTTP.**

- **2.Service:**

    - **Define un servicio de tipo `LoadBalancer.`**
    - **Expondrá el puerto `80` al exterior y lo redirige al puerto `80` de los Pods.**


## 2. Aplicar el archivo YAML en Kubernetes

Una vez que tengas el archivo listo, sigue estos pasos:

- a) Abre tu terminal y asegúrate de estar conectado a tu clúster de Kubernetes.
- b) Aplica el archivo YAML usando el comando `kubectl`:
```bash
kubectl apply -f nginx-deployment.yaml
```
Esto creará el Deployment y el Service en tu clúster de Kubernetes.


## 3. Verificar la implementación

Para verificar que el Deployment y el Service se crearon correctamente, usa los siguientes comandos:

- Ver los pods creados:
```bash
kubectl get pods
```
Debes ver tres Pods ejecutándose con el prefijo nginx-deployment.

- Ver el estado del servicio:
```bash
kubectl get services
```
Esto mostrará el servicio nginx-service con una dirección IP externa (si tu clúster soporta LoadBalancer, como en GKE o EKS).

## 4. Acceder a la aplicación

Si estás usando un clúster en la nube que soporta `LoadBalancer,` una vez que el servicio tenga asignada una IP externa, podrás acceder a la aplicación ingresando esa dirección IP en tu navegador.

Si usas `Minikube` o un clúster local, puedes exponer el servicio en tu máquina local con el siguiente comando:

```bash
minikube service nginx-service
```
Este comando abrirá la aplicación nginx en tu navegador predeterminado.

## 5. Escalar el Deployment (opcional)
Puedes escalar el número de réplicas del Deployment para manejar más tráfico con el siguiente comando:
```bash
kubectl scale deployment nginx-deployment --replicas=5
```
Esto aumentará el número de réplicas de 3 a 5.


## UTILIZANDO ESTRATEGIAS DE DESPLIEGUE.

### RollingUpdate (la estrategia por defecto)
```bash
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  strategy:
    type: RollingUpdate  # Estrategia de despliegue (RollingUpdate o Recreate)
    rollingUpdate:
      maxUnavailable: 1  # Máximo número de Pods que pueden estar inactivos durante la actualización
      maxSurge: 1        # Máximo número de Pods que pueden estar activos por encima del número de réplicas durante la actualización
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.19.2
        ports:
        - containerPort: 80

---

apiVersion: v1
kind: Service
metadata:
  name: nginx-service
spec:
  selector:
    app: nginx
  ports:
    - protocol: TCP
      port: 80
      targetPort: 80
  type: LoadBalancer

```

### Descripción de las Estrategias de Despliegue

1. RollingUpdate (Actualización Continua).

    La estrategia RollingUpdate es la predeterminada en Kubernetes. Permite actualizar los Pods de manera gradual sin interrumpir el servicio. Esto asegura que haya siempre una parte de los Pods ejecutándose mientras los nuevos se despliegan.

    - maxUnavailable: Especifica cuántos Pods pueden estar inactivos mientras se realiza la actualización. En este caso, el valor es 1, lo que significa que durante la actualización, un Pod como máximo estará inactivo.

    - maxSurge: Define cuántos Pods adicionales pueden ser creados temporalmente durante la actualización. En este ejemplo, 1 Pod adicional puede ser creado por encima del número deseado de réplicas.

    Ventajas:

    - No hay tiempo de inactividad durante el despliegue.
    - La actualización es gradual, minimizando riesgos.

2. Recreate (Recreación Completa)

    En esta estrategia, Kubernetes elimina todos los Pods antiguos antes de crear los nuevos. Esto puede provocar un tiempo de inactividad, pero es útil cuando la versión nueva de la aplicación no es compatible con la anterior o cuando el cambio afecta recursos compartidos, como bases de datos.

    Para aplicar esta estrategia, puedes modificar el archivo YAML de la siguiente manera:

```bash
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  strategy:
    type: Recreate  # Estrategia de recreación completa
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.19.2
        ports:
        - containerPort: 80

```

Ventajas:

- Se asegura que no haya conflictos entre la versión antigua y la nueva.
- Ideal para casos donde se necesitan cambios drásticos.

Proceso de Implementación
 1. Aplicar el archivo YAML:
 ```bash
 kubectl apply -f nginx-deployment.yaml
 ```

 2. Verificar el estado del Deployment:
 ```bash
 kubectl get deployments
 kubectl describe deployment nginx-deployment
 ```

 3. Monitorear la actualización de los Pods:
 ```bash
kubectl get pods -w
  ```

### Elección de la Estrategia
- **Usa RollingUpdate si necesitas garantizar la disponibilidad continua durante las actualizaciones.**
- **Usa Recreate cuando la aplicación requiere una actualización "todo o nada" debido a incompatibilidades entre versiones.**



