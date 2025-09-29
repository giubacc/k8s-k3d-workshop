---
marp: true
theme: default
paginate: true
---

# Dockerfiles — Building Container Images

---

# What is a Dockerfile?

- A **recipe** to build container images  
- Defines:
  - **Base image** (e.g. Ubuntu, Alpine, Python, Postgres)  
  - **Steps** to install dependencies  
  - **Commands** to run inside container  

👉 Output = an **image** you can run with `docker run` or deploy to Kubernetes

---

# Dockerfile — Basic Example

```dockerfile
# Start from a base image
FROM python:3.12-slim

# Set working directory inside the image
WORKDIR /app

# Copy files into the image
COPY requirements.txt .
RUN pip install -r requirements.txt

# Copy app source
COPY . .

# Command executed when container starts
CMD ["python", "app.py"]
```

---

# Building & Running

- Build the image:
```bash
docker build -t myapp:1.0 .
```

- Run the container:
```bash
docker run --rm -p 8080:8080 myapp:1.0
```

👉 Now your app runs in an isolated environment built from the Dockerfile

---

# Best Practices

- Use **small base images** (`alpine`, `slim`)  
- Keep layers minimal (combine commands)  
- Don’t run as **root** inside containers  
- Add `.dockerignore` to avoid copying junk  
- Pin versions for reproducibility  

---

# Multi-stage Builds

- Useful for apps that need **build tools** but not in final image

```dockerfile
# Stage 1: build
FROM golang:1.23 as builder
WORKDIR /src
COPY . .
RUN go build -o myapp

# Stage 2: runtime
FROM alpine:3.20
COPY --from=builder /src/myapp /usr/local/bin/
CMD ["myapp"]
```

---

# Recap — Dockerfiles

- **Dockerfile** = recipe to build images  
- **Build** with `docker build`  
- **Run** with `docker run`  
- Best practices = small, secure, reproducible  
- Multi-stage builds = efficient production images
