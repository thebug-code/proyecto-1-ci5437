#!/usr/bin/bash

mkdir results

# Correr UCS en topspin12-4 sin eliminacion de duplicados
echo "Corriendo UCS en topspin12-4 sin eliminacion de duplicados, 15 minutos"
taskset -c 1 timeout 900 ./topspin12-4.ucs > "results/topspin12-4-ucs.txt" &

# Correr UCS en topspin14-4 sin eliminacion de duplicados
echo "Corriendo UCS en topspin14-4 sin eliminacion de duplicados, 15 minutos"
taskset -c 2 timeout 900 ./topspin14-4.ucs > "results/topspin14-4-ucs.txt" &

# Correr UCS en topspin17-4 sin eliminacion de duplicados
echo "Corriendo UCS en topspin17-4 sin eliminacion de duplicados, 15 minutos"
taskset -c 3 timeout 900 ./topspin17-4.ucs > "results/topspin17-4-ucs.txt"
