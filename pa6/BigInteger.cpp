//-----------------------------------------------------------------------------
// James Gu
// jjgu
// pa6
//
//
//
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
	digits = List();
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
		//std::cerr << "hi";
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
	}
	bool all_zeroes = true;
	int num_digits = 0;	
	for(size_t j = 1; j < s.length(); j++){
		num_digits++;
		if(!std::isdigit(s[j])){
			//std::cerr << "bye";
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
		char dgt = s[j];
		int curr_char = atoi(&dgt);
		if(curr_char != 0){
			all_zeroes = false;
		}
	}
	if(all_zeroes){
		signum = 0;
		digits = List();
		return;
	}
	if(s[0] == '-'){
		signum = -1;
	}else{
		signum = 1;
	}
	std::string temp_s = "";
	digits = List();
	/*
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
			curr+=1;
		}
		long curr_num = stol(temp_s, nullptr, 10);
		digits.insertAfter(curr_num);
		//digits.moveNext();
		temp_s = "";
	}
	if(curr < (int)(s.length())){
		for(int j = 0; j < num_digits_per_entry; j++){
			temp_s += s[curr];
			curr+=1;
			if(curr >= (int)(s.length())){
				break;
			}
		}
		long curr_num = stol(temp_s, nullptr, 10);
		digits.insertAfter(curr_num);
	}
*/
	digits.moveBack();
	//ceiling of num_digits/power and num_digits/num_entries without math.h
	int num_entries = (num_digits/power) + ((num_digits % power) != 0);
	int num_digits_per_entry = (num_digits/num_entries) + ((num_digits % num_entries) != 0);
	int curr = s.length();
	std::string s_c = s;
	if(s[0] != '-' && s[0] != '+'){
		s_c.insert(0, "-");
	}
	bool break_called = false;
	for(int i = 0; i < num_entries; i++){
		for(int j = 0; j < num_digits_per_entry; j++){
			if(s_c[curr] == '-' || s_c[curr] == '+'){
				break_called = true;
				break;
			}
			/*
			std::string char_to_str = "" + s_c[curr];
			temp_s.insert(0, char_to_str);
			*/
			temp_s += s_c[curr];
			curr-=1;
		}
		for(int k = 0; k < (int)(temp_s.length() / 2); k++){
			std::swap(temp_s[k], temp_s[temp_s.length() - k - 1]);
		}
		for(int k = 0; k < (int)(temp_s.length()); k++){
			if(!std::isdigit(temp_s[k])){
				temp_s.erase(k);		
			}
		}
		long curr_num = stol(temp_s, nullptr, 10);
		digits.insertBefore(curr_num);
		//digits.moveNext();
		//digits.moveBack();
		temp_s = "";
		if(break_called){
			break;
		}
	}
	if(curr > 0){
		for(int j = 0; j < num_digits_per_entry; j++){
			if(s_c[curr] == '-' || s_c[curr] == '+'){
				break_called = true;
				break;
			}
			/*
			std::string char_to_str = "" + s_c[curr];
			temp_s.insert(0, char_to_str);
			*/
			temp_s += s_c[curr];
			curr-=1;
			if(curr <= 0){
				break;
			}
			if(break_called){
				break;
			}
		}
		for(int k = 0; k < (int)(temp_s.length() / 2); k++){
			std::swap(temp_s[k], temp_s[temp_s.length() - k - 1]);
		}
		long curr_num = stol(temp_s, nullptr, 10);
		digits.insertBefore(curr_num);
	}



	//remove leading zeros
	digits.moveBack();
	while(digits.peekPrev()==0 && digits.peekPrev() != -1){
		
		digits.eraseBefore();
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
		if(digits.length() > N.digits.length()){
			return 1;
		}
		if(digits.length() < N.digits.length()){
			return -1;
		}
	}
	if(sign() == -1 && N.sign() == -1){		
		if(digits.length() > N.digits.length()){
			return -1;
		}
		if(digits.length() < N.digits.length()){
			return 1;
		}
	}
	if(signum == 0 && N.signum == 0){
		return 0;
	}
	List digits_c = this->digits;
	List N_digits = N.digits;
	digits_c.moveFront();
	N_digits.moveFront();
	while(digits_c.peekNext() != -1 && N_digits.peekNext() != -1){
		if(sign() == 1 && N.sign() == 1){
			if(digits_c.peekNext() > N_digits.peekNext()){
				return 1;
			}
			if(digits_c.peekNext() < N_digits.peekNext()){
				return -1;
			}
		}
		if(sign() == -1 && N.sign() == -1){
			if(digits_c.peekNext() > N_digits.peekNext()){
				return -1;
			}
			if(digits_c.peekNext() < N_digits.peekNext()){
				return 1;
			}
		}
		digits_c.moveNext();
		N_digits.moveNext();
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
	//L.moveFront();
		//make the terms negative if the are below base.
		//example: 21+71= 92 and when normalizing it you need to add 100 instead so to keep it as subtracting 100 we willmake 92 negative and make it positive later
		/*
		while(L.peekNext() != -1){
			if(L.peekNext() < base){
				L.setAfter(L.peekNext()*-1);
			}
			L.moveNext();
		}
		*/
		//normalize each value by subtracting 100
	L.moveFront();
	long carry = 0;
	long orig = 0;
	while(L.peekNext() != -1){
		//L.setNext(L.peekNext()+carry-base);
		if(L.peekNext() < 0){
			//L.setNext(L.peekNext()*-1);
			orig = L.peekNext();
			L.setAfter(L.peekNext()+carry+base);
			//carry = -1;
			carry = orig/base;
			if(carry == 0){
				carry = -1;
			}
			
		}else if(L.peekNext() < base){
			orig = L.peekNext();
			L.setAfter(L.peekNext()+carry);
			//carry = 0;
			carry = orig/base;
		}else if(L.peekNext() > base){
			orig = L.peekNext();
			L.setAfter(L.peekNext()+carry-base);	
			//carry = 1;
			carry = orig/base;
		}
		L.moveNext();
	}
	//if there is a leftover carry by the end
	if(carry != 0){
		L.moveBack();
		L.insertAfter(carry);
	}

}

void sumList(List& S, List A, List B, int sgn){
	S.clear();
	if(sgn == 1){
		S.moveFront();
		A.moveFront();
		B.moveFront();
		int greatest_length = 0;
		if(A.length() > B.length()){
			greatest_length = A.length();
		}else{
			greatest_length = B.length();
		}
		for(int i = 0; i < greatest_length; i++){
			if(A.peekNext() == -1 && B.peekNext() == -1){
				break;
			}
			if(A.peekNext() != -1 && B.peekNext() != -1){
				S.insertBefore(A.peekNext()+B.peekNext());
				A.moveNext();
				B.moveNext();
			}else if(A.peekNext() == -1){
				S.insertBefore(B.peekNext());
				B.moveNext();
			}else{
				S.insertBefore(A.peekNext());
				A.moveNext();
			}
			S.moveNext();
		}
		normalizeList(S);
	}
	if(sgn == -1){
		S.moveFront();	
		A.moveFront();
		B.moveFront();
		int greatest_length = 0;
		if(A.length() > B.length()){
			greatest_length = A.length();
		}else{
			greatest_length = B.length();
		}
		for(int i = 0; i < greatest_length; i++){
			if(A.peekNext() == -1 && B.peekNext() == -1){
				break;
			}
			if(A.peekNext() != -1 && B.peekNext() != -1){
				S.insertBefore(A.peekNext()-B.peekNext());
				A.moveNext();
				B.moveNext();
			}else if(A.peekNext() == -1){
				S.insertBefore(0-B.peekNext());
				B.moveNext();
			}else{
				S.insertBefore(A.peekNext());
				A.moveNext();
			}
			S.moveNext();
		}
		normalizeList(S);
	}
}

   // BigInteger Arithmetic operations ----------------------------------------

   // add()
   // Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
	if(N.sign() == 0){
		BigInteger CPY = BigInteger(*this);
		normalizeList(CPY.digits);
		return CPY;
	}
	if(this->sign() == 0){
		BigInteger CPY = BigInteger(N);
		normalizeList(CPY.digits);
		return CPY;
	}
	BigInteger sum;
	int sgn = 1;
	if(N.sign() == -1 && this->sign() == 1){
		sgn = -1;
		BigInteger CPY = BigInteger(N);
		CPY.negate();
		//sumList(sum.digits, this->digits, CPY.digits, sgn);
		if(this->compare(CPY) == -1){
			sumList(sum.digits, CPY.digits, this->digits, sgn);
			sum.signum = -1;
		}else if(this->compare(CPY) == 1){
			sumList(sum.digits, this->digits, CPY.digits, sgn);
			sum.signum = 1;
		}else{
			sum.digits.clear();
			sum.signum = 0;
		}
		CPY.negate();
	}else if(N.sign() == 1 && this->sign() == -1){
		sgn = -1;
		BigInteger CPY = BigInteger(*this);
		CPY.negate();
		//sumList(sum.digits, N.digits, CPY.digits, sgn);
		if(CPY.compare(N) == -1){
			sumList(sum.digits, N.digits, CPY.digits,sgn);
			sum.signum = 1;
		}else if(CPY.compare(N) == 1){
			sumList(sum.digits, CPY.digits, N.digits, sgn);
			sum.signum = -1;
		}else{
			sum.digits.clear();
			sum.signum = 0;
		}
		CPY.negate();
	}else{
		sgn = 1;
		sumList(sum.digits, this->digits, N.digits, sgn);
		if(N.sign() == -1){
			sum.signum = -1;
		}else{
			sum.signum = 1;
		}	
	}
	BigInteger zero;
	if(zero.compare(sum) == 0){
		sum.signum = 0;
	}
	return sum;
}

   // sub()
   // Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
	BigInteger CPY = BigInteger(N);
	CPY.negate();
	BigInteger diff;
	diff = this->add(CPY);;
	CPY.negate();
	BigInteger zero;
	if(zero.compare(diff) == 0){
		diff.signum = 0;
	}
	return diff;
}

