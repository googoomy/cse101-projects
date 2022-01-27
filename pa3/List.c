/********************************************
 * James Gu
 * jjgu
 * pa2
 *
 *
 * 
 *******************************************/
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structs
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int n;
	int idx;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
//This function creates a new Node
Node newNode(int node_data){
	Node N = malloc(sizeof(NodeObj));
	N->data = node_data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

//This function deconstructs the Node
void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

//This function is the consrtuctor for the List ADT
List newList(void){
	List L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->cursor = NULL;
	L->n = 0;
	L->idx = -1;
	L->back = NULL;
	return(L);
}	// Creates and returns a new empty List.

void freeList(List* pL){ // Frees all heap memory associated with *pL, and sets
	// *pL to NULL.
	if(pL != NULL && * pL != NULL){
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

// Access function -----------------------------------------------------------
int length(List L){ // Returns the number of elements in L.
	if(L == NULL){
		fprintf(stderr, "List Error: calling length() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->n);
}

int index(List L){ // Returns index of cursor element if defined, -1 otherwise.
	if(L == NULL){
		fprintf(stderr, "List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL){
		return -1;
	}
	return (L->idx);
}

int front(List L){ // Returns front element of L. Pre: length()>0
	if(L == NULL){
		fprintf(stderr, "List Error: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		fprintf(stderr, "List Error: calling front() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	return (L->front->data);
}

int back(List L){ // Returns back element of L. Pre: length()>0
	if(L == NULL){
		fprintf(stderr, "List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);	
	}
	if(length(L) <= 0){
		fprintf(stderr, "List Error: calling back() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	return (L->back->data);
}

int get(List L){ // Returns cursor element of L. Pre: length()>0, index()>=0
	if(L == NULL){
		fprintf(stderr, "List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || index(L) < 0){
		fprintf(stderr, "List Error: calling get() on an empty List\n");
		exit(EXIT_FAILURE); 
	}
	return (L->cursor->data);
}

bool equals(List A, List B){ // Returns true iff Lists A and B are in same
 // state, and returns false otherwise.
	if(A == NULL){
		fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(B == NULL){
		fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	//if the lists are both 0 then they are equal
	if(length(A) == 0 && length(B) == 0){
		return true;
	}
	//if the length, front, or the backs are different then theya re not equal
	if(length(A) != length(B) || front(A) != front(B) || back(A) != back(B)){
		return false;
	}
	//loop through each list and check if all elements in between front and back are equal
	Node NodA = A->front;
	Node NodB = B->front;
	bool isEqual = true;
	for(int i = 0; i < length(A); i++){
		if(NodA->data != NodB->data){
			isEqual = false;
			break;
		}
		NodA = NodA->next;
		NodB = NodB->next;
	}
	return isEqual;
}

 // Manipulation procedures ----------------------------------------------------
void clear(List L){ // Resets L to its original empty state.
	//loop through the List and free each Node
	if(L->front != NULL){
		//Nod is the Node that will be deleted and is also the iteration variable in a way
		Node Nod = L->front;
		while(Nod != NULL){
			//temporarily store the next Node
			Node NodTemp = Nod->next;
			if(Nod != NULL){
				freeNode(&Nod);
			}
			//make the iteration Node the next Node in line
			Nod = NodTemp;
		}
	}
	//memset to reset the List to 0
	//if I don't have this line I segfault
	memset(L, 0, sizeof(ListObj));
	L->idx = -1;
}

void set(List L, int x){ // Overwrites the cursor element’s data with x. 
 // Pre: length()>0, index()>=0
	if(L == NULL){
		fprintf(stderr, "List Error: calling set() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || index(L) < 0){
		fprintf(stderr, "List Error: calling set() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	Node Nod = newNode(x);
	//in case if the cursor is at the front
	if(L->idx == 0){
		//set the new Node's next to the current front's next, 
		//set the next Node from the current front's previous to the new Node,
		//free the current front,
		//and set cursor to the New Node
		Nod->next = L->front->next;
		L->front->next->prev = Nod;
		freeNode(&L->front);
		L->front = Nod;
		L->cursor = Nod;
	//in case if the cursor is at the back
	}else if(L->idx == (L->n)-1){
		//set the new Node's previous to the current back's previous,
		//set the prevous Node from the current back's next to the new Node,
		//free the current back,
		//and set the cursor to the new Node
		Nod->prev = L->back->prev;
		L->back->prev->next = Nod;
		freeNode(&L->back);
		L->back = Nod;
		L->cursor = Nod;
	//in case if the List is only one element long
	}else if(length(L) == 1){
		L->idx = 0;
		freeNode(&L->front);
		L->front = L->back = Nod;
		L->cursor = Nod;
	//in case if the cursor is somewhere in between front and back
	}else{
		//set the node at the cursor's next's, previous to the new Node
		//set the node at the cursor's previous's next to the new Node
		//set the new Node's next to the current cursor's Node's next
		//set the new Node's prev to the current cursor's Node's prev
		//free the cursor Node and set the cursor to the new Node
		L->cursor->next->prev = Nod;
		L->cursor->prev->next = Nod;
		Nod->next = L->cursor->next;
		Nod->prev = L->cursor->prev;
		freeNode(&L->cursor);
		L->cursor = Nod;
	}
}

void moveFront(List L){ // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
	if(L == NULL){
		fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) > 0){
		//set the cursor to the front and index to 0
		L->cursor = L->front;
		L->idx = 0;
	}
}

void moveBack(List L){ // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
	if(L == NULL){
		fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) > 0){
		//set the cursor to the back and index to n-1
		L->cursor = L->back;
		L->idx = (L->n)-1;
	}
}		

void movePrev(List L){ // If cursor is defined and not at front, move cursor one 
 // step toward the front of L; if cursor is defined and at 
 // front, cursor becomes undefined; if cursor is undefined 
 // do nothing
 	if(L == NULL){
		fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor != NULL){
		if(L->idx != 0){
			L->idx--;
			L->cursor = L->cursor->prev;
		}	
		//if the List is length 1
		else{
			L->cursor = NULL;
			L->idx = -1;
		}
	}
}
	
void moveNext(List L){ // If cursor is defined and not at back, move cursor one 
 // step toward the back of L; if cursor is defined and at 
 // back, cursor becomes undefined; if cursor is undefined 
 // do nothing
	if(L == NULL){
		fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor != NULL){
	       	if(L->idx != (L->n)-1){
			L->idx++;
			L->cursor = L->cursor->next;
		}
		//if the List is length 1
		else{
			L->cursor = NULL;
			L->idx = -1;
		}
	}
}

void prepend(List L, int x){ // Insert new element into L. If L is non-empty, 
 // insertion takes place before front element.
	Node Nod = newNode(x);
	//if the List is empty then the front and back are the same
	if(length(L) == 0){
		L->front = L->back = Nod;
	}else{ //if the length of the list is more than 0
		//Set the new node's next to the front
		//set the current front's previous to the new node
		//set the front to the new Node
		//increase the cursor's index by 1
		Nod->next = L->front;
		L->front->prev = Nod;
		L->front = Nod;
		if(L->idx != -1){
			L->idx++;
		}
	}
	L->n++;
}

void append(List L, int x){ // Insert new element into L. If L is non-empty, 
 // insertion takes place after back element.
	Node Nod = newNode(x);
	if(length(L) == 0){
		L->front = L->back = Nod;
	}else{
		//set the current back's next to the new Node,
		//set the new Node's previous to the current back
		//make the new back the new node
		L->back->next = Nod;
		Nod->prev = L->back;
		L->back = Nod;
	}
	L->n++;
}

void insertBefore(List L, int x){ // Insert new element before cursor. 
 // Pre: length()>0, index()>=0
	if(L == NULL){
		fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || L->idx < 0){
		fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(L->idx == 0){
		prepend(L, x);
	}else{
		//to insert before, make sure the new Node's next connects to the cursor and prev connect to the cursor's prev
		//then make sure the those nodes point to the new node instead of each other
		//the index increases in insertBefore() because the cursor gets pushed up a position in the list
		Node Nod = newNode(x);
		L->idx++;
		L->n++;
		Nod->next= L->cursor;
		Nod->prev = L->cursor->prev;
		L->cursor->prev->next = Nod;
		L->cursor->prev = Nod;
	}
}

void insertAfter(List L, int x){ // Insert new element after cursor. 
 // Pre: length()>0, index()>=0
	if(L == NULL){
		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || L->idx < 0){
		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->idx >= L->n - 1){
		append(L, x);
	}else{
		//to insert after, the new Node's prev becomes the cursor and the next becomes the cursor's next
		//those nodes point to the new node instead of each other
		Node Nod = newNode(x);
		L->n++;
		Nod->next = L->cursor->next;
		Nod->prev = L->cursor;
		L->cursor->next->prev = Nod;
		L->cursor->next = Nod;
	}
}
void deleteFront(List L){ // Delete the front element. Pre: length()>0
	if(L == NULL){
		fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
	}
	if(length(L) == 0){
		fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	
	if(L->front == NULL){
		return;
	}
	//if the cursor is at the front then it becomes null after front is deleted
	if(L->cursor == L->front){
		L->cursor = NULL;
		L->idx = -1;
	}
	//if the length of the list is 1
	if(length(L) == 1){
		//free the only node in the list
		freeNode(&L->front);
		L->front = NULL;
		L->back = NULL;
		L->n = 0;
	//if the length of the list is greater than 1
	}else{
		//set a temp Node to the current front
		//set the front to the next node in line
		//and set this new node's previous to null because we are going to delete the old front
		//free the old fornt
		Node Nod = L->front;
		L->front = L->front->next;
		L->front->prev = NULL;
		freeNode(&Nod);
		Nod = NULL;
		if(L->idx != -1){
			L->idx--;
		}
		L->n--;
	}
}

void deleteBack(List L){ // Delete the back element. Pre: length()>0
	if(L == NULL){
		fprintf(stderr, "ListError: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) == 0){
		fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(L->back == NULL){
		return;
	}
	//if he cursor is at the back then it becomes null after back is deleted
	if(L->cursor == L->back){
		L->cursor = NULL;
		L->idx = -1;
	}
	//if the length of the list is 1
	if(length(L) == 1){
		//free the only node in the list
		freeNode(&L->back);
		L->n = 0;
	}else{
		//set the temp Node to the back's previous
		//set the back's previous's next to NULL
		//free the current back
		//set the new node as the new back
		Node Nod = L->back->prev;
		L->back->prev->next = NULL;
		freeNode(&L->back);
		L->back = Nod;
		L->n--;
	}
}	
	
void delete(List L){ // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
	if(L == NULL){
		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || index(L) < 0){
		fprintf(stderr, "List Error: calling delete() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL){
		return;
	}
	//if cursor is the front then deleteFront()
	if(L->cursor == L->front){
		deleteFront(L);
	//if cursor is the back then deleteBack()
	}else if(L->cursor == L->back){
		deleteBack(L);
	}else{
		//set the current cursor's next's previous and prev's next to null
		//free the cursor
		//make the new cursor into the new node
		L->cursor->next->prev = NULL;
		L->cursor->prev->next = NULL;
		freeNode(&L->cursor);
		L->cursor = NULL;
		L->idx = -1;
		L->n--;
	}
}	
	
// Other operations -----------------------------------------------------------

void printList(FILE* out, List L){ // Prints to the file pointed to by out, a 
 // string representation of L consisting 
 // of a space separated sequence of integers,
// with front on left.
	if(L == NULL){
		fprintf(stderr, "List Error calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(out == NULL){
		return;
	}
	//loop through the list and print the current node's data into the outfile
	Node Nod = NULL;
	for(Nod = L->front; Nod != NULL; Nod = Nod->next){
		fprintf(out, "%d ", Nod->data);
	}
}

List copyList(List L){ // Returns a new List representing the same integer 
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state 
// of L is unchanged.
	if(L == NULL){
		fprintf(stderr, "List Error calling copyList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	//if the list is empty then return an empty list
	if(length(L) == 0){
		List R = newList();
		return R;
	}
	//loop through the list and add each node to the new list
	Node Nod = NULL;
	List R = newList();
	for(Nod = L->front; Nod != NULL; Nod = Nod->next){
		append(R, Nod->data);
	}
	return R;
}
