#!/usr/bin/bash

mkdir results

# Correr BFS en 15-puzzle sin eliminacion de duplicados
echo "Corriendo IDDFS en 15-puzzles sin eliminacion de duplicados, 15 minutos"
taskset -c 1 timeout 900 ./15-puzzles.iddfs > "results/15-puzzles-iddfs.txt" &

# Correr IDDFS en 24-puzzle sin eliminacion de duplicados
echo "Corriendo IDDFS en 24-puzzles sin eliminacion de duplicados, 15 minutos"
taskset -c 2 timeout 900 ./24-puzzles.iddfs > "results/24-puzzles-iddfs.txt"
