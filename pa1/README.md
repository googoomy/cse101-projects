#James Gu
#jjgu
#Winter2022
#PA1
##Description of Program: This program is an implementation of the List ADT and is written in C. The main program is called Lex.c and the implementation is in List.c. The List ADT consists of nodes that connect to one another from the front of the list to the back of the list. Each of these nodes can have data assigned to them. Additionally each node has a next node and previous node that keeps track of how the nodes allign in the List. 
###Build for Program: List.h: the header file for List.c that layouts the interface, List.c: contains the implementation for the List ADT, ListClient.c: a program to help test the List, Lex.c: the main for this program, the input is a infile and outputs a sorted List into the outfile, Makefile: This file compiles the program by typing in make in the command line. README.md: describes the program and build for the program.
####User Guide: The first stop to use this program is to use the command make. Then the user can type in ./Lex <infile> <outfile> so they can sort the elements in the infile and output them to the outfile. 
