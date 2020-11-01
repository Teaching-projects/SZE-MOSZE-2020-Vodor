#!/bin/bash

if test -f output.txt
then
    rm output.txt
fi

for file in test/scenarios/*.json; do
    ./a.out $file >> output.txt
    echo >> output.txt
done