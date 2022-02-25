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
	string str_A;
	string read_and_discard;
	string str_B;
	getline(in, str_A);
	getline(in, read_and_discard);
	getline(in, str_B);
	BigInteger A = BigInteger(str_A);
	BigInteger B = BigInteger(str_B);
	BigInteger ApB = A+B;
	BigInteger AmB = A-B;
	BigInteger AmA = A-A;
	BigInteger three = BigInteger("3");
	BigInteger two = BigInteger("2");
	BigInteger threeAmtwoB = ((three*A)-(two*B));
	BigInteger AB = A*B;
	BigInteger AA = A*A;
	BigInteger BB = B*B;
	BigInteger nine = BigInteger("9");
	BigInteger sixteen = BigInteger("16");
	BigInteger nineAfourpsixteenBfive = (((((nine*A)*A)*A)*A) + (((((sixteen*B)*B)*B)*B)*B));
/*	
	A << "\n" << endl;
	B << "\n" << endl;
	ApB << "\n" << endl;
	AmB << "\n" << endl;
	AmA << "\n" << endl;
	threeAmtwoB << "\n" << endl;
	AB << "\n" << endl;
	AA << "\n" << endl;
	BB << "\n" << endl;
	nineAfourpsixteenBfive << "\n" << endl;
*/
	
	out << A << "\n" << endl;
	out << B << "\n" << endl;
	out << ApB << "\n" << endl;
	out << AmB << "\n" << endl;
	out << AmA << "\n" << endl;
	out << threeAmtwoB << "\n" << endl;
	out << AB << "\n" << endl;
	out << AA << "\n" << endl;
	out << BB << "\n" << endl;
	out << nineAfourpsixteenBfive << "\n" << endl;

	in.close();
	out.close();
}


