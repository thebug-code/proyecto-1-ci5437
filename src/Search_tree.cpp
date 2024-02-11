#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>
#include "Node.cpp"

#define MAX_LINE_LENGTH 999

using namespace std;

int main(int argc, char **argv)
{
    state_t state;                 // state_t es un tipo definido por PSVN_API. Es el tipo de estado utilizado en los operadores.
    char str[MAX_LINE_LENGTH + 1]; // MAX_LINE_LENGTH es el tamaño máximo permitido para una línea.
    ssize_t nstr;                  // Guarda el número de caracteres leídos

    state_t child;          // Guarda el estado hijo
    ruleid_iterator_t iter; // ruleid_terator_t es un tipo definido por PSVN_API. Es el tipo de iterador utilizado en los operadores.
    int ruleid;             // Se utiliza para guardar el identificador de una regla.

    // Cola de nodos
    queue<Node *> queue;

    // Esto se podría hacer directamente como pase de parámetros
    // Se lee el estado
    printf("Please enter a state: ");
    if (fgets(str, sizeof str, stdin) == NULL)
    {
        printf("Error: empty input line.\n");
        return 1;
    }

    // Se convierte el estado a un state_t
    nstr = read_state(str, &state);
    if (nstr <= 0)
    {
        printf("Error: invalid state entered.\n");
        return 1;
    }

    Node *root = Node::make_root(state);
    queue.push(root);
    int depth = 0;
    int nodes_at_depth = 0;
    float branching_factor = 0;

    // Se recorre el árbol de búsqueda
    while (!queue.empty())
    {
        int number_of_child = 0;
        nodes_at_depth = queue.size();

        // Se recorren los nodos en la cola
        for (int i = 0; i < nodes_at_depth; i++)
        {
            Node *node = queue.front();
            queue.pop();

            init_fwd_iter(&iter, &node->state);
            while ((ruleid = next_ruleid(&iter)) >= 0)
            {
                apply_fwd_rule(ruleid, &node->state, &child);
                Node *child_node = node->make_node(child, get_fwd_rule_label(ruleid));
                queue.push(child_node);
                number_of_child++;
            }
        }

        // Se imprime la información del nivel
        branching_factor = (float)number_of_child / nodes_at_depth;
        cout << "Depth: " << depth << "Nnodes" << nodes_at_depth << " Branching factor: " << branching_factor << endl;
        depth++;

        if (number_of_child == 0)
        {
            printf("the state has no children\n");
        }
    }
    return 0;
}