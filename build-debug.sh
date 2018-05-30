#!/bin/bash
if test -d build
then
echo "build dir deteced,cleaning.."
rm -rf build/*
else
mkdir build
fi
export MAKEROOT=`pwd`
cd build
for file in ../src/utils/*
do
    if test -f $file
    then
    gcc -c  -g --std=c11 $file -Wall
    fi
done
ar -rc libjobshop.a *.o
gcc -g  --std=c11 "$MAKEROOT/src/main.c" -L. -ljobshop -o "$MAKEROOT/jobshop" -Wall
cd ..
echo "build finished."
echo "run:./jobshop"
