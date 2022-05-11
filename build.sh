#!/bin/bash

GXX=$1

if [$GXX = ""]
then
    GXX="g++"
fi

mkdir -p bin

$GXX graph.cpp $(root-config --glibs --cflags --libs) -o bin/graph_app
