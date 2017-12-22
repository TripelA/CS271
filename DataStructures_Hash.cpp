//====================================================================
// Anamay Agnihotri and Aixin Li
// Submitted: November 10, 2017
// hash.cpp
// Hash implementation of list
//====================================================================

#include <iostream>
using namespace std;

//=========================================
// default constructor
// pre-condition: N/A
// post-condition: empty BST
//=========================================
template<class KeyType>
HashTable<KeyType>::HashTable(int numSlots)
{
  slots = numSlots;
  table= new List<KeyType> [slots];
}

//=========================================
// copy constructor
// pre-condition: existing Hash
// post-condition: new hash created from exisiting one.
//=========================================
template<class KeyType>
HashTable<KeyType>::HashTable(const HashTable<KeyType>& h)
{
    slots = h.slots;
    table = new List<KeyType> [slots];
    for (int i = 0; i < h.slots;i++)
    {
       if (h.table[i].length() != 0)
         table[i] = h.table[i];
    }
}

//=========================================
// assignment operator
// pre-condition: existing Hash
// post-condition: assigned Hash
//=========================================
template<class KeyType>
HashTable<KeyType>& HashTable<KeyType>::operator=(const HashTable<KeyType>& h)
{
  Node<KeyType> * mnode;
  Node<KeyType> * dnode;
  for (int i = 0; i < slots;i++)
  {
    for (int j = 0; j < table[i].length();j++)
    {
      mnode = table[i][j];
      dnode = mnode;
      mnode = mnode->next;
      delete mnode;
    }

  }
  slots = h.slots;
  table = new List<KeyType> [slots];
  for (int i = 0; i < h.slots;i++)
  {
     if (h.table[i].length() != 0)
       table[i] = h.table[i];
  }
    return *this;
}

//=========================================
// destructor
// pre-condition: existing hash
// post-condition: N/A
//=========================================
template<class KeyType>
HashTable<KeyType>::~HashTable()
{
  delete [] table; // deletes array
}

//=========================================
// length method
// pre-condition: existing hash
// post-condition: N/A
//=========================================
template<class KeyType>
int HashTable<KeyType>::length()
{
  return slots;
}

//=========================================
// get method
// pre-condition: existing hash
// post-condition: N/A
//=========================================
template<class KeyType>
KeyType* HashTable<KeyType>::get( KeyType& k) const
{
  KeyType* track;
  int s = k.hash(slots);
  int i = 0;
  int remaincount = table[s].length();
  while ((*table[s][i] != k) && (remaincount !=0 ))
  {
      i++;
      remaincount--;
  }
  if (remaincount == 0)
    cout << "NOT FOUND" <<endl;
  else
    track = table[s][i];   //depends on list file
  return track;
}

//===============================
//insert method
// pre-condition: existing hash
// post-condition: existing hash with inserted k
//====================================
template<class KeyType>
void HashTable<KeyType>::insert(KeyType *k)
{
  int s = k->hash(slots);
  table[s].append(k);
}

//=====================================
// toString method
// pre-condition: N/A
// post-condition: N/A
//=====================================
template<class KeyType>
std::string HashTable<KeyType>::toString(int k)
{
   slots = k;
   std::stringstream ss;
   for ( int i = 0; i < slots; i++ )
    {
      ss << table[i].toString();
    }
    return ss.str();
}

//===========================================
//remove
// pre-condition: exisiting hash
// post-condition: hash with removed k
//==========================================
template<class KeyType>
void HashTable<KeyType>::remove(KeyType& k)
{
  int s = k.hash(slots);
  int i = 0;
  int remaincount = table[s].length();
  while ( (*table[s][i] != k) && (remaincount !=0 ))
  {
      i++;
      remaincount--;
  }
  if (remaincount!=0)
    table[s].remove(k);        // remove the first occurrence of the value item
}
/*=========================================================================*/
