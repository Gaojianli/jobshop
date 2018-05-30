#!/bin/bash
if test -d build
then
    echo "build dir deteced,cleaning.."
    rm -rf build/*
else
    echo "making building directory.."
    mkdir build
fi
export MAKEROOT=`pwd`
cd build
for file in ../src/utils/*
do
    if test -f $file
    then
        gcc -c -O2 -march=native --std=c11 $file -w
    fi
done
ar -rc libjobshop.a *.o
gcc -O2 -march=native --std=c11 "$MAKEROOT/src/main.c" -L. -ljobshop -o "$MAKEROOT/jobshop" -w
cd ..
echo "build finished."
echo "run:./jobshop"