void scalarMultList(List& L, ListElement m){
	L.moveFront();
	//while(L.peekNext() != -1){
	for(int i = 0; i < L.length(); i++){
		L.setAfter(L.peekNext()*m);
		L.moveNext();
	}
}

   // mult()
   // Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
	BigInteger CPY = BigInteger(N);
	if(CPY.signum == 0 || this->signum == 0){
		BigInteger zero;
		return zero;
	}
	CPY.digits.moveFront();
	BigInteger prod;
	//bool first_iter = true;
	//BigInteger copy = BigInteger(*this);
	BigInteger copy;
	int num_shifts = 0;
	//while(CPY.digits.peekNext() != -1){
	for(int i = 0; i < CPY.digits.length(); i++){
		copy = BigInteger(*this);
		copy.digits.moveFront();
		for(int i = 0; i < num_shifts; i++){
			copy.digits.insertBefore(0);
			copy.digits.moveFront();
		}/*
		if(!first_iter){
			copy.digits.moveFront();
			copy.digits.insertBefore(0);
		}
	*/	
		scalarMultList(copy.digits, CPY.digits.peekNext());
		
		/*
		copy.digits.moveFront();
		for(int i = 0; i < num_shifts; i++){
			copy.digits.insertBefore(0);
			copy.digits.moveFront();
		}*/
		prod = prod.add(copy);
		copy.digits.clear();
		CPY.digits.moveNext();
		num_shifts+=1;
		//first_iter = false;
	}
	return prod;
}


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this BigInteger consisting of its
   // base 10 digits. If this BigInteger is negative, the returned string 
   // will begin with a negative sign '-'. If this BigInteger is zero, the
   // returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
	//std::cerr << digits.front() << std::endl;
	std::string str = "";
	/*
	if(sign() == -1){
		str+="-";
	}
	*/
	if(sign() == 0){
		str = "0";
		return str;
	}
	bool first_iter = true;
	digits.moveBack();
	while(digits.peekPrev() != -1){
		std::string curr_num = std::to_string(digits.peekPrev());
		if((int)(curr_num.length()) < power && !first_iter){
			for(int i = 0; i < (int)(power-curr_num.length()); i++){
				str+="0";
			}
		}
		if(first_iter){
			first_iter = false;
		}
		str+=curr_num;
		digits.movePrev();
	}
	if(sign() == -1 && std::isdigit(str[0])){
		str.insert(0, "-");
	}
	return str;
}


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
	//return stream << N.BigInteger::to_string();
	return stream << N.to_string();
}

   // operator==()
   // Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
	return (A.BigInteger::compare(B) == 0);
}

   // operator<()
   // Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
	return (A.BigInteger::compare(B) == -1);
}

   // operator<=()
   // Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
	if(A.BigInteger::compare(B) == -1 || A.BigInteger::compare(B) == 0){
		return true;
	}
	return false;
}

   // operator>()
   // Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
	return (A.BigInteger::compare(B) == 1);
}

   // operator>=()
   // Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
	if(A.BigInteger::compare(B) == 1 || A.BigInteger::compare(B) == 0){
		return true;
	}
	return false;
}
   // operator+()
   // Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	return A.add(B);
}

   // operator+=()
   // Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	A = A.add(B);
	return A;
}

   // operator-()
   // Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	return A.sub(B);
}

   // operator-=()
   // Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	A = A.sub(B);
	return A;
}

   // operator*()
   // Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	return A.mult(B);
}

   // operator*=()
   // Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	A = A.mult(B);
	return A;
}



