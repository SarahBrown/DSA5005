/*
* Name: Sarah Brown
* Course: DSA 5005 - Computing Structures
* Summer 2002
* Project 3: Binary Search Tree
*/


#include <iostream>
#include <string>
#include <chrono>

using namespace std;

// ----------------------------------------------------------------------------
// class to store the strings in a BST
// ----------------------------------------------------------------------------
class nodeBST {
	string data;
	nodeBST* left;
	nodeBST* right;

public:
	nodeBST();					// default constructor
	nodeBST(string d);			// non default constructor
	void setData(string d);		// setter for data
	string getData();			// getter for data
	void setLeft(nodeBST* L);	// setter for left node
	void setRight(nodeBST* R);	// setter for right node
	nodeBST* getLeft();			// getter for left node
	nodeBST* getRight();		// getter for right node
	void insert(string d);		// insertion into BST
	bool find(string d);		// find a string
};

// ----------------------------------------------------------------------------
// nodeBST default constructor
// ----------------------------------------------------------------------------
nodeBST::nodeBST() {
	data = "";
	left = NULL;
	right = NULL;
}

// ----------------------------------------------------------------------------
// nodeBST non-default constructor
// ----------------------------------------------------------------------------
nodeBST::nodeBST(string d) {
	data = d;
	left = NULL;
	right = NULL;
}

// ----------------------------------------------------------------------------
// nodeBST setter for data
// ----------------------------------------------------------------------------
void nodeBST::setData(string d) {
	data = d;
}

// ----------------------------------------------------------------------------
// nodeBST getter for data
// ----------------------------------------------------------------------------
string nodeBST::getData() {
	return data;
}

// ----------------------------------------------------------------------------
// nodeBST setter for left node
// ----------------------------------------------------------------------------
void nodeBST::setLeft(nodeBST* L) {
	left = L;
}

// ----------------------------------------------------------------------------
// nodeBST setter for right node
// ----------------------------------------------------------------------------
void nodeBST::setRight(nodeBST* R) {
	right = R;
}

// ----------------------------------------------------------------------------
// nodeBST getter for left node
// ----------------------------------------------------------------------------
nodeBST* nodeBST::getLeft() {
	return left;
}

// ----------------------------------------------------------------------------
// nodeBST getter for right node
// ----------------------------------------------------------------------------
nodeBST* nodeBST::getRight() {
	return right;
}

// ----------------------------------------------------------------------------
// nodeBST insert method
// ----------------------------------------------------------------------------
void nodeBST::insert(string d) {
	// compare d to data in node
	// if equal, do not insert. done by not comparing >= or <= so equals is not checked
	if (data.compare(d) > 0) { 			// if less than, insert left 
		if (left == NULL) {				// check for more data on left
			left = new nodeBST(d);		// creates new node if it doesnt exist
		}
		else {
			left->insert(d);			// inserts left
		}
	}

	else if (data.compare(d) < 0) {		// if greater than, insert right
		if (right == NULL) {			// check for more data on left
			right = new nodeBST(d);		// creates new node if it doesnt exist
		}
		else {
			right->insert(d);			// inserts right
		}
	}
}

// ----------------------------------------------------------------------------
// nodeBST find method
// ----------------------------------------------------------------------------
bool nodeBST::find(string d) {
	if (data.compare(d) == 0) return true;	// if strings are equal, string is found

	else if (data.compare(d) > 0) {			// else check left branch if it is less than root
		if (left == NULL) {	
			return false;
		}
		else {
			left->find(d);
		}
	}

	else if (data.compare(d) < 0) {			// else check right branch if it is greater than root
		if (right == NULL) {				
			return false;
		}
		else {
			right->find(d);
		}
	}
	else {
		return false;
	}
}

// ----------------------------------------------------------------------------
// display method to recursively display the tree in an inorder traversal format
// ----------------------------------------------------------------------------
void display_tree(nodeBST* root) {
	if (root == NULL) return;
	display_tree(root->getLeft());
	cout << root->getData() << " ";
	display_tree(root->getRight());
}

// ----------------------------------------------------------------------------
// main method to run code
// ----------------------------------------------------------------------------
int main()
{
	// object of nodeBST class
	nodeBST* wordBST = new nodeBST();

	string word;

	cin >> word;
	wordBST->setData(word); // set the root word
	cin >> word; // reads in next word to work with cin.eof()

	auto start_add = chrono::high_resolution_clock::now(); // start timer for insertion 
	while (!cin.eof() && word.compare("FIND1!!") != 0) { // loops until end of find marker
		wordBST->insert(word);
		cin >> word;
	}
	auto stop_add = chrono::high_resolution_clock::now(); // end timer for execution
	auto duration_add = chrono::duration_cast<chrono::microseconds>(stop_add - start_add);
	cout << "Time taken to construct tree: " << duration_add.count() << " microseconds" << endl;

	cout << endl;
	display_tree(wordBST);
	cout << endl;
	cout << endl;

	cin >> word;
	auto start_find = chrono::high_resolution_clock::now(); // start timer for find
	while (!cin.eof()) { // loops until end of file
		wordBST->find(word);
		cin >> word;
	}
	auto stop_find = chrono::high_resolution_clock::now();	// end timer for find
	auto duration_find = chrono::duration_cast<chrono::microseconds>(stop_find - start_find);
	cout << "Time taken to find  x words: " << duration_find.count() << " microseconds" << endl;

	return 0;
}