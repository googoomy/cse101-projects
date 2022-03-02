//-----------------------------------------------------------------------------
// Dictionary.cpp
// Client file for Dictionary ADT based on a Binary Search Tree. Includes a
// built in iterator called current that can perform a smallest-to-largest
// (forward) or a largest-to-smallest (reverse) iteration over all keys.
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>

#include "Dictionary.h"

//Node Constructor
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
};

   // Class Constructors & Destructors ----------------------------------------
Dictionary::Dictionary(){
	nil = new Node("NIL", -1);
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("NIL", -1);
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::~Dictionary(){
	clear();
}
   // Helper Functions (Optional) ---------------------------------------------

   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
void inOrderString(std::string& s, Node* R) const;

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order determined
   // by a pre-order tree walk.
void preOrderString(std::string& s, Node* R) const;

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
void preOrderCopy(Node* R, Node* N){
	if(R != this->nil){
		 R;
		preOrder
	}
}

   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R, sets R to nil.
void postOrderDelete(Node* R){
	if(R != this->nil){
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		delete R;
	}

}

   // search()
   // Searches the subtree rooted at R for a Node with key==k. Returns
   // the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if(R == this->nil || k == R->key){
		return R;
	}else if(k < R->key){
		return search(R->left, k);
	}else{
		return search(R->right, k);
	}
}

   // findMin()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // leftmost Node in that subtree, otherwise returns nil.
Node* findMin(Node* R){
	while(R->left != this->nil){
		R = R->left;
	}
	return R;
}

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
Node* findMax(Node* R){
	while(R->right != this->nil){
		R = R->right;
	}
	return R;
}

   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
Node* findNext(Node* N){
	if(N->right != this->nil){
		return findMin(N->right);
	}
	Node* next = N->parent;
	while(next != this->nil && N == next->right){
		N = next;
		next = next->parent;
	}
	return next;
}

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
Node* findPrev(Node* N){
	Node prev;
	if(N->left != this->nil){
		prev = findPrev(N->left);
	}else{
		return N;
	}
	return prev;
}


   // Access functions --------------------------------------------------------

   // size()
   // Returns the size of this Dictionary.
int Dictionary::size() const{
	return num_pairs;
}

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
bool Dictionary::contains(keyType k) const{
	return (search(this->root, k) != this->nil);
	
}

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
	Node n = search(this->root, k);
	if(n == this->nil){
		return 
	}
}

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
bool Dictionary::hasCurrent() const{
	return (this->current != this->nil);
}

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
	if(!hasCurrent){
		throw std::invalid_argument("Dictionary: currentKey: current iterator undefined");
		exit(EXIT_FAILURE);
	}
	return this->current->key;
}

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
valType& currentVal() const;


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
void clear();

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
void setValue(keyType k, valType v);

   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
void remove(keyType k);

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
void begin();

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
void end();

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
void next();

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
void prev();


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
std::string to_string() const;

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
std::string pre_string() const;

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
bool equals(const Dictionary& D) const;


   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
friend std::ostream& operator<<( std::ostream& stream, Dictionary& D );

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
friend bool operator==( const Dictionary& A, const Dictionary& B );

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
Dictionary& operator=( const Dictionary& D );



