OBJS := Parser.o Game.o Unit.o main.o
CLFAGS := -Wall -Werror -std=c++17
RUN := g++

CPPCHCK := cppcheck
CPPCHCKOBJS := Parser.cpp Game.cpp Unit.cpp main.cpp
CPPCHCKFLAGS := --enable=warning --error-exitcode=1
CPPCHCKUPFLAGS := --enable=all --output-file=cppreport.txt
VALGRINDOBJS := ./runGame test/units/unit1.json test/units/unit2.json 
VALGRINDFLAGS := --error-exitcode=1 --leak-check=full
DIFFOBJS := output.txt test/units/good_output.txt
CMAKEOBJ := CMakeLists.txt
SUBDIR := test

.DEFAULT_GOAL: runGame
.PHONY: cppcheck cppcheckup valgrind diff doxygen buildunittest unittest
tests: runGame cppcheck cppcheckup valgrind diff

runGame: $(OBJS)
	$(RUN) $(CFLAGS) -o runGame $(OBJS)

Parser.o: Parser.cpp
	$(RUN) $(CFLAGS) -c Parser.cpp

Game.o: Game.cpp
	$(RUN) $(CFLAGS) -c Game.cpp

Unit.o: Unit.cpp
	$(RUN) $(CFLAGS) -c Unit.cpp

main.o: main.cpp
	$(RUN) $(CFLAGS) -c main.cpp

cppcheck:
	$(CPPCHCK) $(CPPCHCKOBJS) $(CPPCHCKFLAGS)  

cppcheckup:
	$(CPPCHCK) $(CPPCHCKOBJS) $(CPPCHCKUPFLAGS)

valgrind: 
	valgrind $(VALGRINDFLAGS) $(VALGRINDOBJS)

diff:
	./run_test.sh /
	diff $(DIFFOBJS)

doxygen:
	doxygen doxconf

buildunittest:
	cmake $(SUBDIR)/$(CMAKEOBJ) /
	$(MAKE) -C $(SUBDIR)

unittest: buildunittest
	$(SUBDIR)/parserTest