#!/bin/bash
kubectl autoscale deployment stress \
  -n demo \
  --cpu=50 \
  --min=1 \
  --max=5

kubectl get hpa -n demo -w
