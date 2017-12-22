//====================================================================
// Anamay Agnihotri and Aixin Li
// Submitted: November 10, 2017
// test_hash.cpp
// Hash test file for some KeyType class Element
//====================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include "hash.h"
#include "list.h"
#include "dictionhash.h"

using namespace std;

class Element
{
  public:
	int key;


    Element() {key = 0;}
  	Element(int initKey) { key = initKey; }
  	~Element() { };
  	int hash(int slots);

  	bool operator<(const Element &other) const;
  	bool operator==(const Element &other) const;
  	bool operator!=(const Element &other) const;
  	friend ostream &operator<<(ostream &strm, Element &e);
};

bool Element::operator<(const Element &other) const
{
    return key < other.key;
}

bool Element::operator==(const Element &other) const
{
    return key == other.key;
}

bool Element::operator!=(const Element &other) const
{
    return key != other.key;
}

ostream &operator<<(ostream &strm, Element &e)
{
	strm << e.key;
	return strm;
}

int Element::hash(int slots)
{
	return key % slots;
}

void constTest()
{
  HashTable<Element> a(10); // empty Hash
  assert(a.toString(10) == "[][][][][][][][][][]");
}

void copyTest()
{
  HashTable<Element> b(10);
  Element e(10), f(24), g(2),h(17), i(33), j(12),k(22), l(27), m(3);
  b.insert(&e);
  b.insert(&f);
  b.insert(&g);
  b.insert(&h);
  b.insert(&i);
  b.insert(&j);
  b.insert(&k);
  b.insert(&l);
  b.insert(&m);
  HashTable<Element> a(b);
  assert(a.toString(10) == "[10][][2, 12, 22][33, 3][24][][][17, 27][][]");

}

void insertTest()
{
  HashTable<Element> b(10);
  Element e(10), f(24), g(2),h(17), i(33), j(12),k(22), l(27), m(3);
  b.insert(&e);
  b.insert(&f);
  b.insert(&g);
  b.insert(&h);
  b.insert(&i);
  b.insert(&j);
  b.insert(&k);
  b.insert(&l);
  b.insert(&m);
  assert(b.toString(10) == "[10][][2, 12, 22][33, 3][24][][][17, 27][][]");

}

void removeTest()
{
  HashTable<Element> b(10);
  Element e(10), f(24), g(2),h(17), i(33);
  b.insert(&e);
  b.insert(&f);
  b.insert(&g);
  b.insert(&h);
  b.insert(&i);
  b.remove(f);
  assert(b.toString(10) == "[10][][2][33][][][][17][][]");
  b.remove(i);
  assert(b.toString(10) == "[10][][2][][][][][17][][]");
  b.remove(g);
  try {*b.get(g);}
  catch (IndexError)
  {
    cout << "Error: Value not in table!" << endl;
  }

}

void getTest()
{
  HashTable<Element> b(10);
  Element e(10), f(24), g(2),h(17), i(33);
  b.insert(&e);
  b.insert(&f);
  b.insert(&g);
  b.insert(&h);
  b.insert(&i);
  assert(*b.get(g) == 2);
  b.remove(h);
  try {*b.get(h);} // element already removed
  catch (IndexError)
  {
    cout << "Error: Value not in table!" << endl;
  }

}

void assignTest()
{
  HashTable<Element> b(10);
  Element e(10), f(24), g(2),h(17), i(33);
  b.insert(&e);
  b.insert(&f);
  b.insert(&g);
  b.insert(&h);
  b.insert(&i);
  assert(b.toString(10) == "[10][][2][33][24][][][17][][]");
  HashTable<Element> a = b;
  assert(a.toString(10) == "[10][][2][33][24][][][17][][]");
}

void lengthTest()
{
  HashTable<Element> b(10);
  assert(b.length() == 10);
  HashTable<Element> c(100);
  assert(c.length() == 100);
}

int main()
{
   constTest();
   copyTest();
   insertTest();
   removeTest();
   getTest();
   assignTest();
   lengthTest();

   return 0;
}

/*=========================================================================*/
