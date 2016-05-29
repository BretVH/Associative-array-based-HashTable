/*
* File:   assoc.h
* Author: bret
*
* Created on March 7, 2014, 11:40 AM
*/

#ifndef ASSOC_H
#define	ASSOC_H

#include <string>
#include <vector>    
using namespace std;

const unsigned int prime = 16777619;
const unsigned int offset_basis = 2166136261;
template<class T> class assoc {
public:

	/* An internal structure is needed for the key/value pairs */
	struct pair {
		string key;   // key (always a string)
		T      value; // value associated with the key
		pair  *next;  // next in the chain (omit for open addressing)

		// Default constructor (if needed)
		pair() : key(), value(), next(NULL) {}

		// Basic constructor: sets the three fields
		pair(const string& key, T value, pair* next = NULL)
			: key(key), value(value), next(next) {}
	};


	/* Constructors */

	// intialializes the table to the given size
	assoc(int s = 4);

	assoc(int loadFactor, int size);


	// (The destructor is omitted)
	~assoc() { delete[] assocArray; }

	/* Basic operations */

	// Tests for containment of the given key in this table
	bool contains(const string& key);

	// Searches for the value associated with key in this table.
	// If it is found, value is set to the associated value and true
	// is returned; otherwise false is returned and value is unmodified.
	bool lookup(T& value, const string& key);

	// Associates value with key in this table,
	// replacing any existing association.
	void insert(const string& key, const T& value);


	/* Other operations */

	// Returns the total number of key/value pairs in this table
	int n() const;

	// Returns the load factor: the ratio of the number of pair to the table size
	double load_factor() const;

	// Returns the maximum allowable load factor.  If the actual load factor
	// exceeds this, the table will be resized.
	void set_max_load_factor(double factor);

	// Returns the current maximum load factor
	double get_max_load_factor() const;


	// All value extraction: the returned vector contains the value for each
	// key/value pair stored in this table.
	vector<T> values();

	// (Test Stuff)
	void print(ostream& out) const;
	friend int test_assoc(int, int);
private:
	int hash(const string& key);
	int n_elements;
	pair** assocArray;
	int arraySize;
	double maxLoadFactor;
};
#endif	/* ASSOC_H */
