CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
#PSVNOPT = --no_state_map --no_abstraction --no_backwards_moves --history_len=0
PSVNOPT = --state_map --backwards_moves --history_len=0
#PSVNOPT2 = #--fwd_history_len=3 --bwd_history_len=0  --backwards_moves --state_map
ROOTPATH = ../../..

all: towersofhanoi4-12.ucs towersofhanoi4-14.ucs towersofhanoi4-18.ucs

psvn2c_core.c:
	cp $(ROOTPATH)/src/psvn/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp $(ROOTPATH)/src/psvn/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp $(ROOTPATH)/src/psvn/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: ../%.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	$(ROOTPATH)/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	#rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.ucs: %.c $(ROOTPATH)/src/search-algorithms/search_tree/ucs.cpp
	$(CXX) $(OPT) $(ROOTPATH)/src/search-algorithms/search_tree/ucs.cpp -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.ucs *.c *.dSYM *.o *~

cleanall: clean
	rm -fr *.ucs
