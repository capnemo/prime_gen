#!/bin/bash

echo "running totals test"
./test_totals.sh > totals.out
dx=$(diff totals.out totals.good)
if [[ $dx == "" ]]
then
    echo "totals test passed"
    rm totals.out
else
    echo "totals test FAILED"
    echo $dx
fi

echo "running file test"
unzip  p8.zip
../prime_gen 8 -f p8.out
dx=$(diff p8.out p8.good)
if [[ $dx == "" ]]
then 
    echo "file test has passed"
    rm p8.out
else
    echo "file test has FAILED"
fi
rm p8.good
