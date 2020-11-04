#!/bin/bash

if test -f output.txt
then
    rm output.txt
fi

for file in test/scenarios/*.json; do
    ./runGame $file >> output.txt
done