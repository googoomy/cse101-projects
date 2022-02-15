#include <iostream>
#include <string>
#include "List.h"

#define DUMMY_NUM -1

List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

List::List(){
	frontDummy = new Node(DUMMY_NUM);
	backDummy = new Node(DUMMY_NUM);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

List::List(const List& L){
	frontDummy = new Node(DUMMY_NUM);
	backDummy = new Node(DUMMY_NUM);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements= 0;

	//load elements of L into this List
	Node *N = L.frontDummy->next;
	while(N != L.backDummy){
		this->insertBefore(N->data);
		N = N->next;
	}
	//reset cursor
	this->moveFront();
}

//Destructor
List::~List(){
	clear();
	delete(frontDummy);
	delete(backDummy);
}
   // Access functions --------------------------------------------------------

   // length()
   // Returns the length of this List.
int List::length() const{
	return num_elements;
}
	
   // front()
   // Returns the front element in this List.
   // pre: length()>0
ListElement List::front() const{
	if(length() <= 0){
		throw std::length_error("List: front(): empty List");
	}
	return frontDummy->next->data;
}

   // back()
   // Returns the back element in this List.
   // pre: length()>0
ListElement List::back() const{
	if(length() <= 0){
		throw std::length_error("List: back(): empty List");
	}
	return backDummy->prev->data;
}

   // position()
   // Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
	return pos_cursor;
}

   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<length()
ListElement List::peekNext() const{
	if(position() >= length()){
		std::cerr << "List: peekNext(): no next element in List" << std::endl;
		return (EXIT_FAILURE);
	}
	return afterCursor->data;
}


   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
ListElement List::peekPrev() const{
	if(position() <= 0){
		std::cerr << "List: peekPrev(): no previous element in List" << std::endl;
		return (EXIT_FAILURE);
	}
	return beforeCursor->data;
}


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	moveFront();
	while(length() != 0){
		eraseAfter();
	}
}

   // moveFront()
   // Moves cursor to position 0 in this List.
void List::moveFront(){
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	pos_cursor = 0;

}

   // moveBack()
   // Moves cursor to position length() in this List.
void List::moveBack(){
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
	pos_cursor = length();
}	

   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
ListElement List::moveNext(){
	if(position() >= length()){
		std::cerr << "List: moveNext(): no next element in List" << std::endl;
		return (EXIT_FAILURE);
	}
	pos_cursor++;
	beforeCursor = beforeCursor->next;
	afterCursor = afterCursor->next;
	return beforeCursor->data;
}

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
ListElement List::movePrev(){
	if(position() <= 0){
		std::cerr << "List: movePrev(): no previous element in List" << std::endl;
		return (EXIT_FAILURE);
	}
	pos_cursor--;
	beforeCursor = beforeCursor->prev;
	afterCursor = afterCursor->prev;
	return afterCursor->data;
}

   // insertAfter()
   // Inserts x after cursor.
void List::insertAfter(ListElement x){
	Node* N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	afterCursor = N;
	num_elements++;
}

   // insertBefore()
   // Inserts x before cursor.
void List::insertBefore(ListElement x){
	Node* N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	beforeCursor = N;
	pos_cursor++;
	num_elements++;
}

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
void List::setAfter(ListElement x){
	if(position() >= length()){
		std::cerr << "List: setAfter(): no next element in List" << std::endl;
		exit(1);
	}
	eraseAfter();
	insertAfter(x);
}

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
void List::setBefore(ListElement x){
	if(position() <= 0){
			std::cerr << "List: setBefore(): no previous element in List" << std::endl;
			exit(1);
		}
		eraseBefore();
		insertBefore(x);
	}

	   // eraseAfter()
	   // Deletes element after cursor.
	   // pre: position()<length()
void List::eraseAfter(){
	if(position() >= length()){
		std::cerr << "List: eraseAfter(): no next element in List" << std::endl;
		exit(1);
	}
	Node* N = afterCursor;
	afterCursor = afterCursor->next;
	beforeCursor->next = afterCursor;
	afterCursor->prev = beforeCursor;
	delete N;
	num_elements--;
}

	   // eraseBefore()
	   // Deletes element before cursor.
	   // pre: position()>0
