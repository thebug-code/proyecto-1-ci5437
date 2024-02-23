#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// GOAL 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
// Obtener la distancia Manhantan de una ficha a su posición objetivo
int manhattan(state_t *state)
{
    int h = 0;
    var_t *tile = state->vars;
    int row, col;
    int ntile;
    int row_goal, col_goal;

    for (int i = 0; i < 16; i++)
    {
        ntile = (int)tile[i];
        // Obtener la posición de la ficha en el estado actual
        if (ntile == 0)
        {
            continue;
        }
        row = i / 4;
        col = i % 4;
        row_goal = ntile / 4;
        col_goal = ntile % 4;

        // Obtener la posición objetivo de la ficha
        // Calcular la distancia Manhattan
        h += abs(row - row_goal) + abs(col - col_goal);
    }
    return h;
}