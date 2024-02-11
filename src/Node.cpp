#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <iostream>

using namespace std;

// claae to represent a node in the search tree
class Node
{

public:
    state_t state; // state represented by the node
    Node *parent;  // parent node
    string action; // action that led to this state
    unsigned cost; // cost of the path from the root to this node
    int color;     // color of the node: -1 black, 0 white, 1 gray

    Node(state_t state, Node *parent, string action, unsigned cost, int color)
    {
        this->state = state;
        this->parent = parent;
        this->action = action;
        this->cost = cost;
        this->color = color;
    }

    Node *make_node(state_t s, string action)
    {
        return new Node(state, this, action, this->cost + 1, 0);
    }

    void extract_path(vector<string> &reversed_path)
    {
        Node *node = this;
        while (node != NULL && node->parent != NULL)
        {
            reversed_path.push_back(node->action);
            node = node->parent;
        }
    }

    static Node *make_root(state_t state)
    {
        return new Node(state, NULL, "", 0, 0);
    }
};