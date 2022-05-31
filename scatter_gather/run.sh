#!/bin/bash
# Benchmark with different number of processes

for i in $(seq 1 8)
do
echo "$i processes"
time mpirun -np $i ./multmatriz
done
