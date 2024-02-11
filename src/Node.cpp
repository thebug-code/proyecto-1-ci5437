#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>

using namespace std;

// clase que representa un nodo del arbol de busqueda
class Node
{

public:
    state_t state; // estado del nodo
    Node *parent;  // padre del nodo
    string action; // accion que lleva al nodo
    unsigned cost; // costo del nodo
    int color;     // color del nodo (0 = white, 1 = grey, -1 = black)

    // constructor
    Node(state_t state, Node *parent, string action, unsigned cost, int color)
    {
        this->state = state;
        this->parent = parent;
        this->action = action;
        this->cost = cost;
        this->color = color;
    }

    // metodo que crea un nodo
    Node *make_node(state_t s, string action)
    {
        return new Node(state, this, action, this->cost + 1, 0);
    }

    // metodo que extrae el camino desde el nodo hasta la raiz
    void extract_path(vector<string> &reversed_path)
    {
        Node *node = this;
        while (node != NULL && node->parent != NULL)
        {
            reversed_path.push_back(node->action);
            node = node->parent;
        }
    }

    // metodo que crea un nodo raiz
    static Node *make_root(state_t state)
    {
        return new Node(state, NULL, "", 0, 0);
    }
};