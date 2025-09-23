---
marp: true
theme: default
paginate: true
_class: lead
---

# Kubernetes Concepts (30m)

---

# From Docker to Kubernetes

- Docker gave us **containers**
- But we still need to manage:
  - Many containers
  - Scaling up/down
  - Networking between them
  - Configuration & secrets
  - Self-healing

👉 This is why we need **orchestration**.

---

# Kubernetes in a Nutshell

- **Kubernetes** = Container Orchestrator
- Runs containers **at scale**
- Key abstractions:
  - **Cluster**: group of machines (nodes)
  - **Nodes**: worker machines (VM or physical)
  - **Pods**: smallest deployable unit (one or more containers)

---

# Kubernetes Architecture

**Control Plane**

- API Server
- Scheduler
- Controller Manager
- etcd (key/value store for cluster state)

**Worker Nodes**
- Kubelet (agent running on each node)
- Kube-proxy (networking)
- Container runtime (containerd, CRI-O, etc.)

---

# Control Plane vs Worker Nodes

- **Control Plane**: decides *what should happen*
- **Worker Nodes**: do the actual work (run Pods)

👉 API Server is the “front door” of the cluster
👉 etcd is the “source of truth”

---

# Basic Concepts: Pods

- Smallest deployable unit in Kubernetes
- Wraps **one or more containers**
- Containers in a Pod:
  - Share **network namespace**
  - Can communicate via `localhost`
  - Can share volumes

---

# Basic Concepts: Deployments

- Higher-level abstraction for managing Pods
- Provide:
  - **Scaling** (replicas)
  - **Self-healing** (restart Pods if they fail)
  - **Rolling updates**

👉 You rarely run Pods directly — you run **Deployments**

---

# Basic Concepts: Services

- Expose Pods to the network
- Types:
  - **ClusterIP**: internal only (default)
  - **NodePort**: accessible on node’s IP + port
  - **LoadBalancer**: external, cloud provider integration

👉 Services provide **stable DNS names** and load balancing across Pods

---

# Basic Concepts: Namespaces

- Virtual clusters inside a Kubernetes cluster
- Separate resources logically:
  - `default`
  - `kube-system`
  - `dev`, `staging`, `prod`
- Useful for **multi-team** or **multi-environment** setups

---

# Recap

- **Why Kubernetes** → containers need orchestration
- **Cluster architecture** → Control Plane + Worker Nodes
- **Basic Concepts** → Pods, Deployments, Services, Namespaces

👉 With this foundation, we can start **hands-on with k3d**!

---

# Thanks!

- Convert to **HTML / PDF / PPTX** with **Marp**
- Q&A
