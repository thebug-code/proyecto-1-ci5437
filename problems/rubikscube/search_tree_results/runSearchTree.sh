#!/usr/bin/bash

mkdir results

# Correr IDDFS en rubikscube3x3x3 sin eliminacion de duplicados
echo "Corriendo BFS en rubikscube3x3x3 sin eliminacion de duplicados, 15 minutos"
taskset -c 1 timeout 900 ./rubikscube3x3x3.bfs > "results/rubikscube3x3x3-bfs.txt"
