#!/usr/bin/env bash
set -euo pipefail

CGROUP=/sys/fs/cgroup/testmem
LIMIT_MB="${LIMIT_MB:-50}"   # default 50MB if not set outside

echo ">>> Setting up cgroup at $CGROUP with limit ${LIMIT_MB}MB"

# Set memory limit (bytes)
echo $((LIMIT_MB * 1024 * 1024)) | sudo tee "$CGROUP/memory.max" > /dev/null
echo 0 | sudo tee "$CGROUP/memory.swap.max" > /dev/null

# Start the memory hog program in background
./memhog &

PID=$!
echo ">>> Memory hog PID: $PID"

# Attach process to cgroup
echo $PID | sudo tee "$CGROUP/cgroup.procs" > /dev/null

echo ">>> Process is now in cgroup with limit ${LIMIT_MB}MB"
echo ">>> Watching memory.current..."

# Live monitor memory.current until process exits
(
  while kill -0 $PID 2>/dev/null; do
    usage_bytes=$(cat "$CGROUP/memory.current")
    usage_mb=$((usage_bytes / 1024 / 1024))
    echo "memory.current = ${usage_mb} MB"
    sleep 1
  done
) &

wait $PID || echo ">>> Process was killed by OOM!"

echo ">>> Done."
