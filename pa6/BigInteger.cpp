//-----------------------------------------------------------------------------
// BigInteger.cpp
// File for the BigInteger ADT
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"
#include "BigInteger.h"

int power = 9;
long base = 1000000000;

   // Class Constructors & Destructors ----------------------------------------

   // BigInteger()
   // Constructor that creates a new BigInteger in the zero state: 
   // signum=0, digits=().
BigInteger::BigInteger(){
	signum = 0;
	digits = new List();
}

   // BigInteger()
   // Constructor that creates a new BigInteger from the string s.
   // Pre: s is a non-empty string consisting of (at least one) base 10 digit
   // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
	if(s.length() == 0){
		throw std::invalid_argument("BigInteger: Contructor: empty string");
	}
	if(s[0] != '+' && s[0] != '-' && !std::isdigit(s[0])){
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
	}
	bool all_zeroes = true;
	int num_digits = 0;	
	for(int i = 1; i <= s.length(); i++){
		num_digits++;
		if(!std::isdigit(s[i])){
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
		int curr_char = atoi(s[i]);
		if(curr_char != 0){
			all_zeroes = false;
		}
	}
	if(all_zeroes){
		signum = 0;
		digits = new List();
		return;
	}
	if(s[0] == '-'){
		signum = -1;
	}else{
		signum = 1;
	}
	std::string temp_s = "";
	digits = newList();
	digits.moveFront();
	//ceiling of num_digits/power and num_digits/num_entries without math.h
	int num_entries = (num_digits/power) + ((num_digits % power) != 0);
	int num_digits_per_entry = (num_digits/num_entries) + ((num_digits % num_entries) != 0);
	int curr = 0;
	if(s[0] == '-' || s[0] == '+'){
		curr+=1;
	}
	for(int i = 0; i < num_entries; i++){
		for(int j = 0; j < num_digits_per_entry; j++){
			temp_s += s[curr];
		}
		long curr_num = atol(temp_s);
		digits.insertBefore(curr_num);
		digits.moveNext();
	}
	//remove leading zeros
	digits.moveBack();
	while(digits.get()==0){
		digits.deleteBack();
		digits.moveBack();	
	}	
	

	
}

   // BigInteger()
   // Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
	this->signum = N.signum;
	this->digits = N.digits;
}

   // Optional Destuctor
   // ~BigInteger()
   // ~BigInteger();


   // Access functions --------------------------------------------------------

   // sign()
   // Returns -1, 1 or 0 according to whether this BigInteger is positive, 
   // negative or 0, respectively.
int BigInteger::sign() const{
	return signum;
}

   // compare()
   // Returns -1, 1 or 0 according to whether this BigInteger is less than N,
   // greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
	if(sign() > N.sign()){
		return 1;
	}
	if(sign() < N.sign()){
		return -1;
	}
	if(sign() == 1 && N.sign() == 1){		
		if(length(this->digits) > length(N.digits)){
			return 1;
		}
		if(length(this->digits) < length(N.digits)){
			return -1;
		}
	}
	if(sign() == -1 && N.sign() == -1){		
		if(length(this->digits) > length(N.digits)){
			return -1;
		}
		if(length(this->digits) < length(N.digits)){
			return 1;
		}
	}
	if(signum == 0 && N.signum == 0){
		return 0;
	}
	digits.moveFront();
	N->digits.moveFront();
	while(digits.index() != -1 && N.digits.index() != -1){
		if(sign() == 1 && N.sign() == 1){
			if(digits.get() > N->digits.get()){
				return 1;
			}
			if(digits.get() < N->digits.get()){
				return -1;
			}
		}
		if(sign() == -1 && N.sign() == -1){
			if(digits.get() > N->digits.get()){
				return -1;
			}
			if(digits.get() < N->digits.get()){
				return 1;
			}
		}
		digits.moveNext();
		N->digits.moveNext();
	}
	return 0;
}


   // Manipulation procedures -------------------------------------------------

   // makeZero()
   // Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
	digits.clear();
	signum = 0;
}

   // negate()
   // If this BigInteger is zero, does nothing, otherwise reverses the sign of 
   // this BigInteger positive <--> negative. 
void BigInteger::negate(){
	signum *= -1;
}

