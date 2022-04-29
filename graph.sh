#!/bin/bash

gfortran graph.f90 -o graph.out
./graph.out

g++ graph.cpp $(root-config --glibs --cflags --libs) -o graph_app
./graph_app
