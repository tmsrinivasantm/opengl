#!/bin/bash
INPUT="$1"
if  [ -z $INPUT ]; then
    cd build || exit
    make
    ./opengl
elif [ $INPUT = "val" ]; then
    cd build || exit
    make
    valgrind ./opengl
    exit 0
elif [ $INPUT = "gdb" ]; then
    cd build || exit
    make
    gdb ./opengl
    exit 0
fi
