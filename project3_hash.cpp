/*
* Name: Sarah Brown
* Course: DSA 5005 - Computing Structures
* Summer 2002
* Project 3: Hash Table
*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <string> 
#include <chrono>	// for finding execution time
#include <iterator> // for displaying list

using namespace std;

// ----------------------------------------------------------------------------
// hash table class
// ----------------------------------------------------------------------------
class hMap
{
private:
	unordered_map<int, list<string>*> wordHash; // hash table to store a list of strings

public:
	hMap();							// default constructor
	void insert(string str);		// insert into hash table
	int find(string str);			// find string in hash table
	int hashFunction(string str);	// hash function to find index where you will push the string
	void display();					// display function
};

// ----------------------------------------------------------------------------
// hMap default constructor
// ----------------------------------------------------------------------------
hMap::hMap() {
	for (int i = 0; i < 53; i++) {
		wordHash[i] = new list<string>();
	}
}

// ----------------------------------------------------------------------------
// hMap insert method
// ----------------------------------------------------------------------------
void hMap::insert(string str) {
	int i = hashFunction(str);
	if (i != -1) {	// ignores insert if string doesnt get mapped properly
		if (find(str) == -1) {
			wordHash[i]->push_front(str); // adds to front of list 
		}
	}
}

// ----------------------------------------------------------------------------
// hMap find method
// ----------------------------------------------------------------------------
int hMap::find(string str) {
	int i = hashFunction(str);	// gets index of where string should be in hash table
	if (i != -1) {				// ignores find if it doesnt get mapped properly
		if (wordHash[i] != NULL) {
			for (auto j = wordHash[i]->begin(); j != wordHash[i]->end(); j++) {	// iterates over list
				if (str.compare(*j) == 0) {
					return i;	// returns index of str location in hash if string is found
				}
			}
		}
	}

	return -1;
}

// ----------------------------------------------------------------------------
// hMap hash function method
// ----------------------------------------------------------------------------
int hMap::hashFunction(string str) {
	if (str.length() > 0) {						// checks that string is not an empty string
		if (str[0] >= 'A' && str[0] <= 'Z') {
			return (str[0] - 'A');				// A-Z at 0-25
		}
		else if (str[0] >= 'a' && str[0] <= 'z') {
			return (str[0] - (65+96-'[' ));		// a-z at 26-51
		}
		else if (str[0] >= '0' && str[0] <= '9') {
			return(52);							// stuffs 0-9 at the end of the hash
		}
		else {
			return -1;							// returns -1 if something unexpected happens. -1 gets ignored
		}
	}
	else {
		return -1;
	}
}

// ----------------------------------------------------------------------------
// hMap display method
// ----------------------------------------------------------------------------
void hMap::display() {
	for (int i = 0; i < 53; i++) {
		cout << "wordHash[" << i << "] ";
		for (auto j = wordHash[i]->begin(); j != wordHash[i]->end(); j++) { // iterates over list
			cout << "-> '" << *j << "' "; // displays contents of list
		}
		cout << endl;
	}
}

// ----------------------------------------------------------------------------
// main method to run code
// ----------------------------------------------------------------------------
int main()
{
	// object of hash table
	hMap* wordTable = new hMap();

	string word;

	cin >> word;

	auto start_add = chrono::high_resolution_clock::now(); // start timer for insertion 
	while (!cin.eof() && word.compare("FIND1!!") != 0) { // loops until end of find marker
		wordTable->insert(word);
		cin >> word;
	}
	auto stop_add = chrono::high_resolution_clock::now(); // end timer for execution
	auto duration_add = chrono::duration_cast<chrono::microseconds>(stop_add - start_add);
	cout << "Time taken to construct tree: " << duration_add.count() << " microseconds" << endl;

	// display hashtable
	cout << endl;
	wordTable->display();
	cout << endl;

	cin >> word;
	auto start_find = chrono::high_resolution_clock::now(); // start timer for find
	while (!cin.eof()) { // loops until end of file
		wordTable->find(word);
		cin >> word;
	}
	auto stop_find = chrono::high_resolution_clock::now(); // end timer for find
	auto duration_find = chrono::duration_cast<chrono::microseconds>(stop_find - start_find);
	cout << "Time taken to find x words: " << duration_find.count() << " microseconds" << endl;

	return 0;
}