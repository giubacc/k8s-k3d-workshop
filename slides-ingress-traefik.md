---
marp: true
theme: default
paginate: true
---

# Ingress in Kubernetes

---

# Why Ingress?

- Services (ClusterIP, NodePort, LoadBalancer) expose Pods
- But for **HTTP/HTTPS apps** we often need:
  - Friendly URLs
  - Host-based and path-based routing
  - TLS termination (HTTPS)
- **Ingress** = API object that manages external access to Services

---

# Ingress Controller

- Ingress is just the **specification**
- Needs an **Ingress Controller** implementation:
  - NGINX Ingress Controller
  - HAProxy Ingress
  - **Traefik Ingress (default in k3d)**
- Controller watches Ingress resources and configures the reverse proxy accordingly

---

# Traefik in k3d

- k3d installs **Traefik** by default
- Provides:
  - Reverse proxy
  - HTTP routing based on Ingress rules
  - TLS termination with Let’s Encrypt integration
- Accessible through a NodePort in the k3d cluster

---
# Example: Ingress Resource

```yaml
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: web-ingress
spec:
  rules:
  - host: web.local
    http:
      paths:
      - path: /
        pathType: Prefix
        backend:
          service:
            name: web
            port:
              number: 80
```

- Routes `http://web.local/` → `web` Service on port 80

---

# How It Works

1. User requests `http://web.local`
2. DNS resolves `web.local` → cluster node
3. Traefik (Ingress Controller) receives traffic
4. Traefik matches Ingress rules
5. Request is forwarded to backend Service → Pod

---

# TLS with Traefik

- Traefik can terminate TLS (HTTPS) at the ingress
- Ingress resource defines a TLS section:

```yaml
spec:
  tls:
  - hosts:
    - web.local
    secretName: web-tls
```

- `web-tls` = Kubernetes Secret containing certificate + key
- Traefik uses this secret to serve HTTPS

---

# Benefits of Ingress + Traefik

- Central entry point for all apps
- Clean URLs (no need for high NodePorts)
- Path- or host-based routing
- TLS termination and Let’s Encrypt support
- Built-in to k3d → no extra install required

---

# Recap

- **Ingress** = Kubernetes resource for external HTTP/HTTPS access
- Needs a **controller** → in k3d it’s **Traefik**
- Define routing rules in an **Ingress object**
- Supports TLS termination
- Traefik = flexible, production-ready ingress controller
