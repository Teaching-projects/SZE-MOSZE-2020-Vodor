#!/bin/bash

if test -f output.txt
then
    rm output.txt
fi

for file1 in test/units/*.json; do
    for file2 in test/units/*.json; do
        if [ $file1 != $file2 ]
        then
            ./runGame $file1 $file2 >> output.txt
            echo >> output.txt
        fi
    done
done