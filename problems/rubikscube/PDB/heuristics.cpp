#include <iostream>

state_map_t *map1;
state_map_t *map2;
state_map_t *map3;
state_map_t *map4;
state_map_t *map5;
state_map_t *map6;
state_map_t *map7;
state_map_t *map8;
abstraction_t *abs1;
abstraction_t *abs2;
abstraction_t *abs3;
abstraction_t *abs4;
abstraction_t *abs5;
abstraction_t *abs6;
abstraction_t *abs7;
abstraction_t *abs8;
state_t abs_state1;
state_t abs_state2;
state_t abs_state3;
state_t abs_state4;
state_t abs_state5;
state_t abs_state6;
state_t abs_state7;
state_t abs_state8;
unsigned maximum;

void loadPDB(){
	FILE *f1 = fopen("8corners3coloursB.txt","r");
	FILE *f2 = fopen("8corners3coloursG.txt","r");
	FILE *f3 = fopen("8corners3coloursR.txt","r");
    FILE *f4 = fopen("8corners3coloursY.txt","r");
    FILE *f5 = fopen("12edges3coloursB.txt","r");
    FILE *f6 = fopen("12edges3coloursG.txt","r");
    FILE *f7 = fopen("12edges3coloursR.txt","r");
    FILE *f8 = fopen("12edges3coloursY.txt","r");

	abs1 = read_abstraction_from_file("rubikscube3x3x3-8corners3coloursB.abst");
	map1 = read_state_map(f1);

	abs2 = read_abstraction_from_file("rubikscube3x3x3-8corners3coloursG.abst");
	map2 = read_state_map(f2);

	abs3 = read_abstraction_from_file("rubikscube3x3x3-8corners3coloursR.abst");
	map3 = read_state_map(f3);

    abs4 = read_abstraction_from_file("rubikscube3x3x3-8corners3coloursY.abst");
    map4 = read_state_map(f4);

    ab5 = read_abstraction_from_file("rubikscube3x3x3-12edges3coloursB.abst");
    map5 = read_state_map(f5);

    ab6 = read_abstraction_from_file("rubikscube3x3x3-12edges3coloursG.abst");
    map6 = read_state_map(f6);

    ab7 = read_abstraction_from_file("rubikscube3x3x3-12edges3coloursR.abst");
    map7 = read_state_map(f7);

    ab8 = read_abstraction_from_file("rubikscube3x3x3-12edges3coloursY.abst");
    map8 = read_state_map(f8);

	fclose(f1);
	fclose(f2);
	fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);
    fclose(f7);
    fclose(f8);
}

unsigned heuristic(state_t puzzle_state){
	abstract_state(abs1, &puzzle_state, &abs_state1);
	abstract_state(abs2, &puzzle_state, &abs_state2);
	abstract_state(abs3, &puzzle_state, &abs_state3);
    abstract_state(abs4, &puzzle_state, &abs_state4);
    abstract_state(abs5, &puzzle_state, &abs_state5);
    abstract_state(abs6, &puzzle_state, &abs_state6);
    abstract_state(abs7, &puzzle_state, &abs_state7);
    abstract_state(abs8, &puzzle_state, &abs_state8);

	//maximum = std::max(*state_map_get(map1, &abs_state1), std::max(*state_map_get(map2, &abs_state2), *state_map_get(map3, &abs_state3)))
    maximum = std::max(*state_map_get(map1, &abs_state1), std::max(*state_map_get(map2, &abs_state2), *state_map_get(map3, &abs_state3)));
    maximum = std::max(maximum, *state_map_get(map4, &abs_state4));
    maximum = std::max(maximum, *state_map_get(map5, &abs_state5));
    maximum = std::max(maximum, *state_map_get(map6, &abs_state6));
    maximum = std::max(maximum, *state_map_get(map7, &abs_state7));
    maximum = std::max(maximum, *state_map_get(map8, &abs_state8));

	return (maximum);
}