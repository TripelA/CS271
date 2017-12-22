//====================================================================
// Anamay Agnihotri and Aixin Li
// Submitted: November 10, 2017
// hash.h
// Hash implementation of list
//====================================================================

#include "list.h"
#ifndef HASH_H
#define HASH_H

using namespace std;

template <class KeyType>
class HashTable
{
    public:
        HashTable(int numSlots);
        HashTable(const HashTable<KeyType>& h);
        ~HashTable();
        KeyType* get( KeyType& k) const;
        void insert(KeyType *k);
        void remove( KeyType& k);
        HashTable<KeyType>& operator=(const HashTable<KeyType>& h);
        std::string toString(int slot) ;
        int length();
    private:
        int slots;
        List<KeyType> *table; // an array of List<KeyType>’s
};


#include "hash.cpp"
#endif

/*=========================================================================*/
