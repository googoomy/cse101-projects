#James Gu
#jjgu
#Winter2022
#PA4
##Description of Program: This program is an implementation of the Matrix ADT and is written in C. The main program is called Sparse.c and the implementation is in Matrix.c. The Matrix ADT consists of an array of lists with entries. These serve as the rows and columns of the Matrix. Each of these entries have a value assigned to them as well as a column number. The main operations of this program is its sum(), diff(), and product() functions. These functions maniuplate matrices so they can be summed, subtracted, or multiplied.
###Build for Program: List.h: the header file for List.c that layouts the interface, List.c: contains the implementation for the List ADT, ListTest.c: a program to help test the List, Matrix.h: the header file for MAtrix.c that layouts the interface, Matrix.c: contains the implementation for the Matrix ADT, MatrixTest.c: a program to help test the Matrix, Sparse.c: the main for this program, the input is a infile and outputs matrices that underwent various operations from Matrix.c, Makefile: This file compiles the program by typing in make in the command line. README.md: describes the program and build for the program.
####User Guide: The first step to use this program is to use the command make. Then the user can type in ./Sparse <infile> <outfile> so they can view how each matrix operation can manipulate their matrices.
