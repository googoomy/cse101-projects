#include <iostream>
#include <string>
#include <iomanip>
#include "List.h"
using namespace std;

#define MAX_LEN 300

void shuffle(List& D){
	List split1;
	List split2;
	int j = D.length() / 2;
	int k = D.length()-j;
	D.moveFront();
	for(int i = 0; i < j; i++){
		split1.insertBefore(D.peekNext());
		D.moveNext();
	}
	for(int i = 0; i < k; i++){
		split2.insertBefore(D.peekNext());
		D.moveNext();
	}
	split1.moveFront();
	split2.moveFront();
	D.moveFront();
	
	//reset D so we can merge the splits
	D.clear();
	for(int i = 0; i < j; i++){
		if(split2.peekNext() != -1){
			D.insertBefore(split2.peekNext());
			split2.moveNext();
		}
		if(split1.peekNext() != -1){
			D.insertBefore(split1.peekNext());
			split1.moveNext();
		}
	}
	if((j+k) % 2 != 0){
		D.insertBefore(split2.peekNext());
	}
	
}

int main(int argc, char * argv[]){
	if(argc != 2){
		cerr << "Usage: " << argv[0] << "<integer>" << endl;
		return(EXIT_FAILURE);
	}
	int n = 0;
	int shuffle_count = 0;
	n = atoi(argv[1]);
	cout << "deck size       shuffle count" << endl;
	cout << "------------------------------" << endl;
	List deck;
	List deck_copy;
	for(int i = 1; i <= n; i++){
		shuffle_count = 0;
		//make the deck with i deck size
		deck.moveFront();
		deck_copy.moveFront();
		for(int j = 0; j < i; j++){
			deck.insertAfter(j);
			deck.moveNext();
			deck_copy.insertAfter(j);
			deck_copy.moveNext();
		}
		shuffle(deck);
		shuffle_count++;
		while(!deck_copy.equals(deck)){
			shuffle(deck);
			shuffle_count++;
		}	
		cout << " " << left << setw(16) << i << right << shuffle_count <<endl;
		deck.clear();
		deck_copy.clear();
	}
}


