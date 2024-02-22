#include <iostream>

state_map_t *map1;
state_map_t *map2;
state_map_t *map3;
state_map_t *map4;
abstraction_t *abs1;
abstraction_t *abs2;
abstraction_t *abs3;
abstraction_t *abs4;
state_t abs_state1;
state_t abs_state2;
state_t abs_state3;
state_t abs_state4;

unsigned maximum;

void loadPDB(){
	FILE *f1 = fopen("towersofhanoi4-18-abs1.pdb", "r");
	FILE *f2 = fopen("towersofhanoi4-18-abs2.pdb", "r");
	FILE *f3 = fopen("towersofhanoi4-18-abs3.pdb", "r");
	FILE *f4 = fopen("towersofhanoi4-18-abs4.pdb", "r");

	abs1 = read_abstraction_from_file("towersofhanoi4-18-abs1.abst");
	map1 = read_state_map(f1);

	abs2 = read_abstraction_from_file("towersofhanoi4-18-abs2.abst");
	map2 = read_state_map(f2);

	abs3 = read_abstraction_from_file("towersofhanoi4-18-abs3.abst");
	map3 = read_state_map(f3);

	abs4 = read_abstraction_from_file("towersofhanoi4-18-abs4.abst");
	map4 = read_state_map(f4);

	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
}

unsigned heuristic(state_t puzzle_state){
	abstract_state(abs1, &puzzle_state, &abs_state1);
	abstract_state(abs2, &puzzle_state, &abs_state2);
	abstract_state(abs3, &puzzle_state, &abs_state3);
	abstract_state(abs4, &puzzle_state, &abs_state4);

	maximum = std::max(*state_map_get(map1, &abs_state1), *state_map_get(map2, &abs_state2));
	maximum = std::max(maximum, *state_map_get(map3, &abs_state3));
	maximum = std::max(maximum, *state_map_get(map4, &abs_state4));

	return (maximum);
}