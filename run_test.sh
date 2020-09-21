#!/bin/bash

if test -f units/output.txt
then
    rm units/output.txt
fi

for file1 in units/*.json; do
    for file2 in units/*.json; do
        if [ $file2 != $file1 ]
        then
            ./a.out $file1 $file2 >> units/output.txt
            echo >> units/output.txt
        fi
    done
done