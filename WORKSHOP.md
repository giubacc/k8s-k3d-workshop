# Workshop - Introduction to Kubernetes with k3d

## **Session 1 (2h)**

**Goal:** Understand containers, Kubernetes concepts, and run first workloads.

### 1. Theory (1h)

* **Containers & Isolation (30m)**
  * What is a container? Processes with isolation and limits
  * **Namespaces** (UTS, Mount, PID) → what a process *sees*
  * **cgroups** (CPU, Memory) → what a process *uses*
  * Build a minimal container by hand (unshare + cgroups)

* **Kubernetes Concepts (30m)**
  * From Docker to Kubernetes: why we need orchestration
  * High-level overview: Pods, Nodes, Clusters
  * Kubernetes Architecture:
    * Control Plane: API Server, Scheduler, Controller Manager, etcd
    * Worker Nodes: Kubelet, Kube-proxy, container runtime
  * Basic Concepts:
    * Pods
    * Deployments
    * Services (ClusterIP, NodePort, LoadBalancer)
    * Namespaces

### 2. Demo with k3d (1h)

* Install **k3d** and **kubectl**
* Create a cluster (`k3d cluster create demo`)
* Explore the cluster:
  * `kubectl get nodes`
  * `kubectl get pods -A`
* Deploy a simple application (e.g. NGINX or Hello World app)
  * `kubectl create deployment`
  * `kubectl expose deployment`
* Access the application in the browser

---

## **Session 2 (2h)**

**Goal:** Explore scaling, configuration, networking, and storage basics.

### 1. Theory (1h)

* **Scaling & Self-Healing (15m)**
  * ReplicaSets
  * Horizontal Pod Autoscaler (HPA) basics

* **Configuration Management (20m)**
  * ConfigMaps
  * Secrets

* **Networking & Ingress (15m)**
  * Service discovery
  * Ingress controllers (conceptual)

* **Storage Overview (10m)**
  * Volumes, Persistent Volumes, Persistent Volume Claims

### 2. Demo with k3d (1h)

* Scale an application
  * `kubectl scale deployment`
* Show self-healing (delete a pod, see it recreated)
* Create a ConfigMap and inject it into a pod
* Use a Secret (e.g. fake credentials for an app)
* Demonstrate Ingress with k3d’s built-in Traefik
* If time allows: create a Persistent Volume and attach it to a pod

---

## **Prerequisites for Participants**

* Docker installed
* k3d + kubectl installed (or guided installation at start)
* Basic Linux command line familiarity

---

## **Outcomes**

At the end of the workshop, participants should:

* Understand Linux container building blocks (namespaces + cgroups)
* Understand Kubernetes fundamentals
* Be able to create and explore a local Kubernetes cluster with k3d
* Deploy, scale, and expose applications
* Manage configuration, secrets, and basic networking
* Have a clear path for further learning (operators, monitoring, CI/CD integration)
