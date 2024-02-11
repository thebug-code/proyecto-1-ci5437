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
    state_t state;
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nstr;

    state_t child;
    ruleid_iterator_t iter;
    int ruleid;

    queue<Node *> queue;

    Node *root = Node::make_root(state);
    queue.push(root);
    int depth = 0;
    int nodes_at_depth = 0;
    float branching_factor = 0;

    while (!queue.empty())
    {
        int count = 0;
        nodes_at_depth = queue.size();

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
                count++;
            }
        }

        branching_factor = (float)count / nodes_at_depth;
        cout << "Depth: " << depth << "Nnodes" << nodes_at_depth << " Branching factor: " << branching_factor << endl;
    }
}