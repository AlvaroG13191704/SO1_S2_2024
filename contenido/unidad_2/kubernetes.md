# Kubernetes: Conceptos, Comandos y Ejemplos

Kubernetes es un sistema de orquestación de contenedores que automatiza el despliegue, la gestión y la escalabilidad de aplicaciones en contenedores. A continuación se presenta una descripción general de Kubernetes, junto con algunos comandos y ejemplos útiles.

---

## 1. Conceptos Principales

### Cluster
Un **cluster** es un conjunto de máquinas (nodos) que ejecutan aplicaciones en contenedores, coordinados por un nodo maestro (Control Plane).

### Node
Cada **node** es una máquina (física o virtual) que forma parte del clúster y ejecuta los **Pods**.

### Pod
El **Pod** es la unidad mínima de trabajo en Kubernetes. Puede contener uno o más contenedores y comparte recursos como almacenamiento y red.

### Deployment
Un **Deployment** es una definición que especifica cómo deben ejecutarse los Pods, gestionando réplicas, actualizaciones y fallos.

### Service
Un **Service** proporciona una dirección IP estable y un puerto para acceder a los Pods, incluso si cambian de IP.

### Namespace
Un **Namespace** permite segmentar lógicamente los recursos dentro del clúster para aislamiento y organización.

### ConfigMap y Secret
- **ConfigMap**: Almacena configuraciones no sensibles.
- **Secret**: Almacena datos sensibles (como contraseñas) de forma segura.

---

## 2. Comandos Kubernetes con `kubectl`

### Comandos del Clúster

- **Ver el estado del clúster**:  
  ```bash
  kubectl cluster-info
   ```

  - **Listar nodos en el clúster**:  
  ```bash
  kubectl get nodes
    ```

## Comandos de Pods

  - **Listar todos los pods**:  
  ```bash
  kubectl get pods
   ```

  - **Describir un pod específico**:  
  ```bash
  kubectl describe pod <nombre-del-pod>
   ```

  - **Eliminar un pod**:  
  ```bash
  kubectl delete pod <nombre-del-pod>
   ```

## Comandos de Deployments

  - **Crear un Deployment**:  
  ```bash
  kubectl create deployment <nombre-del-deployment> --image=<imagen>
   ```

  - **Ejemplo**:  
  ```bash
  kubectl create deployment nginx-deployment --image=nginx
   ```

  - **Escalar un Deployment**:  
  ```bash
  kubectl scale deployment <nombre-del-deployment> --replicas=<número>
   ```

  - **Actualizar un Deployment**:  
  ```bash
  kubectl set image deployment/<nombre-del-deployment> <contenedor>=<nueva-imagen>
   ```

   ## Comandos de Services

  - **Exponer un Deployment como un servicio**:  
  ```bash
  kubectl expose deployment <nombre-del-deployment> --type=LoadBalancer --port=<puerto>
   ```

  - **Ver todos los servicios**:  
  ```bash
   kubectl get services
   ```

  ## Namespaces

  - **Crear un Namespace**:  
  ```bash
  kubectl create namespace <nombre-namespace>
   ```

- **Cambiar el Namespace**:  
```bash
kubectl config set-context --current --namespace=<nombre-namespace>
   ```

  ## 3. Ejemplos Prácticos

  - **a) Crear un Deployment con NGINX**:  
  ```bash
  kubectl config set-context --current --namespace=<nombre-namespace>
```

  - **a) Esto crea un deployment con la imagen oficial de NGINX. Para verificarlo**:  
  ```bash
  kubectl get deployments
  kubectl get pods
```

  - **b) Escalar un Deployment**: 
  ```bash
  kubectl scale deployment nginx --replicas=3
```

- **Escala el deployment nginx a 3       réplicas. Verifica las réplicas:**: 
  
```bash
kubectl get pods
```

  - **Exponer el Deployment como un Servicio**: 
  Esto expone el servicio en el puerto 80 y lo hace accesible desde el exterior del clúster.
  ```bash
kubectl expose deployment nginx --type=LoadBalancer --port=80
```

  - **d) Actualizar el Deployment**: 
  Actualiza la imagen de nginx a la versión 1.20.0.

   ```bash
kubectl set image deployment/nginx nginx=nginx:1.20.0
```

 - **e) Aplicar un Archivo YAML**: 
 Puedes usar un archivo YAML para crear recursos en Kubernetes. Por ejemplo, un deployment:

  ```bash
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: my-nginx
  spec:
    replicas: 2
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
```

  Para aplicar este archivo:

```bash
kubectl apply -f deployment.yaml
```

## 4. Estrategias de Despliegue

 - **Rolling Update**: 
 La estrategia predeterminada de Kubernetes. Los pods se actualizan de manera gradual, asegurando que la aplicación esté siempre disponible durante la actualización.

  - **Recreate**: 
  Elimina todos los pods antiguos antes de crear los nuevos. Esto puede causar tiempos de inactividad, pero garantiza que no haya conflictos entre versiones.

  - **Ejemplo de configuración en YAML**
  ```bash
   strategy:
     type: RollingUpdate
     rollingUpdate:
       maxUnavailable: 1
       maxSurge: 1
  ```











