OBJS := Parser.o Game.o Unit.o main.o
CFLAGS := -Wall -Werror -std=c++17
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
.PHONY: cppcheck cppcheckup valgrind diff doc buildunittest unittest
tests: runGame cppcheck cppcheckup valgrind diff

runGame: $(OBJS)
	$(RUN) $(CFLAGS) -o runGame $(OBJS)

Parser.o: Parser.cpp Parser.h
	$(RUN) $(CFLAGS) -c Parser.cpp
	
Game.o: Game.cpp Game.h
	$(RUN) $(CFLAGS) -c Game.cpp

Unit.o: Unit.cpp Unit.h
	$(RUN) $(CFLAGS) -c Unit.cpp

main.o: main.cpp Game.h
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

doc:
	doxygen doxconf

buildunittest:
	cmake $(SUBDIR)/$(CMAKEOBJ) /
	$(MAKE) -C $(SUBDIR)

unittest: buildunittest
	$(SUBDIR)/parserTest