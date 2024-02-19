#!/usr/bin/bash

mkdir results

# Correr UCS en rubikscube3x3x3 sin eliminacion de duplicados
echo "Corriendo UCS en rubikscube3x3x3 sin eliminacion de duplicados, 15 minutos"
taskset -c 1 timeout 900 ./rubikscube3x3x3.ucs > "results/rubikscube3x3x3-ucs.txt"
