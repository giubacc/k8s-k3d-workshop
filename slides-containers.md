---
marp: true
theme: default
paginate: true
_class: lead
---

# Introduction to Containers
### Namespaces & cgroups: building blocks

---

# What Are Containers?

- Lightweight isolation mechanism
- Share the host kernel
- Combine:
  - **Namespaces** → isolate what a process can *see*
  - **cgroups** → limit what a process can *use*
- Goal today: build a container by hand

---

# Namespaces Overview

- **Namespaces** partition kernel resources
- A process sees its own view of:
  - Hostname (UTS)
  - Mount table (Mount namespace)
  - Process tree (PID)
- We’ll demo: **UTS**, **Mount**, **PID**

---

# UTS + Mount Namespace Demo

```bash
sudo unshare --uts --mount --fork /bin/bash
```

- `unshare`: userland tool to detach from namespaces
- `--uts`: new hostname/UTS namespace
- `--mount`: new mount namespace (private mount table)

**Try inside:**

```bash
hostname mycontainer
hostname     # shows "mycontainer"
exit
hostname     # unchanged on host
```

---

# Mount Namespace in Action

```bash
sudo unshare --mount --fork /bin/bash
mount -t tmpfs none /mnt
touch /mnt/hello.txt
ls /mnt        # file visible here
exit
ls /mnt        # mount disappeared
```

- Each mount namespace has its own view of mounts

---

# PID Namespace

```bash
sudo unshare --pid --fork --mount-proc /bin/bash
```

- `--pid`: new PID namespace (first process becomes **PID 1**)
- `--mount-proc`: mount a fresh `/proc` so tools show only local processes

**Try:**
```bash
echo $$   # shows 1
ps -ef    # only shows processes in this namespace
```

---

# cgroups Overview

- **cgroups** = control groups
- Limit & account for resources:
  - CPU
  - Memory
  - (Also I/O, pids, devices, etc.)
- Unified hierarchy: `/sys/fs/cgroup` (cgroup v2)

---

# CPU cgroup Demo (~10% CPU)

```bash
mount -t cgroup2 none /sys/fs/cgroup || true
sudo mkdir -p /sys/fs/cgroup/mydemo

yes > /dev/null &
pid=$!
echo 10000 100000 | sudo tee /sys/fs/cgroup/mydemo/cpu.max
echo $pid | sudo tee /sys/fs/cgroup/mydemo/cgroup.procs
```

- Limits the process to ~10% CPU
- Verify with `top` or `htop`

---

# Memory cgroup Demo (50 MB)

```bash
sudo mkdir -p /sys/fs/cgroup/memorydemo
echo $((50*1024*1024)) | sudo tee /sys/fs/cgroup/memorydemo/memory.max

python3 -c "a = ' ' * 100_000_000; print('Allocated!'); input()" &
pid=$!

echo $pid | sudo tee /sys/fs/cgroup/memorydemo/cgroup.procs
```

- Memory limit = **50 MB**
- Process should be killed by OOM (SIGKILL) when exceeding the limit

---

# Build a Container by Hand

1) **Create a cgroup**

```bash
sudo mkdir -p /sys/fs/cgroup/mycontainer
echo 200M | sudo tee /sys/fs/cgroup/mycontainer/memory.max
echo 20000 100000 | sudo tee /sys/fs/cgroup/mycontainer/cpu.max
```

2) **Start isolated namespaces**

```bash
sudo unshare --pid --uts --mount --fork --mount-proc /bin/bash
```

3) **Inside the shell**

```bash
hostname tinybox
echo $$ > /sys/fs/cgroup/mycontainer/cgroup.procs
```

---

# What We Just Built

- A “hand-rolled container”:
  - Own **PID/UTS/Mount namespaces**
  - CPU & memory limits via **cgroups**
- Docker/Kubernetes add:
  - Images & layers
  - Networking
  - Orchestration & scheduling

---

# Tips & Caveats

- You may need `sudo` for mounts and cgroups
- Ensure cgroup v2 is mounted at `/sys/fs/cgroup`
- Some distros require `systemd.unified_cgroup_hierarchy=1`
- Clean up background jobs after demos

---

# Next Steps

- Images & runtimes (runc, containerd, Docker)
- Filesystem isolation (chroot, pivot_root, overlayfs)
- Networking (net namespaces, veth, CNI)
- Orchestration (Kubernetes basics)

---

# Thanks!

- Convert to **HTML / PDF / PPTX** with **Marp**
- Q&A
