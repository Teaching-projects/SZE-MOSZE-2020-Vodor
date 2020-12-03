OBJS := JSON.o Hero.o Monster.o Unit.o main.o Map.o Game.o SVGRenderer.o TextRenderer.o
CFLAGS := -Wall -Werror -std=c++17
RUN := g++-9
SCA := cppcheck
SCAOBJS := JSON.cpp Hero.cpp Monster.cpp Unit.cpp main.cpp Map.cpp Game.cpp SVGRenderer.cpp TextRenderer.cpp
SCAFLAGS := --enable=warning --error-exitcode=1
SCAUPFLAGS := --enable=all --output-file=cppreport.txt
MEMCHECK := valgrind
MEMCHECKOBJS := cat test/scn1.txt | ./runGame scenarios/scenario1.json
MEMCHECKFLAGS := --error-exitcode=1 --leak-check=full
DIFF := diff
DIFFOBJS := output.txt test/good_output.txt
DIFFSVGOBSERVEROBJS := observerOutput.svg test/scn1ObsOut.svg
DIFFSVGCHARACTEROBJS := characterOutput.svg test/scn1CharOut.svg
CMAKEOBJ := CMakeLists.txt
SUBDIR := test

.DEFAULT_GOAL: runGame
.PHONY: sca scaup memcheck diff doc buildunittest unittest
tests: runGame sca scaup memcheck diff

runGame: $(OBJS)
	$(RUN) $(CFLAGS) -o runGame $(OBJS)

JSON.o: JSON.cpp JSON.h
	$(RUN) $(CFLAGS) -c JSON.cpp
	
Unit.o: Unit.cpp Unit.h JSON.h Damage.h
	$(RUN) $(CFLAGS) -c Unit.cpp

Monster.o: Monster.cpp Hero.h Monster.h Unit.h JSON.h Damage.h
	$(RUN) $(CFLAGS) -c Monster.cpp

Hero.o: Hero.cpp Monster.h Hero.h Unit.h JSON.h Damage.h
	$(RUN) $(CFLAGS) -c Hero.cpp

main.o: main.cpp Monster.h Hero.h Unit.h JSON.h Damage.h Game.h Renderer.h TextRenderer.h SVGRenderer.h
	$(RUN) $(CFLAGS) -c main.cpp

Map.o: Map.cpp Map.h
	$(RUN) $(CFLAGS) -c Map.cpp

Game.o: Game.cpp Game.h Map.h Monster.h Hero.h Unit.h JSON.h Damage.h Renderer.h
	$(RUN) $(CFLAGS) -c Game.cpp

SVGRenderer.o: SVGRenderer.cpp SVGRenderer.h Renderer.h Game.h Map.h Monster.h Hero.h Unit.h JSON.h Damage.h
	$(RUN) $(CFLAGS) -c SVGRenderer.cpp

TextRenderer.o: TextRenderer.cpp TextRenderer.h Renderer.h Game.h Map.h Monster.h Hero.h Unit.h JSON.h Damage.h
	$(RUN) $(CFLAGS) -c TextRenderer.cpp

sca:
	$(SCA) $(SCAOBJS) $(SCAFLAGS)  

scaup:
	$(SCA) $(SCAOBJS) $(SCAUPFLAGS)

memcheck: 
	$(MEMCHECK) $(MEMCHECKFLAGS) $(MEMCHECKOBJS)

diff:
	 $(DIFF) log.txt test/good_log.txt && $(DIFF) $(DIFFSVGOBSERVEROBJS) && $(DIFF) $(DIFFSVGCHARACTEROBJS) && ./run_test.sh && $(DIFF) $(DIFFOBJS)

doc:
	doxygen doxconf

buildunittest:
	cmake $(SUBDIR)/$(CMAKEOBJ) /
	$(MAKE) -C $(SUBDIR)

unittest: buildunittest
	$(SUBDIR)/unitTest