void normalizeList(List& L){
	List norm;
	L.moveFront();
	//make the terms negative if the are below base.
	//example: 21+71= 92 and when normalizing it you need to add 100 instead so to keep it as subtracting 100 we willmake 92 negative and make it positive later
	while(L.index() != -1){
		if(L.get() < base){
			L.set(L.get()*-1);
		}
		L.moveNext();
	}
	//normalize each value by subtracting 100
	L.moveBack();
	long carry = 0;
	while(L.index() != -1){
		L.set(L.get()+carry-base);
		if(L.get() < 0){
			L.set(L.get()*-1);
		}
		if(L.get() < base){
			carry = 1;
		}
		if(L.get() > base){
			L.set(L.get()%base);	
			carry = 0;
		}
		L.movePrev();
	}
	//if there is a leftover carry by the end
	if(carry != 0){
		L.moveFront();
		L.insertBefore(carry);
	}
}

void sumList(List& S, List A, List B, int sgn){
	if(sgn == 1){
		
	}
	if(sgn == -1){
		
	}
}

   // BigInteger Arithmetic operations ----------------------------------------

   // add()
   // Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
	if(N.sign() == 0){
		BigInteger CPY = BigInteger(this);
		return CPY;
	}
	if(this.sign() == 0){
		BigInteger CPY = BigInteger(N);
		return CPY;
	}
	BigInteger sum;
	int sgn = 1;
	if(N.sign() == -1 && this.sign() == 1){
		sgn = -1;
		N.negate();
		sumList(sum->digits, this->digits, N->digits, sgn);
		if(this.compare(N) == -1){
			sum->signum = -1;
		}else if(this.compare(N) == 1){
			sum->signum = 1;
		}else{
			sum->signum = 0;
		}
		N.negate();
	}else if(N.sign() == 1 && this.sign() == -1){
		sgn = -1;
		this.negate();
		sumList(sum->digits, N->digits, this->digits, sgn);
		if(this.compare(N) == -1){
			sum->signum = 1;
		}else if(this.compare(N) == 1){
			sum->signum = -1;
		}else{
			sum->signum = 0;
		}
		this.negate();
	}else{
		sgn = 1;
		sumList(sum->digits, this->digits, N->digits, sgn);
		if(N.sign() == -1){
			sum->signum = -1;
		}else{
			sum->signum = 1;
		}	
	}
	return sum;
}

   // sub()
   // Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
	N.negate();
	BigInteger diff;
	diff = this.BigInteger::add(N);
	N.negate();
	return diff;
}

   // mult()
   // Returns a BigInteger representing the product of this and N. 
   BigInteger mult(const BigInteger& N) const;


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this BigInteger consisting of its
   // base 10 digits. If this BigInteger is negative, the returned string 
   // will begin with a negative sign '-'. If this BigInteger is zero, the
   // returned string will consist of the character '0' only.
   std::string to_string();


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of N into stream.
   friend std::ostream& operator<<( std::ostream& stream, BigInteger N );

   // operator==()
   // Returns true if and only if A equals B. 
   friend bool operator==( const BigInteger& A, const BigInteger& B );

   // operator<()
   // Returns true if and only if A is less than B. 
   friend bool operator<( const BigInteger& A, const BigInteger& B );

   // operator<=()
   // Returns true if and only if A is less than or equal to B. 
   friend bool operator<=( const BigInteger& A, const BigInteger& B );

   // operator>()
   // Returns true if and only if A is greater than B. 
   friend bool operator>( const BigInteger& A, const BigInteger& B );

   // operator>=()
   // Returns true if and only if A is greater than or equal to B. 
   friend bool operator>=( const BigInteger& A, const BigInteger& B );

   // operator+()
   // Returns the sum A+B. 
   friend BigInteger operator+( const BigInteger& A, const BigInteger& B );

   // operator+=()
   // Overwrites A with the sum A+B. 
   friend BigInteger operator+=( BigInteger& A, const BigInteger& B );

   // operator-()
   // Returns the difference A-B. 
   friend BigInteger operator-( const BigInteger& A, const BigInteger& B );

   // operator-=()
   // Overwrites A with the difference A-B. 
   friend BigInteger operator-=( BigInteger& A, const BigInteger& B );

   // operator*()
   // Returns the product A*B. 
   friend BigInteger operator*( const BigInteger& A, const BigInteger& B );

   // operator*=()
   // Overwrites A with the product A*B. 
   friend BigInteger operator*=( BigInteger& A, const BigInteger& B );

};

