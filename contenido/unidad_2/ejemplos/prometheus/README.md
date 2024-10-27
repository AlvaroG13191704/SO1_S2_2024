# Prometheus + Grafana con Helm

**Vamos a crear un Cluster en GKE el cual tenga nuestros servicios monitorizados utilizando Prometheus con Grafana para la visualización de las métricas. Para la el control de los DP's estaremos utilizando Helm.**

**Instalar HELM**
```bash
sudo dnf install helm #fedora
# ubuntu
curl https://baltocdn.com/helm/signing.asc | gpg --dearmor | sudo tee /usr/share/keyrings/helm.gpg > /dev/null
sudo apt-get install apt-transport-https --yes
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/helm.gpg] https://baltocdn.com/helm/stable/debian/ all main" | sudo tee /etc/apt/sources.list.d/helm-stable-debian.list
sudo apt-get update
sudo apt-get install helm
```

## Si estamos utilizando GKE entonces debemos correr este comando para brindar permisos

```bash
ACCOUNT=$(gcloud info --format='value(config.account)')
kubectl create clusterrolebinding owner-cluster-admin-binding \
    --clusterrole cluster-admin \
    --user $ACCOUNT
```

### Utilizando los charts de Helm

**Vamos a estar utilizando este [Prometheus Cart](https://artifacthub.io/packages/helm/prometheus-community/kube-prometheus-stack) el cual lo que hace es instalar diferentes charts y entr ellos Grafana.**

**Para instalar la configuración del chart usamos esto**

```bash
helm repo add prometheus-community https://prometheus-community.github.io/helm-charts
helm repo update
```

**Luego para instalar todo lo necesario dentro de nuestro Cluster, usamos estos comandos:**

```bash
helm install my-kube-prometheus-stack prometheus-community/kube-prometheus-stack
```

**Ahora vamos a ver todo lo que se instalo:**

```bash
kubectl get all
```

Aquí tienes la traducción al español:

El chart de Helm creó los siguientes recursos:

- **Pods**: Alojan la aplicación de Kubernetes Prometheus implementada dentro del clúster.
- **Replica Sets**: Una colección de instancias de la misma aplicación dentro del clúster de Kubernetes. Mejora la confiabilidad de la aplicación.
- **Deployments**: Es el plano para crear los pods de la aplicación.
- **Services**: Expone los pods que se ejecutan dentro del clúster de Kubernetes. Se usa para acceder a la aplicación de Kubernetes implementada.
- **Stateful Sets**: Administran el despliegue de los componentes de la aplicación con estado y aseguran identidades de red estables y predecibles para estos componentes.
- **Daemon Sets**: Aseguran que todos (o un conjunto específico de) los nodos ejecuten una copia de un pod, lo cual es útil para tareas como registro, monitoreo y otras operaciones específicas de los nodos.

**Si imprimimos los servicios, podemos ver varios pero lo que nos importa son:** 

Por el momento solo están accesibles para el cluster, debemos exponerlos utilizando un LoadBalancer o NodeIP.

| Name                                   | Type      | Cluster-IP     | External-IP | PORT(S) | AGE   |
|----------------------------------------|-----------|----------------|-------------|---------|-------|
| service/my-kube-prometheus-stack-grafana | ClusterIP | 34.118.232.182 | <none>      | 80/TCP  | 8m43s |
|service/my-kube-prometheus-stack-grafana  |ClusterIP  | 34.118.232.182 |  <none>     |80/TCP         |8m43s


**Para poder exponer estos servicios lo haremos de la siguiente manera:**

```bash
kubectl expose service my-kube-prometheus-stack-prometheus --type=NodePort --target-port=9090 --name=prometheus-node-port-service

kubectl expose service my-kube-prometheus-stack-grafana --type=NodePort --target-port=3000 --name=grafana-node-port-service
```


Para obtener la IP external de cluster utilizando este comando y escogemos la IP que tenga como nombre nap-tuv como relación.

**Ojo que los puertos al no especificar con el la bandera `-port` la salida, estos se generan automaticamente y los pueden ver usando el `kubectl get services`**

```bash
# prometheus
http://35.238.12.150:32654

# grafana
http://35.238.12.150:30264
```

**Para obtener la contraseña de grafana es con el siguiente comando**

```bash
kubectl get secret --namespace default my-kube-prometheus-stack-grafana -o jsonpath="{.data.admin-password}" | base64 --decode ; echo
```

### Importar dashbaord

Utilizando los [dashboards de la comunidad](https://grafana.com/grafana/dashboards/) se pueden importar.


