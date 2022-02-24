#include <iostream>
#include <string>
#include <fstream>
#include "List.h"
#include "BigInteger.h"
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
	ifstream in;
	ifstream out;
	if(argc != 3){
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}

	in.open(argv[1]);
	if(!in.is_open()){
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return(EXIT_FAILURE);
	}

	out.open(argv[2]);
	if(!out.is_open()){
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return(EXIT_FAILURE);
	}
	string str_A = "";
	string read_and_discard = "";
	string str_B = "";
	getline(in, A);
	getline(in, read_and_discard);
	getline(in, B);
	BigInteger A = new BigInteger(str_A);
	BigInteger B = new BigInteger(str_B);
	BigInteger ApB = A+B;
	BigInteger AmB = A-B;
	BigInteger AmA = A-A;
	BigInteger three = new BigInteger("3");
	BigInteger two = new BigInteger("2");
	BigInteger threeAmtwoB = ((three*A)-(two*B));
	BigInteger AB = A*B;
	BigInteger AA = A*A;
	BigInteger BB = B*B;
	BigInteger nine = new BigInteger("9");
	BigInteger sixteen new BigInteger("16");
	BigInteger nineAfourpsixteenBfive = (((((nine*A)*A)*A)*A) + (((((sixteen*B)*B)*B)*B)*B));

	out << A;
	out << B;
	out << ApB;
	out << AmB;
	out << AmA;
	out << threeAmtwoB;
	out << AB;
	out << AA;
	out << BB;
	out << nineAfourpsixteenBfive;

	in.close();
	out.close();
}


