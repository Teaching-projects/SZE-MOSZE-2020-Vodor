#!/bin/bash

if test -f output.txt
then
    rm output.txt
fi

cat test/scn1.txt | ./runGame scenarios/scenario1.json >> output.txt
cat test/scn5.txt | ./runGame scenarios/scenario5.json >> output.txt