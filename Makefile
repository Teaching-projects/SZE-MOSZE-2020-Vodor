OBJS := Parser.o Game.o Unit.o main.o
CFLAGS := -Wall -Werror -std=c++17
RUN := g++

SCA := cppcheck
SCAOBJS := Parser.cpp Game.cpp Unit.cpp main.cpp
SCAFLAGS := --enable=warning --error-exitcode=1
SCAUPFLAGS := --enable=all --output-file=cppreport.txt
MEMCHECK := valgrind
MEMCHECKOBJS := ./runGame test/units/unit1.json test/units/unit2.json 
MEMCHECKFLAGS := --error-exitcode=1 --leak-check=full
DIFFOBJS := output.txt test/units/good_output.txt
CMAKEOBJ := CMakeLists.txt
SUBDIR := test

.DEFAULT_GOAL: runGame
.PHONY: sca scaup memcheck diff doc buildunittest unittest
tests: runGame sca scaup memcheck diff

runGame: $(OBJS)
	$(RUN) $(CFLAGS) -o runGame $(OBJS)

Parser.o: Parser.cpp Parser.h
	$(RUN) $(CFLAGS) -c Parser.cpp
	
Unit.o: Unit.cpp Unit.h Parser.h
	$(RUN) $(CFLAGS) -c Unit.cpp

Game.o: Game.cpp Game.h Unit.h Parser.h
	$(RUN) $(CFLAGS) -c Game.cpp

main.o: main.cpp Game.h Unit.h Parser.h
	$(RUN) $(CFLAGS) -c main.cpp

sca:
	$(SCA) $(SCAOBJS) $(SCAFLAGS)  

scaup:
	$(SCA) $(SCAOBJS) $(SCAUPFLAGS)

memcheck: 
	$(MEMCHECK) $(MEMCHECKFLAGS) $(MEMCHECKOBJS)

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