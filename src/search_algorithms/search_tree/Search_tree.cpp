// Search tree with no duplicates
#include <vector>
#include "priority_queue.hpp"

int main(int argc, char **argv)
{
    int64_t Nodes, numAtD;  // counters
    float branchingFactor;  // branching factor
    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int d, ruleid;          // d: distance to initial state
    ruleid_iterator_t iter; // ruleid iterator

    PriorityQueue<state_t> open;        // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated

    // add goal states
    first_goal_state(&state, &d);
    do
    {
        state_map_add(map, &state, 0);
        open.Add(0, 0, state);
    } while (next_goal_state(&state, &d));

    d = 0;
    numAtD = 0;
    Nodes = 0;
    branchingFactor = 0;
    while (!open.Empty())
    {
        // get current distance from goal; since operator costs are
        // non-negative this distance is monotonically increasing
        if (open.CurrentPriority() > d)
        {
            printf("Estados: %" PRId64 ", Profundidad: %d, factor: %f\n", numAtD, d, branchingFactor);
            d = open.CurrentPriority();
            Nodes = numAtD;
            numAtD = 0;
        }

        // remove top state from priority state
        state = open.Top();
        open.Pop();

        // check if we already expanded this state.
        // (entries on the open list are not deleted if a cheaper path to a state is found)
        const int *best_dist = state_map_get(map, &state);
        assert(best_dist != NULL);
        if (*best_dist < d)
            continue;

        numAtD++;
        branchingFactor = (float)numAtD / (float)Nodes;

        // look at all predecessors of the state
        init_bwd_iter(&iter, &state);
        while ((ruleid = next_ruleid(&iter)) >= 0)
        {
            apply_bwd_rule(ruleid, &state, &child);
            int move_cost = get_bwd_rule_cost(ruleid);
            const int child_d = d + move_cost;

            // check if either this child has not been seen yet or if
            // there is a new cheaper way to get to this child.
            const int *old_child_d = state_map_get(map, &child);

            state_map_add(map, &child, child_d);
            open.Add(child_d, child_d, child);
        }
    }
    // print last level
    if (numAtD > 0)
    {
        printf("Estados: %" PRId64 ", Profundidad: %d, factor: %f\n", numAtD, d, branchingFactor);
    }

    return 0;
}