void List::eraseBefore(){
	if(position() <= 0){
		std::cerr << "List: eraseBefore(): no previous element in List" << std::endl;
		exit(1);
	}
	Node* N = beforeCursor;
	beforeCursor = beforeCursor->prev;
	afterCursor->prev = beforeCursor;
	beforeCursor->next = afterCursor;
	delete N;
	pos_cursor--;
	num_elements--;
}


	   // Other Functions ---------------------------------------------------------

	   // findNext()
	   // Starting from the current cursor position, performs a linear search (in 
	   // the direction front-to-back) for the first occurrence of element x. If x
	   // is found, places the cursor immediately after the found element, then 
	   // returns the final cursor position. If x is not found, places the cursor 
	   // at position length(), and returns -1. 
int List::findNext(ListElement x){
	while(afterCursor != backDummy){
		if(afterCursor->data == x){
			moveNext();
			return pos_cursor;
		}
		moveNext();
	}
	return -1;
}

	   // findPrev()
	   // Starting from the current cursor position, performs a linear search (in 
	   // the direction back-to-front) for the first occurrence of element x. If x
	   // is found, places the cursor immediately before the found element, then
	   // returns the final cursor position. If x is not found, places the cursor 
	   // at position 0, and returns -1. 
int List::findPrev(ListElement x){
	while(beforeCursor != frontDummy){
		if(beforeCursor->data == x){
			movePrev();
			return pos_cursor;
		}
		movePrev();
	}
	return -1;
}

	   // cleanup()
	   // Removes any repeated elements in this List, leaving only unique elements.
	   // The order of the remaining elements is obtained by retaining the frontmost 
	   // occurrance of each element, and removing all other occurances. The cursor 
	   // is not moved with respect to the retained elements, i.e. it lies between 
	   // the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
	Node* N = frontDummy->next;
	int i = 0;
	int fn = 0;
	int curr_pos = pos_cursor;
	//int orig_size = length();
	//for(int j = 0; j < orig_size; j++){
	while(N != backDummy){
		moveFront();
		findNext(N->data);
		while(true){
			fn = findNext(N->data);
			if(fn == -1){
				break;
			}
			if(N->next == backDummy){
				break;
			}
			if(pos_cursor <= curr_pos){
				curr_pos--;
			}
			eraseBefore();
		}
		N = frontDummy->next;
		i++;
		for(int j = 0; j < i; j++){
			N = N->next;
		}
	}
	
	moveFront();
	for(int j = 0; j < curr_pos; j++){
		moveNext();
	}
}
	 
	   // concat()
	   // Returns a new List consisting of the elements of this List, followed by
	   // the elements of L. The cursor in the returned List will be at postion 0.
	List List::concat(const List& L) const{
		List LL;
		Node* N = this->frontDummy->next;
		while(N != this->backDummy){
		LL.insertBefore(N->data);
		N = N->next;
	}
	N = L.frontDummy->next;
	while(N != L.backDummy){
		LL.insertBefore(N->data);
		N = N->next;
	}
	LL.moveFront();
	return LL;
}

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   // Credit: to_string() from Queue.cpp in the examples
std::string List::to_string() const{
	Node* N = nullptr;
	std::string s = "(";

	for(N = frontDummy->next; N != backDummy; N = N->next){
		if(N->next == backDummy){
			s += std::to_string(N->data);
			break;	
		}
		s += std::to_string(N->data)+", ";
	}
	s += ")";
	return s;
}

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   // Credit: equals() from Queue.cpp in the examples
bool List::equals(const List& R) const{
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;

	eq = ( this->num_elements == R.num_elements);
	N = this->frontDummy->next;
	M = R.frontDummy->next;
	while(eq && N != nullptr){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
}

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
}

   // operator=()
   // Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	if(this != &L){
		List temp = L;

		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(num_elements, temp.num_elements);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(beforeCursor, temp.beforeCursor);
	}
	return *this;
}

