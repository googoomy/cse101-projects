#include <iostream>
#include <string>
#include "List.h"

#define DUMMY_NUM -1

List::Node::Node(int x){
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
	return frontDummy;
}

   // back()
   // Returns the back element in this List.
   // pre: length()>0
ListElement List::back() const{
	if(length() <= 0){
		throw std::length_error("List: back(): empty List");
	}
	return backDummy;
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
		throw std::position_error("List: peekNext(): no next element in List");
	}
	return afterCursor->data;
}


   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
ListElement List::peekPrev() const{
	if(position <= 0){
		throw std::position_error("List: peekPrev(): no previous element in List");
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
		throw std::position_error("List: moveNext(): no next element in List");
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
		throw std::position_error("List: movePrev(): no previous element in List");
	}
	pos_cursor--;
	beforeCursor = beforeCursor->prev;
	afterCursor = afteerCursor->prev;
	return afterCursor->data;
}

   // insertAfter()
   // Inserts x after cursor.
void insertAfter(ListElement x);

   // insertBefore()
   // Inserts x before cursor.
void insertBefore(ListElement x);

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
void setAfter(ListElement x);

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
void setBefore(ListElement x);

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
void eraseAfter();

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
void eraseBefore();


   // Other Functions ---------------------------------------------------------

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
int findNext(ListElement x);

   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
int findPrev(ListElement x);

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
void cleanup();
 
   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
List concat(const List& L) const;

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
std::string to_string() const;

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
bool equals(const List& R) const;


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
friend std::ostream& operator<<( std::ostream& stream, const List& L );

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
friend bool operator==( const List& A, const List& B );

   // operator=()
   // Overwrites the state of this List with state of L.
List& operator=( const List& L );

