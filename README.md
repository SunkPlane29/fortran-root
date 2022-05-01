# fortran-root
fortran with root to plot graphics

This is more of a helper application that was made with the objective to learn a little about the ROOT framework. This application plots graphics defined in data files, meaning it was made to use the root framework as something like gnuplot. It can help if someone wants to use the root framework in conjuntion with the fortran programming language.

## Instructions

Dependencies
- g++
- root 6.26

The application can be build with the build.sh script, or, if you want to use g++, the command `g++ graph.cpp $(root-config --glibs --cflags --libs) -o bin/graph_app`.

After the application is build you can run the application with the command: `bin/graph_app file1.dat file2.dat (...)`

Then a GUI window will apear showing the graph plotted. The graph can then be saved using the File menu options and Save (you can opt for different file types).

![image](https://user-images.githubusercontent.com/62779977/166152148-95c61bc3-b72e-400e-98d7-5d48eaa46b32.png)

*print showing the example program*
