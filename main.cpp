#include <iostream>
#include <string>
#include "cstdio"
#include "assoc.h"
#include "assoc.cpp"

using namespace std;
/*****************/
/* Testing Stuff */
/*****************/

int test_assoc(int trials, int max)
{
	char buf[256];
	int errors = 0;

	int *values = new int[max];

	for (int n = 0; n < trials; n++) {
		// construct the table
		assoc<int*> table;
		if (table.n() != 0) {
			cerr << "n() returned nonzero on a newly created table" << endl;
			errors++;
		}

		// initialize the test values
		for (int k = 0; k < max; k++)
			values[k] = 2 * (n*max + k) + 1;

		for (int k = 0; k < max; k++) {
			// Construct a new key having the form "n:k"
			sprintf(buf, "%d:%d", n, k);
			string key(buf);

			// the key is unique and should not be there
			if (table.contains(key)) {
				cerr << "False positive in containment test of '" << key << "'" << endl;
				errors++;
			}

			// the value is a pointer to an integer
			int* value = values + k;

			// insert the value, given the key
			table.insert(key, value);

			// the number of elements should now be one more than 'k'
			int n_elem = table.n();
			if (n_elem != k + 1) {
				cerr << "invalid element count\n";
				errors++;
			}

			// the table should now contain 'key'
			if (!table.contains(key)) {
				cerr << "contains() returned false for the key just added" << endl;
				errors++;
			}

			// test lookup of what we just inserted
			int* result;
			if (!table.lookup(result, key)) {
				cerr << "Lookup of '" << key << "' failed after insertion" << endl;
			}
			else if (result != value || *result != values[k]) {
				cerr << "Lookup of '" << key << "' ";
				cerr << "gave wrong value ";
				cerr << "(immediately after insertion)" << endl;
				errors++;
			}

		} // (end of 'k' loop)

		//cerr << "min bucket count: " << table.min_bucket() << "\n";
		//cerr << "max bucket count: " << table.max_bucket() << "\n";
		//table.print(cerr);

		for (int k = 0; k < max; k++) {
			sprintf(buf, "%d:%d", n, k);
			string key(buf);

			// the table should contain 'key'
			if (!table.contains(key)) {
				cerr << "contains() returned false for a known key" << endl;
				errors++;
			}

			// test lookup 
			int* result;
			if (!table.lookup(result, key)) {
				cerr << "Lookup of '" << key << "' failed" << endl;
			}
			if (!result || result != values + k || *result != values[k]) {
				cerr << "Lookup of '" << key << "' ";
				cerr << "gave wrong value " << endl;
				errors++;
			}

		} // (end of 'k' loop)

	}

	// free up the 'values' array
	delete[] values;

	cerr << errors << " error" << (errors == 1 ? "" : "s") << " "
		<< "(max = " << max << ", trials = " << trials << ")" << endl;

	return errors;
}


// Possible 'main'

int main(int argc, char *argv[])
{
	test_assoc(1, 16);
	test_assoc(1, 2000000);
}
