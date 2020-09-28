#!/bin/bash

if test -f output.txt
then
    rm output.txt
fi

for file1 in units/*.json; do
    for file2 in units/*.json; do
        if [ $file1 != $file2 ]
        then
            ./a.out $file1 $file2 >> output.txt
            echo >> output.txt
        fi
    done
done