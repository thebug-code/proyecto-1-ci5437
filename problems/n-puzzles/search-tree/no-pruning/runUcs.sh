#!/usr/bin/bash

mkdir results

# Correr UCS en 15-puzzle sin eliminacion de duplicados
echo "Corriendo UCS en 15-puzzles sin eliminacion de duplicados, 15 minutos"
taskset -c 1 timeout 900 ./15-puzzles.ucs > "results/15-puzzles-ucs.txt" &

# Correr UCS en 24-puzzle sin eliminacion de duplicados
echo "Corriendo UCS en 24-puzzles sin eliminacion de duplicados, 15 minutos"
taskset -c 2 timeout 900 ./24-puzzles.ucs > "results/24-puzzles-ucs.txt"
