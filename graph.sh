#!/bin/bash

gfortran graph.f90 -o graph.out
./graph.out

mkdir -p bin

g++ graph.cpp $(root-config --glibs --cflags --libs) -o bin/graph_app
bin/graph_app graph1.dat graph2.dat
