#!/bin/bash

if test -f output.txt
then
    rm output.txt
fi

cat test/scenarios/scn1.txt | ./runGame test/scenarios/scenario1.json >> output.txt
cat test/scenarios/scn2.txt | ./runGame test/scenarios/scenario2.json >> output.txt