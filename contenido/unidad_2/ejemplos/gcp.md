# Configurando sdk de gcp para levantar un Cluster de Kubernetes


### Primer paso instalar gcloud

```bash
curl -O https://dl.google.com/dl/cloudsdk/channels/rapid/downloads/google-cloud-cli-linux-x86_64.tar.gz

tar -xf google-cloud-cli-linux-x86_64.tar.gz

./google-cloud-sdk/install.sh

gcloud init # para configurar su sdk con su cuenta de google

```

### Segundo crear las instrucciones de firewall para acceder a los nodos del cluster

Nos vamos a [Reglas de firewall](https://console.cloud.google.com/net-security/firewall-manager/firewall-policies/) y creamos una nueva regla llamadas `allin` y `allout` permitiendo todos los puertos y conexiones. **Después deshabilitar esta regla para evitar vulnerabilidades**

### Tercero instalar kubectl de gcp

```bash
# instalar
gcloud components install kubectl
# verificar instalación
kubectl version --client

# instalar plugin de auth 
gcloud components install gke-gcloud-auth-plugin

# configurar con el cluster
gcloud container clusters get-credentials sopes1 \
    --region=us-central1-a
```

### Crear cluster

**Primera forma**
```bash
gcloud container clusters create sopes1 --num-nodes=1 --tags=allin,allout --machine-type=n1-standard-2 --no-enable-network-policy
```

**Segunda forma**
```bash
gcloud container clusters create sopes1 --num-nodes=1 --tags=allin,allout --machine-type=n1-standard-1 --no-enable-network-policy --disk-size=100GB --disk-type pd-standard
```

### Significado de cada flag
- `gcloud container cluster create sopes1`: Comando para crear un clúster llamado sopes1.
- `--num-nodes=1`: Número de nodos en el clúster.
- `--tags=allin,allout`: Etiquetas de red para el clúster.
- `--machine-type=n1-standard-2` / `--machine-type=n1-standard-1`: Tipo de máquina para los nodos del clúster.
- `--no-enable-network-policy`: Deshabilita las políticas de red.
- `--disk-size=100GB`: Tamaño del disco (solo en la segunda forma).
- `--disk-type=pd-standard`: Tipo de disco persistente estándar (solo en la segunda forma).


### Verificamos que podemos acceder al cluster viendo los namespaces

```bash
kubectl get namespaces
```
## Comandos esenciales

**Aplicar todos o un archivo**
```bash
    kubectl apply -f .
    kubectl apply -f namespace.yaml
```

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

**Crear ingress para poder enviar peticiones**
```bash
kubectl create ns nginx-ingress
helm repo add ingress-nginx https://kubernetes.github.io/ingress-nginx 
helm repo update 
helm install nginx-ingress ingress-nginx/ingress-nginx -n nginx-ingress
kubectl get services -n nginx-ingress # (To get the Load Balancer IP Address)
```

**Subir deployments**
```bash
kubectl apply -f goclient.yaml
```


### Referencias
[gcloud](https://cloud.google.com/sdk/docs/install?hl=es-419)

[kubectl](https://cloud.google.com/kubernetes-engine/docs/how-to/cluster-access-for-kubectl)

[kubectl commands](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands)

[Namespaces](https://kubernetes.io/docs/concepts/overview/working-with-objects/namespaces/)

[Deployments](https://kubernetes.io/docs/concepts/workloads/controllers/deployment/)

[Helm](https://helm.sh/docs/intro/quickstart/)