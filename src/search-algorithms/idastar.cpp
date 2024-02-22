#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <time.h>


#define MAX_LINE_LENGTH 999

unsigned long int nodes = 0;

using namespace std;

pair<state_t *, int> boundDFS(state_t *state, int cost, int bound, int hist)
{

    int f = cost + heuristic(*state);
    int t = INT_MAX;
    int ruleid;
    ruleid_iterator_t iter;
    state_t *child = new state_t;

    if (f > bound){
        return make_pair(nullptr, f);
    }

    if (is_goal(state)) {
        printf("Solution: %d\n", cost);
        printf("Nodes expanded: %ld\n", nodes);
        return make_pair(state, cost);
    }

    pair<state_t *, int> n;

    nodes++;

    init_fwd_iter(&iter, state);
    while ((ruleid = next_ruleid(&iter)) >= 0)
    {

        apply_fwd_rule(ruleid, state, child);

        if (!fwd_rule_valid_for_history(hist, ruleid))
            continue;

        int newCost = cost + get_fwd_rule_cost(ruleid);

        n = boundDFS(child, newCost, bound, next_fwd_history(hist, ruleid));

        if (n.first != NULL)
        {
            return n;
        }

        t = min(t, n.second);
    }
    return make_pair(nullptr, t);
}

int idastar(state_t *state)
{
    int bound = heuristic(*state);
    pair<state_t *, int> n;
    state_t *child = new state_t;
    int ruleid;
    ruleid_iterator_t iter;

    while (true)
    {
        n = boundDFS(state, 0, bound, init_history);
        if (n.first != NULL)
        {
            return bound;
        }
        bound = n.second;
    }
}

// TEST FILE READER
int main(int argc, char **argv)
{

    char str[MAX_LINE_LENGTH + 1];
    state_t state;
    FILE *file;
    int64_t solution;
    clock_t start, end;
    double cpu_time_used;

    if (argc < 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }
    printf("File: %s\n", argv[1]);

    while (fgets(str, sizeof(str), file) != NULL)
    {
        printf("Reading: %s", str);
        if (read_state(str, &state) > 0)
        {
            start = clock();
            solution = idastar(&state);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

            printf("Time: %f\n", cpu_time_used);
        }
    }

    fclose(file);
    return 0;
}