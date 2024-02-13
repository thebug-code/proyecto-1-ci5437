#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

#include "priority_queue.hpp"

#define  MAX_LINE_LENGTH 999 

unsigned long int expanded_nodes = 0;

/**
 * Algoritmo A* con eliminación tardía de duplicados
 *
 * @param init_state Estado inicial
 * @param h Función heurística
 * @return Costo de la solución o -1 si no se encontró solución
 */
int a_star(state_t init_state, int (*h) (state_t*)) {
    PriorityQueue<state_t> fronteir; // Cola de prioridad ordenada por f
    ruleid_iterator_t iter;          // Iterador para los sucesores
    int ruleid, g0, g1;              // Identificador de la regla, g actual, g nuevo
    state_t current_state, child;    // Estado actual, estado hijo
    state_map_t *distances;          // Tabla de hash para las distancias

    distances = new_state_map();
    state_map_add(distances, &init_state, 0);

    // Agregar el estado inicial a la frontera (f, g, estado)
    fronteir.Add(h(&init_state), 0, init_state);

    while (!fronteir.Empty()) {
        // Obtiene el estado con menor f
        current_state = fronteir.Top();
        fronteir.Pop();

        // Obtiene el valor de g
        g1 = fronteir.CurrentPriority();

        // Obtiene el valor de la actual distancia
        g1 -= h(&current_state);

        expanded_nodes++;

        // Verifica si el estado actual es un estado objetivo
        if (is_goal(&current_state)) {
            // Libera la memoria asociada a la tabla de hash
            destroy_state_map(distances);
            return g1;
        }

        // Obtiene la distancia del estado actual
        g0 = state_map_get(distances, &current_state);

        // Si el estado no ha sido visitado o si el nuevo valor de g es menor
        // que el anterior, se actualiza la distancia y se agregan los sucesores
        // a la frontera
        if (g0 == NULL || g1 < g0) {
            // Actualiza la distancia del estado actual
            state_map_add(distances, &current_state, g1);

            init_fwd_iter(&iter, &current_state);
            while ((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &current_state, &child);

                // Calcula la distancia del estado hijo
                int h_value = h(&child);

                if (h_value < INT_MAX) {
                    int g_value = g1 + get_fwd_rule_cost(ruleid);
                    fronteir.Add(g_value + h_value, g_value, child);
                }
            }
        }
    }

    // Libera la memoria asociada a la tabla de hash
    destroy_state_map(distances);

    // No se encontró solución
    return -1;
}
