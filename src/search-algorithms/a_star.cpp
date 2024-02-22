#include <vector>
#include "search_tree/priority_queue.hpp"
#include <stdbool.h>
#include <fstream>
#include <string>
#include <time.h>

#define  MAX_LINE_LENGTH 999

using namespace std;

int64_t nodes_expanded;

int a_star(state_t *init_state) {
    PriorityQueue<state_t> fronteir;          // Cola de prioridad ordenada por f
    ruleid_iterator_t iter;                   // Iterador para los sucesores
    int g, ruleid;
    state_t state, child;                     // Estado actual, estado hijo
    state_map_t *distance;                    // Tabla de hash para las distancias
    

    distance = new_state_map();
    state_map_add(distance, init_state, 0);

    // Agrega el estado inicial a la frontera (f, g, estado)
    fronteir.Add(0, 0, *init_state);
    
    while(!fronteir.Empty()) {
        // Obtiene la actual distancia desde el estado inicial
        g = fronteir.CurrentPriority();
        
        // Obtiene el estado con menor f
        state = fronteir.Top();
        fronteir.Pop();

        int *old_distance = state_map_get(distance, &state);
        ++nodes_expanded;

        if ((old_distance == NULL) || (g < *old_distance) || (!compare_states(&state, init_state))) {
            // Actualiza la distancia del estado actual
            state_map_add(distance, &state, g);

            // Verifica si el estado actual es un estado objetivo
            if (is_goal(&state)) return g;
            
            init_fwd_iter(&iter, &state);
            while((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &state, &child);

                // Calcula la distancia del estado hijo
                int child_h = heuristic(child);

                if (child_h < INT_MAX) {
                    int child_g = g + get_fwd_rule_cost(ruleid);
                    int child_f = child_g + child_h;

                    fronteir.Add(child_f, child_g, child);
                }
            }
        }
    }
    // Libera la memoria asociada a la tabla de hash
    //destroy_state_map(distance);

    // No se encontró solución
    return -1;
}

int main(int argc, char **argv) {
    char str[MAX_LINE_LENGTH + 1];
    string line;
    int d;
    ssize_t nchars;
    float runTime;
    state_t init_state;
    ifstream file;
    clock_t init_stateTime, endTime, timeSpan;

    loadPDB();

    printf("Ingresa el nombre del archivo de prueba: ");
    if (fgets(str, sizeof str, stdin) == NULL) {
        printf("Error: Invalid filename\n");
        return 0;
    }

    str[strlen(str)-1] = '\0';
    file.open(str);

    if (!file.is_open()) {
        printf("Error: Invalid filename: %s\n", str);
        return -1;
    }

    printf("Instancia \t\t\t Resuelto   Tiempo \t   Nodos Expandidos   Distancia\t\n");
    printf("-----------------------------------------------------------------------------\n");
    
    while (!file.eof()) {
        getline(file, line);
        nchars = read_state(line.c_str(), &init_state);
        if (nchars <= 0) {
            printf("Error: estado invalido\n");
            continue;
        }

        init_stateTime = clock();
        nodes_expanded = 0; 

        d = a_star(&init_state);

        endTime = clock();

        timeSpan = endTime - init_stateTime;

        runTime = timeSpan / (double) CLOCKS_PER_SEC;

        if (d < 0) {
            printf("%s \t False \t %f \t %ld \t\t %d\n", line.c_str(), runTime, nodes_expanded, d);
        } else {
            printf("%s \t True \t %f \t %ld \t\t %d\n", line.c_str(), runTime, nodes_expanded, d);
        }
        
    }

    file.close();
    return 0;
}
