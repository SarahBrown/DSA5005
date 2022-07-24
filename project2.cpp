/*
* Name: Sarah Brown
* Course: DSA 5005 - Computing Structures
* Summer 2002
* Project 2: Trie Data Structure
*/

#include <iostream>
#include <list>
#include <iterator> // for displaying list

using namespace std; 

// ----------------------------------------------------------------------------
// function that returns length of char array
// ----------------------------------------------------------------------------
int array_size(char* a) {
	int size = 0;

	while (*a != '\0') {
		a++;
		size++;
	}

	return size;
}

// ----------------------------------------------------------------------------
// function that compares two char arrays
// ----------------------------------------------------------------------------
int array_cmp(char* a, char* b) {
	if (!a && b)
		return -1;
	else if (!a && !b)
		return 0;
	else if (a && !b)
		return 1;

	while ((*a != '\0') && (*b != '\0') && (*a == *b)) {
		a++;
		b++;
	}

	if ((*a == '\0') && (*b == '\0'))
		return 0;
	else if (*a > *b)
		return 1;
	else
		return -1;
}

// ----------------------------------------------------------------------------
// function that copies a char array
// ----------------------------------------------------------------------------
void array_cpy(char* a, char* b, int len) {
	for (int i = 0; i < len; i++) {
		a[i] = b[i];
	}
}

// ----------------------------------------------------------------------------
// function to use with sort algorithm to alphabetically sort in A-Z order
// ----------------------------------------------------------------------------
bool comparator_alpha(char* a, char* b) {
	return (array_cmp(a, b) < 0); // sort in ascending order
}

// ----------------------------------------------------------------------------
// class prototype - since it is a recursive class
// ----------------------------------------------------------------------------
template <class DT>
class TrieDS;

// ----------------------------------------------------------------------------
// Class definition for TrieNode to store node data for the Trie data structure
// ----------------------------------------------------------------------------
template <class DT>
class TrieNode
{
public:
	TrieDS<DT>* _next;	// pointing to the next address 
	list<DT>* _data;	// store the data as a list	
	TrieNode();
};

// ----------------------------------------------------------------------------
// TrieNode default constructor
// ----------------------------------------------------------------------------
template <class DT>
TrieNode<DT>::TrieNode()
{
	_next = NULL;
	_data = NULL;
}

// ----------------------------------------------------------------------------
// Class definition for travelData class to store multiple rows of data
// ----------------------------------------------------------------------------
template <class DT>
class TrieDS
{
public:
	TrieNode<DT>* myNodes;	// array of length 26 to store the TrieNodes
	int max_depth;			// max depth of structure
	int cur_depth;			// current depth of structure

	// default and non-default constructors
	TrieDS();									
	TrieDS(int max_depth, int cur_depth);

	int getCharPosition(DT str, int loc);		// returns the index position for the 
												// loc-th position character in str

	void insert(DT str);	// insert str to the structure depending on the depth
	void remove(DT str);	// remove str from the structure - make sure to 
							// check if the list is empty and set it to NULL when 
							// removing the last word from the list

	int find(DT str);		// find the the string str - return true or false 
	void displayMyNodes();	// display the entire myNodes array (list at each node)
};

// ----------------------------------------------------------------------------
// TrieDS default constructor
// ----------------------------------------------------------------------------
template <class DT>
TrieDS<DT>::TrieDS()
{
	myNodes = NULL;
	max_depth = 0;
	cur_depth = 0;
}

// ----------------------------------------------------------------------------
// TrieDS non-default constructor
// ----------------------------------------------------------------------------
template <class DT>
TrieDS<DT>::TrieDS(int d, int cur_d)
{
	max_depth = d;
	cur_depth = cur_d;
	myNodes = new TrieNode<DT>[26]();

}

// ----------------------------------------------------------------------------
// TrieDS method to return character position given an index value of a str
// ----------------------------------------------------------------------------
template <class DT>
int TrieDS<DT>::getCharPosition(DT str, int loc)
{
	return (str[loc]-'A'); // returns char value - ascii value of 'A'
}

// ----------------------------------------------------------------------------
// TrieDS method to to insert a new word
// ----------------------------------------------------------------------------
template <class DT>
void TrieDS<DT>::insert(DT str)
{
	int index = getCharPosition(str, cur_depth);	// gets ascii value of current depth char to use as list index
	if (cur_depth < max_depth-1) {					// check recursion depth
		if (myNodes[index]._next == NULL) {
			myNodes[index]._next = new TrieDS<char*>(max_depth, cur_depth + 1); // creates a new object of TrieDS
		}
		myNodes[index]._next->insert(str);			// recurses
	}

	else {
		if (myNodes[index]._data == NULL) {
			myNodes[index]._data = new list<DT>;		// creates a new list
		}
		myNodes[index]._data->push_back(str);			// adds word to list
		myNodes[index]._data->sort(comparator_alpha);	// sorts list again
	}
}

