#include "assoc.h"
#include <iostream>

using namespace std;


/// <summary>
/// Initializes a new instance of the <see cref="assoc{T}"/> class.
/// </summary>
template<class T>
assoc<T>::assoc(int s)
{
	n_elements = 0;
	arraySize = s;
	assocArray = new pair*[arraySize];
	for (int i = 0; i < arraySize; i++)
		assocArray[i] = NULL;
	maxLoadFactor = .75;
}

/// <summary>
/// Initializes a new instance of the <see cref="assoc{T}"/> class.
/// </summary>
/// <param name="loadFactor">The load factor.</param>
/// <param name="size">The size.</param>
template<class T>
assoc<T>::assoc(int loadFactor, int size)
{
	arraySize = size;
	maxLoadFactor = loadFactor;
	assocArray = new pair*[arraySize];
	for (int i = 0; i < arraySize; i++)
		assocArray[i] = NULL;
	n_elements = 0;
}

/// <summary>
/// Determines whether [contains] [the specified key].
/// </summary>
/// <param name="key">The key.</param>
/// <returns>true if the key is contained in the assocArray, false otherwise</returns>
template<class T>
bool assoc<T>::contains(const string& key)
{
	int myhash = hash(key);
	if (assocArray[myhash] == NULL)
	{
		return false;
	}
	else
	{
		pair* myPair = assocArray[myhash];
		string myString = assocArray[myhash]->key;
		while (myPair != NULL)
		{
			string myString = myPair->key;
			if (key.compare(myString) == 0)
				return true;
			myPair = myPair->next;
		}
	}
	return false;
}
/// <summary>
/// Lookups the specified value.
/// </summary>
/// <param name="value">The value.</param>
/// <param name="key">The key.</param>
/// <returns>true if lookup successfull, otherwise false</returns>
template<class T>
bool assoc<T>::lookup(T& value, const string& key)
{
	int myhash = hash(key);
	if (assocArray[myhash] != NULL)
	{
		pair* curr = assocArray[myhash];
		while (curr != NULL)
		{
			if (curr != NULL && key == curr->key)
			{
				value = curr->value;
				return true;
			}
			curr = curr->next;
		}
	}
	return false;
}
/// <summary>
/// Inserts the specified key.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="value">The value.</param>
template<class T>
void assoc<T>::insert(const string& key, const T& value)
{
	double load = load_factor();
	double max = get_max_load_factor();
	if (load >= max)
	{
		pair** currentArray = new pair*[arraySize * 4];
		arraySize *= 4;
		for (int i = 0; i < arraySize; i++)
		{
			currentArray[i] = NULL;

		}
		for (int j = 0; j < arraySize / 4; j++)
		{
			if (assocArray[j] != NULL)
			{
				string key = assocArray[j]->key;
				int myhash = hash(key);
				pair* curr = assocArray[j]->next;
				assocArray[j]->next = NULL;
				currentArray[myhash] = assocArray[j];
				while (curr != NULL)
				{
					key = curr->key;
					myhash = hash(key);
					if (currentArray[myhash] == NULL)
						currentArray[myhash] = new pair(key, curr->value);
					else
					{
						bool valueInserted = false;
						pair* arraySpot = currentArray[myhash];
						if (arraySpot != NULL && arraySpot->key == key)
						{
							arraySpot = new pair(key, curr->value);
							valueInserted = true;
						}

						while (arraySpot->next != NULL)
						{
							arraySpot = arraySpot->next;
							if (arraySpot != NULL && arraySpot->key == key)
							{
								arraySpot->next = new pair(key, curr->value);
								valueInserted = true;
							}
						}
						if (!valueInserted && arraySpot->next == NULL)
							arraySpot->next = new pair(key, curr->value);
						curr = curr->next;
					}
				}
			}
		}
		delete[] assocArray;
		assocArray = currentArray;
	}
	int myhash = hash(key);
	if (assocArray[myhash] == NULL)
	{
		assocArray[myhash] = new pair(key, value);
	}
	else if (assocArray[myhash]->key == key)
	{
		assocArray[myhash] = new pair(key, value);
		return;
	}
	else
	{
		pair* curr = assocArray[myhash];
		while (curr->key != key && curr->next != NULL)
			curr = curr->next;
		if (curr->key == key)
		{
			curr = new pair(key, value);
			return;
		}
		else
			curr->next = new pair(key, value);
	}
	n_elements = n_elements + 1;
}
/// <summary>
/// Hashes the specified key.
/// </summary>
/// <param name="key">The key.</param>
/// <returns>int, the assocArray index</returns>
template<class T>
int assoc<T>::hash(const string& key)
{
	unsigned int hash = offset_basis;
	for (int i = 0; i < key.size(); i++)
	{
		hash = hash^key[i];
		hash *= prime;
	}
	return hash % arraySize;
}
/// <summary>
/// returns the Load_factor of this instance.
/// </summary>
/// <returns>double representing load factor of this instance</returns>
template<class T>
double assoc<T>::load_factor() const
{
	if (n_elements == 0)
		return 0;
	else
		return n_elements / arraySize;
}
/// <summary>
/// Get_max_load_factor for this instance.
/// </summary>
/// <returns>double maxLoadFactor</returns>
template<class T>
double assoc<T>::get_max_load_factor() const
{
	return maxLoadFactor;
}
/// <summary>
/// Prints the specified out.
/// </summary>
/// <param name="out">The out.</param>
template<class T>
void assoc<T>::print(ostream& out) const
{
	cout << "I was called to print" << endl;
}
/// <summary>
/// Set_max_load_factor for this instance.
/// </summary>
/// <param name="factor">The factor.</param>
template<class T>
void assoc<T>::set_max_load_factor(double factor)
{
	maxLoadFactor = factor;
}
/// <summary>
/// returns # of elements in this instance
/// </summary>
/// <returns>int n_elemenst</returns>
template<class T>
int assoc<T>::n() const
{
	return n_elements;
}
/// <summary>
///returns a vector of values contained in the hash table.
/// </summary>
/// <returns>vector<T> of values</returns>
template<class T>
vector<T> assoc<T>::values()
{
	vector<T> myVector;
	for (int i = 0; i < arraySize; i++)
		if (assocArray[i] != NULL)
		{
			myVector.push_back(assocArray[i]->value);
			pair* curr = assocArray[i].next;
			while (curr != NULL)
			{
				myVector.push_back(curr->value);
				curr = curr->next;
			}
		}
	return myVector;
}
