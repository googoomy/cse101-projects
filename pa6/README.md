#James Gu
#jjgu
#Winter2022
#PA6
##Description of Program: This program is an implementation of the BigInteger ADT and is written in C++. The main program is called Arithmetic.cpp and the implementation is in BigInteger.cpp. The BigInteger ADT consists of data in a list that represents digits or multiple digits of a number. Each of these entries has the same number of digits as the global "power" variable. Additionally the list is sorted by having the Least Significant Digit at the front so the inidices match up with the one's place, ten's place and so on.
###Build for Program: List.h: the header file for List.cpp that layouts the interface, List.cpp: contains the implementation for the List ADT, ListTest.cpp: a program to help test the List, BigInteger.h: the header file for BigInteger.cpp that layouts the interface, BigInteger.cpp: contains the implementation for the BigInteger ADT, BigIntegerTest.cpp: a program to help test the BigInteger, Arithmetic.cpp: the main for this program, the input is an integer that represents how cards are in the deck to be shuffled, Makefile: This file compiles the program by typing in make in the command line. README.md: describes the program and build for the program.
####User Guide: The first step to use this program is to use the command make. Then the user can type in ./Arithmetic <infile> <outfile> so they can view how a BigIntegers are operated on using this BigInteger ADT. There's addition, subtraction, and multiplication available. The infile needs to be the integer the user wants followed by a blank line and the third line being the second integer.