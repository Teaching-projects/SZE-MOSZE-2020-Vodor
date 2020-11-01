OBJS := JSON.o Hero.o Monster.o Unit.o main.o
CFLAGS := -Wall -Werror -std=c++17
RUN := g++-10

SCA := cppcheck
SCAOBJS := JSON.cpp Hero.cpp Monster.cpp Unit.cpp main.cpp
SCAFLAGS := --enable=warning --error-exitcode=1
SCAUPFLAGS := --enable=all --output-file=cppreport.txt
MEMCHECK := valgrind
MEMCHECKOBJS := ./runGame test/scenarios/scenario1.json 
MEMCHECKFLAGS := --error-exitcode=1 --leak-check=full
DIFFOBJS := output.txt test/units/good_output.txt
CMAKEOBJ := CMakeLists.txt
SUBDIR := test

.DEFAULT_GOAL: runGame
.PHONY: sca scaup memcheck diff doc buildunittest unittest
tests: runGame sca scaup memcheck diff

runGame: $(OBJS)
	$(RUN) $(CFLAGS) -o runGame $(OBJS)

JSON.o: JSON.cpp JSON.h
	$(RUN) $(CFLAGS) -c JSON.cpp
	
Unit.o: Unit.cpp Unit.h JSON.h
	$(RUN) $(CFLAGS) -c Unit.cpp

Monster.o: Monster.cpp Hero.h Unit.h JSON.h
	$(RUN) $(CFLAGS) -c Monster.cpp

Hero.o: Hero.cpp Monster.h Unit.h JSON.h
	$(RUN) $(CFLAGS) -c Hero.cpp

main.o: main.cpp Monster.h Hero.h JSON.h
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
	$(SUBDIR)/unitTest