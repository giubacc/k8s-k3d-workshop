---
marp: true
theme: default
paginate: true
_class: lead
---

# Kubernetes Concepts

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

# Desired State vs Actual State

- **Core principle of Kubernetes**:
  - You define the **desired state** (e.g. 3 replicas of nginx)
  - Kubernetes continuously works to match the **actual state**
- The **control loop**:
  1. You declare what you want
  2. The system observes the current cluster
  3. It makes adjustments until actual = desired

👉 Kubernetes is a **self-healing system**

---

# Imperative vs Declarative

- **Imperative**: tell the system *exactly what to do*
  - `kubectl run nginx --image=nginx`
  - Procedural, step by step
- **Declarative**: tell the system *what you want*
  - Write a YAML → `kubectl apply -f nginx.yaml`
  - Kubernetes figures out how to reach that state
- Declarative approach = **GitOps friendly** and reproducible

---

# Recap

- **Why Kubernetes** → containers need orchestration
- **Cluster architecture** → Control Plane + Worker Nodes
- **Basic Concepts** → Pods, Deployments, Services, Namespaces
- **Core model** → Desired vs Actual state, Declarative configs

👉 With this foundation, we can start **hands-on with k3d**!

---

# Thanks!

- Convert to **HTML / PDF / PPTX** with **Marp**
- Q&A
