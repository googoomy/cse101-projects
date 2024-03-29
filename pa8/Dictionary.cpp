//-----------------------------------------------------------------------------
// James Gu
// jjgu
// pa8
//Dictionary.cpp
// Client file for Dictionary ADT based on a Binary Search Tree. Includes a
// built in iterator called current that can perform a smallest-to-largest
// (forward) or a largest-to-smallest (reverse) iteration over all keys.
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <stdexcept>
#include <stack>
#include "Dictionary.h"

#define RED 0
#define BLACK 1

//Node Constructor
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = NULL;
    left = NULL;
    right = NULL;
    color = RED;
};

   // Class Constructors & Destructors ----------------------------------------
Dictionary::Dictionary(){
	nil = new Node("\000", INT_MIN);
	nil->left = nil;
	nil->right = nil;
	nil->color = BLACK;
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("\000", INT_MIN);
	nil->left = nil;
	nil->right = nil;
	nil->color = BLACK;
	root = nil;
	current = nil;
	num_pairs = 0;
	Dictionary &ref = const_cast <Dictionary &>(D);
	ref.begin();
	while(ref.current != ref.nil){
		setValue(ref.current->key, ref.current->val);
		ref.next();
	}
}

Dictionary::~Dictionary(){
	begin();
	while(current != this->nil){
		setValue(current->key, current->val);
		remove(current->key);
		begin();
	}
}
   // Helper Functions (Optional) ---------------------------------------------

   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
	if(R != this->nil){
		inOrderString(s, R->left);
		std::string kv = "";
		if(R->val > 0){
			kv += R->key + " : " + std::to_string(R->val) + "\n";
		}
		s+=kv;
		inOrderString(s, R->right);
	}
}

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order determined
   // by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
	if(R != this->nil){
		std::string kv = "";
		if(R->val > 0){
			kv += R->key + "\n";
		}
		s+=kv;
		preOrderString(s, R->left);
		preOrderString(s, R->right);
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
Dictionary::Node* Dictionary::findMin(Node* R){	
	Node *min = R;
	while(min != this->nil && min->left != this->nil){
		min = min->left;
	}
	return min;
}

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
	Node *max = R;
	while(max != this->nil && max->right != this->nil){
		max = max->right;
	}
	return max;
}

   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
	if(N == this->nil){
		return this->nil;
	}
	if(N->right != this->nil){
		N = findMin(N->right);
	}else{
		Node* next = N->parent;
		while(next != this->nil && N == next->right){
			N = next;
			next = next->parent;
		}
		N = next;
	}
	return N;
}

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
	if(N == this->nil){
		return this->nil;
	}
	if(N->left != this->nil){
		N = findMax(N->left);
	}else{
		Node* prev = N->parent;
		while(prev != this->nil && N == prev->left){
			N = prev;
			prev = prev->parent;
		}
		N = prev;
	}
	return N;
}

