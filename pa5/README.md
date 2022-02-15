#James Gu
#jjgu
#Winter2022
#PA5
##Description of Program: This program is an implementation of the List ADT and is written in C++. The main program is called Shuffle.cpp and the implementation is in List.cpp. The List ADT consists of nodes that connect to one another from the front of the list to the back of the list. Each of these nodes can have data assigned to them. Additionally each node has a next node and previous node that keeps track of how the nodes allign in the List.
###Build for Program: List.h: the header file for List.cpp that layouts the interface, List.cpp: contains the implementation for the List ADT, ListTest.cpp: a program to help test the List, Shuffle.cpp: the main for this program, the input is an integer that represents how cards are in the deck to be shuffled, Makefile: This file compiles the program by typing in make in the command line. README.md: describes the program and build for the program.
####User Guide: The first step to use this program is to use the command make. Then the user can type in ./Shuffle <integer> so they can view how a deck of cards at each number of cards leading up to their integer can be shuffled.
