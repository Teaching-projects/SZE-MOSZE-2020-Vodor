OBJS := Parser.o Game.o Unit.o main.o
CLFAGS := -Wall -Werror -std=c++17
RUN := g++

CPPCHCK := cppcheck
CPPCHCKOBJS := Parser.cpp Game.cpp Unit.cpp main.cpp
CPPCHCKFLAGS := --enable=warning --error-exitcode=1
CPPCHCKUPFLAGS := --enable=all --output-file=cppreport.txt

all: runGame cppcheck cppcheckup

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