//Credit: Tantalo's Example
void Dictionary::LeftRotate(Node* N){
	Node* y = N->right;
	N->right = y->left;
	if(y->left != this->nil){
		y->left->parent = N;
	}
	y->parent = N->parent;
	if(N->parent == this->nil){
		this->root = y;
	}else if(N == N->parent->left){
		N->parent->left = y;
	}else{
		N->parent->right = y;
	}
	y->left = N;
	N->parent = y;
}
//Credit: Tantalo's Example
void Dictionary::RightRotate(Node* N){
	Node* y = N->left;
	N->left = y->right;
	if(y->right != this->nil){
		y->right->parent = N;
	}
	y->parent = N->parent;
	if(N->parent == this->nil){
		this->root = y;
	}else if(N == N->parent->right){
		N->parent->right = y;
	}else{
		N->parent->left = y;
	}
	y->right = N;
	N->parent = y;
}
//Credit: Tantalo's Example
void Dictionary::RB_InsertFixUp(Node* N){
	while(N->parent->color == RED){
		if(N->parent == N->parent->parent->left){
			Node* y = N->parent->parent->right;
			if(y->color == RED){
				N->parent->color = BLACK;
				y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			}
			else{
				if(N == N->parent->right){
					N = N->parent;
					LeftRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				RightRotate(N->parent->parent);
			}
		}else{
			Node* y = N->parent->parent->left;
			if(y->color == RED){
				N->parent->color = BLACK;
				y->color = BLACK;
				N->parent->parent->color = 0;
				N = N->parent->parent;
			}else{
				if(N == N->parent->left){
					N = N->parent;
					RightRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				LeftRotate(N->parent->parent);
			}
		}
	}
	root->color = BLACK;
}
//Credit: Tantalo's Example
void Dictionary::RB_Transplant(Node* u, Node* v){
	if(u->parent == this->nil){
		this->root = v;
	}else if(u == u->parent->left){
		u->parent->left = v;
	}else{
		u->parent->right = v;
	}
	v->parent = u->parent;
}
//Credit: Tantalo's Example
void Dictionary::RB_DeleteFixUp(Node* N){
	while(N != this->root && N->color == BLACK){
		if(N == N->parent->left){
			Node* w = N->parent->right;
			if(w->color == RED){
				w->color = BLACK;
				N->parent->color = RED;
				LeftRotate(N->parent);
				w = N->parent->right;
			}
			if(w->left->color == 1 && w->right->color == 1){
				w->color = RED;
				N = N->parent;
			}else{
				if(w->right->color == BLACK){
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(w);
					w = N->parent->right;
				}
				w->color = N->parent->color;
				N->parent->color = BLACK;
				LeftRotate(N->parent);
				N = this->root;
			}
		}else{
			Node* w = N->parent->left;
			if(w->color == RED){
				w->color = BLACK;
				N->parent->color = RED;
				RightRotate(N->parent);
				w = N->parent->left;
			}	
			if(w->right->color == BLACK && w->left->color == BLACK){
				w->color = RED;
				N = N->parent;
			}else{
				if(w->left->color == BLACK){
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(w);
					w = N->parent->left;
				}
				w->color = N->parent->color;
				N->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(N->parent);
				N = this->root;
			}
		}
	}
	N->color = BLACK;
}

//Credit: Tantalo's Example
void Dictionary::RB_Delete(Node* N){
	Node* y = N;
	int y_original_color = y->color;
	Node* x = this->nil;
	if(N->left == this->nil){
		x = N->right;
		RB_Transplant(N, N->right);
	}else if(N->right == this->nil){
		x = N->left;
		RB_Transplant(N, N->left);
	}else{
		y = findMin(N->right);
		y_original_color = y->color;
		x = y->right;
		if(y->parent == N){
			x->parent = y;
		}else{
			RB_Transplant(y, y->right);
			y->right = N->right;
			y->right->parent = y;
		}
		RB_Transplant(N, y);
		y->left = N->left;
		y->left->parent = y;
		y->color = N->color;
	}
	if(y_original_color == BLACK){
		RB_DeleteFixUp(x);
	}
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
	if(!contains(k)){
		throw std::logic_error("Dictionary: getValue(): key "+k+" does not exist");
	}
	Node* n = search(this->root, k);
	return n->val;
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
	if(!hasCurrent()){
		throw std::logic_error("Dictionary: currentKey(): current undefined");
	}
	return this->current->key;
}

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
valType& Dictionary::currentVal() const{
	if(!hasCurrent()){
		throw std::logic_error("Dictionary: currentVal(): current undefined");
	}
	return this->current->val;

}


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
	begin();
	while(current != this->nil){
		setValue(current->key, current->val);
		remove(current->key);
		begin();
	}
	nil= new Node("\000", INT_MIN);
	nil->left = this->nil;
	nil->right =this->nil;
	nil->color = BLACK;
	root = this->nil;
	current = this->nil;
	num_pairs = 0;
}

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   // Credit: TreeInsert from Tantalo in Examples
void Dictionary::setValue(keyType k, valType v){
	Node* m = new Node(k,v);
	Node* y = this->nil;
	Node* x = this->root;
	while(x != this->nil){
		y = x;
		if(m->key < x->key){
			x = x->left;
		}else if(m->key > x->key){
			x = x->right;
		}else{
			x->val = v;
			return;
		}
	}
	m->parent = y;
	if(y == this->nil){
		this->root = m;
	}else if(m->key < y->key){
		y->left = m;
	}else{
		y->right = m;
	}
	m->left = this->nil;
	m->right = this->nil;
	m->color = RED;
	num_pairs++;
	RB_InsertFixUp(m);
}

   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
void Dictionary::remove(keyType k){
	Node* m = search(this->root, k);
	if(m == this->nil){
		throw std::logic_error("Dictionary: remove(): "+k+" does not exist");
	}
	if(this->current == m){
		current = this->nil;
	}
	RB_Delete(m);
	num_pairs--;
	free(m);
}

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
	this->current = findMin(this->root);
}

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
	this->current = findMax(this->root);
}

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
void Dictionary::next(){
	if(current == this->nil){
		throw std::logic_error("Dictionary: next(): current undefined");
	}else{
		current = findNext(this->current);
	}
}

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
void Dictionary::prev(){
	if(current == this->nil){
		throw std::logic_error("Dictionary: prev(): current undefined");
	}else{
		current = findPrev(this->current);
	}
}


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
	std::string s = "";
	inOrderString(s, this->root);
	return s;
}

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
std::string Dictionary::pre_string() const{
	std::string s = "";
	preOrderString(s, this->root);
	return s;
}

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
	std::string T1 = this->pre_string();
	std::string T2 = D.pre_string();
	return(T1 == T2);
}


   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	return stream << D.to_string();	
}

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
	return (A.equals(B));
}

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
	Dictionary &ref = const_cast <Dictionary &>(D);
	if(this == &D){
		return *this;
	}
	Node* curr = ref.current;
	ref.begin();
	while(ref.current != this->nil){
		setValue(ref.current->key, ref.current->val);
		ref.next();
	}
	ref.current = curr;
	return *this;
	
}


