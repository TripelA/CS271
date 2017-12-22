//====================================================================
// Anamay Agnihotri and Aixin Li
// Submitted: November 17, 2017
// redblack.h
// RBT class definition of BST
//====================================================================

#ifndef REDBLACK_H
#define REDBLACK_H
#include <iostream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;


//========================================
template <class KeyType>
struct Node
{
  KeyType* data;
  Node* parent;
  Node* left;
  Node* right;
  char color;
  Node()
  {
    data = NULL;
    parent = NULL;
    left = NULL;
    right = NULL;
    color = 'r';
  }
};
//========================================

template <class KeyType>
class RedBlack
{
public:

  RedBlack();                                          //default constructor
  RedBlack(const RedBlack<KeyType> &);                 //copy constructor
  ~RedBlack();                                         //destructor

  bool empty() const;



   KeyType* get(const KeyType& k) const;
   void insert(KeyType* k);//
   void remove(const KeyType& k);//
   KeyType* maximum()const;//
   KeyType* minimum()const;//
   KeyType* successor(const KeyType& k) const;//
   KeyType* predecessor(const KeyType& k) const;//
   string inOrder() const;//
   string preOrder() const;//
   string postOrder()const;//

   RedBlack<KeyType>& operator= (const RedBlack<KeyType>& tree) const;

private:
  Node<KeyType>* root;
  Node<KeyType>* NIL;
  void leftRotate(Node<KeyType>*);
  void rightRotate(Node<KeyType>*);
  void insertHelp(Node<KeyType>* );            //recursive helper method for insert
  void insertFix(Node<KeyType>* );
  void removeFix(Node<KeyType>* );
  void transplant(Node<KeyType>* ,Node<KeyType>* );

  Node<KeyType>* getHelp(Node<KeyType>* ptr, const KeyType& k)const;     //recursive helper method for get
   Node<KeyType>* successorHelp(Node<KeyType>*)const;
   Node<KeyType>* predecessorHelp(Node<KeyType>*)const;
   Node<KeyType>* maximumHelp(Node<KeyType>*)const;
   Node<KeyType>* minimumHelp(Node<KeyType>*)const;
   string inorderHelp(Node<KeyType>*)const;
   string preorderHelp(Node<KeyType>*)const;
   string postorderHelp(Node<KeyType>*)const;
   void copy(Node<KeyType>*);
   void destroy(Node<KeyType>*);



};

class KeyError{};
#include "redblack.cpp"
#endif

/*=========================================================================*/
