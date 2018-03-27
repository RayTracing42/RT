# RayTracer project for 42

## Build instructions:

* mac: just `make` and it works
* linux: install the SDL2 library then `make debug-linux`
* windows: install a linux distribution on your computer.

## Usage:

./rt [path/to/the/map.xml] [number_of_threads]

For a quad core processor 128 threads seems to be the fastest.
All the pretty maps are in the folder "scenes", and all the tests maps are in the folder "tests" and its sub-folders.

Press A to launch the AntiAliasing (SSAAX16), press S to take a screenshot.


Check out the demo video!
https://www.youtube.com/watch?v=p3DPezetaYE

## About the code:

The program is written in C and uses the SDL2 as the graphic library. The code is object oriented, each class being defined with the C `struct`. Even though each struct is not necessarily a class, all are written with the OOP concepts in mind. There is not much inheritance between classes, only the `t_object` and `t_light` have children, and both use polymorphism in some parts of the code.
For a view of the whole structure check the file structures.h (sorry all the commentaries are in french).

No "mathematical" library was used, other than the standard <math.h>, everything is an implementation of existing algorithms or our own algorithms.
