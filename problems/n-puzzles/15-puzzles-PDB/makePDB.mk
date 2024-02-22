# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.
CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=0 --bwd_history_len=0
ROOTPATH=../../..

psvn2c_core.c:
	cp ${ROOTPATH}/src/psvn/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ${ROOTPATH}/src/psvn/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ${ROOTPATH}/src/psvn/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	${ROOTPATH}/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

priority_queue.hpp:
	cp ${ROOTPATH}/src/search-algorithms/search_tree/priority_queue.hpp ./priority_queue.hpp

node.hpp:
	cp ${ROOTPATH}/search-algorithms/node.hpp ./node.hpp


%.succ: %.c ${ROOTPATH}/global/succ.c
	$(CC) $(OPT) ${ROOTPATH}/psvn/global/succ.c -include $< -o $@
	rm -f $*.c

%.dist: %.c ${ROOTPATH}/global/dist.cpp
	$(CXX) $(OPT) ${ROOTPATH}/global/dist.cpp -include $< -o $@
	rm -f $*.c

%.distSummary: %.c ${ROOTPATH}/global/distSummary.cpp
	$(CXX) $(OPT) ${ROOTPATH}/global/distSummary.cpp -include $< -o $@
	rm -f $*.c

abstractor:
	$(CXX) $(OPT) ${ROOTPATH}/src/psvn/abstractor.cpp ${ROOTPATH}/src/psvn/psvn.cpp -o $@

%.pdb: abstractor
	# Copiar el archivo psvn a la carpeta actual (15-puzzles.psvn)
	@cp ../`dirname $*`.psvn `dirname $*`.psvn
	@rm -f `dirname $*`-`basename $*`.{abst,pdb,psvn}
	./abstractor `dirname $*`.psvn `dirname $*`-`basename $*` < `basename $*`.txt
	make -f makePDB.mk `dirname $*`-`basename $*`.distSummary
	echo Calculating `dirname $*`-`basename $*.pdb` ...
	@./`dirname $*`-`basename $*`.distSummary `dirname $*`-`basename $*`.pdb

%.dist_pdb: %.c ${ROOTPATH}/global/dist_pdb.cpp
	$(CXX) $(OPT) ${ROOTPATH}/global/dist_pdb.cpp -include $< -o $@
	rm -f $*.c

# %.idaStar: %.c ../../../Global/idaStar.cpp priority_queue.hpp node.hpp
# 	$(CXX) $(OPT) ../../../Global/idaStar.cpp -include $< -include 15-puzzle_PDB.cpp -o $@

%.aStar: %.c ${ROOTPATH}/src/search-algorithms/a_star.cpp priority_queue.hpp node.hpp
	$(CXX) $(OPT) ${ROOTPATH}/src/search-algorithms/a_star.cpp -include $< -include heuristics.cpp -o $@

.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary *.dist_pdb psvn2c_core.c psvn2c_state_map.c *.abst *.pdb *.psvn psvn2c_abstraction.c abstractor *.dSYM *.o *~