// ----------------------------------------------------------------------------
// TrieDS method to to remove a specific word
// ----------------------------------------------------------------------------
template <class DT>
void TrieDS<DT>::remove(DT str)
{
	int index = getCharPosition(str, cur_depth);	// gets ascii value of current depth char to use as list index
	if (cur_depth < max_depth-1) {					// check recursion depth
		if (myNodes[index]._next != NULL) {
			myNodes[index]._next->remove(str);		// recurses 
		}
	}

	else {
		if (myNodes[index]._data != NULL) {
			for (auto j = myNodes[index]._data->begin(); j != myNodes[index]._data->end(); j++) {
				if (array_cmp(str, *j) == 0) {
					myNodes[index]._data->erase(j); // removes word based on pointer info
					break;
				}
			}

			if (myNodes[index]._data->empty()) {
				delete(myNodes[index]._data);	// deletes list
				myNodes[index]._data = NULL;	// sets data pointer to NULL
			}
		}
	}
}

// ----------------------------------------------------------------------------
// TrieDS method to to find a specific word
// ----------------------------------------------------------------------------
template <class DT>
int TrieDS<DT>::find(DT str)
{
	int index = getCharPosition(str, cur_depth);	// gets ascii value of current depth char to use as list index
	if (cur_depth < max_depth-1) {					// check recursion depth
		if (myNodes[index]._next == NULL) {
			return 0;								// not found if next pointer is NULL
		}
		else {
			return myNodes[index]._next->find(str); // recurses 
		}
	}

	else {
		if (myNodes[index]._data == NULL) {
			return 0; // not found if data pointer is NULL
		}
		else { // search list
			for (auto j = myNodes[index]._data->begin(); j != myNodes[index]._data->end(); j++) {
				if (array_cmp(str, *j) == 0) {
					return 1; // returns true if match is found
				}
			}
		}
		return 0;
	}
}

// ----------------------------------------------------------------------------
// TrieDS method to to display the entire data structure
// ----------------------------------------------------------------------------
template <class DT>
void TrieDS<DT>::displayMyNodes()
{
	for (int i = 0; i < 26; i++) {
		if (myNodes[i]._next != NULL) {
			myNodes[i]._next->displayMyNodes(); // recurses while next is not null
		}

		else if (myNodes[i]._data != NULL) {
			for (auto j = myNodes[i]._data->begin(); j != myNodes[i]._data->end(); j++) {
				cout << *j << ' ';	// gets word from list
				cout << endl;		// displays each word on a different line
			}
		}
	}
}

// ----------------------------------------------------------------------------
// main method to run code
// ----------------------------------------------------------------------------
int main()
{
	// store variables required to parse input file
	char* tempWord = new char[20];
	char command;
	int mainDepth = 0;

	cin >> mainDepth; // read the depth from redirected input file

	TrieDS<char*> *myTrie = new TrieDS<char*>(mainDepth, 0); // object of TrieDS

	cin >> command; // reads in first command
	while (!cin.eof()) { // loops until end of file

		// checks to make sure command is not 'D' which is not followed by a word
		if (command != 'D') { 
			cin >> tempWord;
		}

		switch (command) { // switch statement to process the various commands
			// command I - Option I followed by a UPPER CASE WORD 
			// will insert the word in the appropriate list.
			case 'I': {
				// check to see if word is already in data structure
				if (!myTrie->find(tempWord)) {
					// copies word to memory					
					char* word = new char[array_size(tempWord) + 1];
					array_cpy(word, tempWord, array_size(tempWord) + 1);
					cout << "Inserting " << word << endl;
					myTrie->insert(word);  // calls insert method with copy of word
				}
				break;
			}

			// command R - Option R followed by a UPPER CASE WORD 
			// will remove the word from the appropriate list if present.
			case 'R': {
				// checks to see if word is in data structure 
				if (myTrie->find(tempWord)) {
					cout << "Removing " << tempWord << endl;
					myTrie->remove(tempWord); // and calls remove method if it is
				}
				break;
			}

			// command F - Option F followed by a UPPER CASE WORD will 
			// search for the word from the list and return true or false.
			case 'F': {
				cout << (myTrie->find(tempWord) == 0 ? "Not found " : "Found ") << tempWord << endl; // prints true if word is found, false if it is not
				break;
			}

			// command D - Option D will display the entire data structure.
			case 'D': {
				cout << "myTrie:" << endl;
				myTrie->displayMyNodes(); // displays data structure
				break;
			}

			// default command, do nothing
			default:
				break;
			}
		cout << endl;
		cin >> command;
	}

	return 0;
}

