#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

#include "Dictionary.h"

#define MAX_LEN 300

int main(int argc,char * argv[]){
	ifstream in;
	ofstream out;
	
	if(argc != 3){
		cerr << "Usage: " << argv[0] << "<input file> <output file>" << endl;
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
	}

	int line_count = 0;
	string line;
	
	Dictionary D;
	while(getline(in, line)){
		D.setValue(line, line_count);
		line_count++;
	}
	in.clear();
	in.seekg(0, ios::beg);
	string keys[line_count];
	int curr = 0;
	while(in.peek() != EOF){
		getline(in, keys[curr]);
		curr++;
	}
	std::sort(keys, keys + line_count);
	string curr_str = "";
	for(int i = 0; i < line_count; i++){
		curr_str += keys[i] + " : " + to_string(D.getValue(keys[i])) + "\n";
		out << curr_str;
	}
	out << endl;
	string str = "";
	str += D.pre_string();
	string col = " : ";
	size_t j = col.length();
	for(size_t k = str.find(col); k != string::npos; k = str.find(col)){
		str.erase(k, j);
	}
	out << str;


	in.close();
	out.close();
}
