$(info $(SHELL))
CC = gcc
CXX = g++
#OPT = -g
OPT = -g -Wall -O3


bin/psvn2c: src/psvn/psvn2c.cpp src/psvn/psvn2c.hpp src/psvn/psvn.cpp src/psvn/psvn.hpp
	$(CXX) $(OPT) src/psvn/psvn2c.cpp src/psvn/psvn.cpp -o $@

clean:
	rm -fr bin/psvn2c bin/*.dSYM *.o *~