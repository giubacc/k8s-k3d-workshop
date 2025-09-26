#!/bin/bash
kubectl delete -n demo horizontalpodautoscalers.autoscaling stress
kubectl delete -n demo deployment stress
