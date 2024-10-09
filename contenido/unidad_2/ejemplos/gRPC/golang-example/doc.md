## Para iniciar con gRPC, primero se debe instalar de manera local `Protocol Buffer Compiler Installation`

**Insalación en el SO**
```bash
# Para linux con debian | ubuntu
apt install -y protobuf-compiler
protoc --version  # Ensure compiler version is 3+

# Para fedora
sudo dnf install protobuf-compiler
```

**Luego debemos instalar un paquete para golang para poder usar gRPC y otros paquetes globales**
```bash
go get google.golang.org/grpc

go install google.golang.org/protobuf/cmd/protoc-gen-go@latest

go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@latest
```

**Actualizar en el PATH para poder compilar**
```bash
export PATH=$PATH:$(go env GOPATH)/bin
```

**Instalar fiber para crear APIs rápido**

```bash
go get github.com/gofiber/fiber/v2 # fiber
```

**Comando para generar compilados dentro de la carpeta `/proto`**
```bash
protoc --go_out=. --go-grpc_out=. $(name).proto # compilar el archivo .proto  
```

**Links oficiales**
- [Introducción a gRPC](https://grpc.io/docs/what-is-grpc/introduction/)
- [Ejemplo con golang](https://grpc.io/docs/languages/go/quickstart/)