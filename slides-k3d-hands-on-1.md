---
marp: true
theme: default
paginate: true
---

# k3d Hands-On (1h)

---

# Step 0 — Check prerequisites

- Verify Docker is running:
```bash
docker ps
```

---

# Step 1 — Install kubectl

- Linux (curl):
```bash
curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
sudo install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl
```

- Verify:
```bash
kubectl version --client
```

---

# Step 2 — Install k3d

- Linux (curl):
```bash
curl -s https://raw.githubusercontent.com/k3d-io/k3d/main/install.sh | bash
```

- Verify:
```bash
k3d version
```

---

# Step 3 — Create a cluster

- Create a new cluster:
```bash
k3d cluster create demo --servers 1 --agents 2
```

- What happens:
  - Control plane + worker nodes in Docker
- Verify:
```bash
kubectl get nodes -o wide
```

---

# Step 4 — Explore the cluster

- List all namespaces & pods:
```bash
kubectl get pods -A
```

- Default namespaces:
  - `default`
  - `kube-system`
  - `kube-public`
  - `kube-node-lease`

- System pods: CoreDNS, Traefik, etc.

---

# Step 5 — Deploy a simple app

- Write a Deployment manifest `nginx-deployment.yaml`:

- Apply it:
```bash
kubectl apply -f nginx-deployment.yaml
```

- Check Pods:
```bash
kubectl get pods
kubectl describe deployment nginx-deployment
```

---

# Step 6 — Expose the app

- Expose as NodePort service:
```bash
kubectl expose deployment nginx-deployment --port=80 --type=NodePort
```

- Check service:
```bash
kubectl get svc
```

- Access in browser:
  - `http://<any-node-ip>:<nodePort>`

---

# Step 7 — Cleanup & recap

- Delete resources:
```bash
kubectl delete svc nginx-deployment
kubectl delete deployment nginx-deployment
```

- Optional: delete cluster:
```bash
k3d cluster delete demo
```

- Recap:
  - **Deployment → Pod(s)** (declarative, managed)
  - **Service → stable access**
  - First app deployed on Kubernetes 🎉

---

# Thanks!

- Convert to **HTML / PDF / PPTX** with **Marp**
- Q&A
