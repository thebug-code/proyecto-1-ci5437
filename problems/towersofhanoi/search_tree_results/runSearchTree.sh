#!/usr/bin/bash

mkdir results

# Correr BFS en topspin12-4 sin eliminacion de duplicados
echo "Corriendo BFS en topspin12-4 sin eliminacion de duplicados, 15 minutos"
taskset -c 1 timeout 900 ./topspin12-4.bfs > "results/topspin12-4-bfs.txt" &

# Correr BFS en topspin14-4 sin eliminacion de duplicados
echo "Corriendo BFS en topspin14-4 sin eliminacion de duplicados, 15 minutos"
taskset -c 2 timeout 900 ./topspin14-4.bfs > "results/topspin14-4-bfs.txt" &

# Correr BFS en topspin17-4 sin eliminacion de duplicados
echo "Corriendo BFS en topspin17-4 sin eliminacion de duplicados, 15 minutos"
taskset -c 3 timeout 900 ./topspin17-4.bfs > "results/topspin17-4-bfs.txt"
