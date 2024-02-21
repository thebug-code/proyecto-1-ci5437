# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=0 --bwd_history_len=0

psvn2c_core.c:
	cp ../../../src/psvn/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../../src/psvn/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../../src/psvn/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

priority_queue.hpp:
	cp ../../../src/search-algorithms/search_tree/priority_queue.hpp ./priority_queue.hpp

node.hpp:
	cp ../../../src/search-algorithms/node.hpp ./node.hpp

%.succ: %.c ../../../global/succ.c
	$(CC) $(OPT) ../../../global/succ.c -include $< -o $@
	rm -f $*.c

%.dist: %.c ../../../global/dist.cpp
	$(CXX) $(OPT) ../../../global/dist.cpp -include $< -o $@
	rm -f $*.c

%.distSummary: %.c ../../../global/distSummary.cpp
	$(CXX) $(OPT) ../../../global/distSummary.cpp -include $< -o $@
	rm -f $*.c

abstractor:
	$(CXX) $(OPT) ../../../src/psvn/abstractor.cpp ../../../src/psvn/psvn.cpp -o $@

%.pdb: abstractor
	@rm -f `dirname $*`-`basename $*`.{abst,pdb,psvn}
	./abstractor ../`dirname $*`.psvn `dirname $*`-`basename $*` < `basename $*`.txt
	make -f makePDB.mk `dirname $*`-`basename $*`.distSummary
	echo Calculating `dirname $*`-`basename $*.pdb` ...
	@./`dirname $*`-`basename $*`.distSummary `dirname $*`-`basename $*`.pdb

%.dist_pdb: %.c ../../../global/dist_pdb.cpp
	$(CXX) $(OPT) ../../../global/dist_pdb.cpp -include $< -o $@
	rm -f $*.c

#%.idaStar: %.c ../../../src/search-algorithms/ida_star.cpp priority_queue.hpp node.hpp
#	$(CXX) $(OPT) ../../../Global/idaStar.cpp -include $< -include 15-puzzle_PDB.cpp -o $@

%.a_star: %.c ../../../src/search-algorithms/a_star.cpp priority_queue.hpp node.hpp
	$(CXX) $(OPT) ../../../src/search-algorithms/a_star.cpp -include $< -include 15_puzzles_pdb.cpp -o $@

.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~
