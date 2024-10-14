#!/bin/bash

# Remove all Docker images
sudo docker rmi -f $(sudo docker images -a -q)

# Variables for the Docker images
GO_CLIENT_IMAGE="golang-client-grpc"
RUST_CLIENT_IMAGE="rust-client-grpc"
GO_SERVER_IMAGE="golang-server-grpc"
DOCKERHUB_USERNAME="alvarog1318"
TAG="0.1"

# Build the Docker image for the Go client
sudo docker build -t $GO_CLIENT_IMAGE ./gRPC/golang-client
# Build the Docker image for the Rust client
sudo docker build -t $RUST_CLIENT_IMAGE ./gRPC/golang-server
# Build the Docker image for the Go server
sudo docker build -t $GO_SERVER_IMAGE ./gRPC/grpc-client


# Tag the Docker image
docker tag $GO_CLIENT_IMAGE "$DOCKERHUB_USERNAME/$GO_CLIENT_IMAGE:$TAG"
docker tag $RUST_CLIENT_IMAGE "$DOCKERHUB_USERNAME/$RUST_CLIENT_IMAGE:$TAG"
docker tag $GO_SERVER_IMAGE "$DOCKERHUB_USERNAME/$GO_SERVER_IMAGE:$TAG"

# Push the Docker image to DockerHub
docker push "$DOCKERHUB_USERNAME/$GO_CLIENT_IMAGE:$TAG"
docker push "$DOCKERHUB_USERNAME/$RUST_CLIENT_IMAGE:$TAG"
docker push "$DOCKERHUB_USERNAME/$GO_SERVER_IMAGE:$TAG"

echo "Docker images pushed successfully."