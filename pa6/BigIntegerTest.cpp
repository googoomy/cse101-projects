//-----------------------------------------------------------------------------
// James Gu
// jjgu
// pa6
//
//
//
// BigIntegerTest.cpp
// Teester for the BigInteger ADT
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "List.h"
#include "BigInteger.h"

using namespace std;

int main(){
	BigInteger A = BigInteger("123456789");
	BigInteger B = BigInteger("987654321");
	BigInteger C = BigInteger("-123456789");
	
	BigInteger ApB = A+B;
	BigInteger AmB = A-B;
	BigInteger BpA = B+A;
	BigInteger AmA = A-A;
	BigInteger BmA = B-A;
	BigInteger AtB = A*B;

	int booll = A.compare(B);
	cout << ApB << endl;
	cout << AmB << endl;
	cout << BpA << endl;
	cout << AmA << endl;
	cout << BmA << endl;
	cout << AtB << endl;
	
	if(booll == -1){
		cout << "true" << endl;
	}
	
}
