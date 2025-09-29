#!/bin/bash

kubectl delete configmap -n demo myapp-config
kubectl delete statefulset -n demo myapp

kubectl delete configmap -n demo pg-config
kubectl delete service -n demo pg
kubectl delete statefulset -n demo pg


psql -h pg-0.pg.demo.svc.cluster.local -U postgres -d appdb
psql -h pg-1.pg.demo.svc.cluster.local -U postgres -d appdb

#CREATE TABLE demo_table (id SERIAL PRIMARY KEY, msg TEXT);
#INSERT INTO demo_table (msg) VALUES ('Hello from primary');
#INSERT INTO demo_table (msg) VALUES ('Replication test');
#SELECT * FROM demo_table;

# see if master/replica
#SELECT pg_is_in_recovery();
