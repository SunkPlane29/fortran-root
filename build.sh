#!/bin/bash

mkdir -p bin

g++ graph.cpp $(root-config --glibs --cflags --libs) -o bin/graph_app
