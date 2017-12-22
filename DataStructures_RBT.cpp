//====================================================================
// Anamay Agnihotri and Aixin Li
// Submitted: November 17, 2017
// redblack.cpp
// RBT implementation of BST
//====================================================================

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
using namespace std;

//=========================================
// default constructor
// pre-condition: N/A
// post-condition: empty RBT
//=========================================
template <class KeyType>
  RedBlack<KeyType>::RedBlack()
{
  NIL = new Node<KeyType>();
  NIL->color = 'b';
  root = NIL;
}

//=========================================
// copy (helper function)
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
void RedBlack<KeyType>::copy(Node<KeyType>* ptr)
{
    if (ptr != NIL)
    {
      insertHelp(ptr);
      copy(ptr->left);
      copy(ptr->right);
    }
}

//=========================================
// copy constructor
// pre-condition: existing RBT
// post-condition: new RBT
//=========================================
template <class KeyType>
RedBlack<KeyType>::RedBlack(const RedBlack<KeyType> & ptr)
{
  root = NIL;
  copy(ptr.root);
}

//=========================================
// destroy
// pre-condition: existing BST
// post-condition: deleted BST
//=========================================
template <class KeyType>
void RedBlack<KeyType>::destroy(Node<KeyType>* ptr)
{
  if (ptr!=NIL)
  {
    destroy(ptr->left);
    destroy(ptr->right);
    delete ptr;
    ptr = NIL;
  }
}

//=========================================
// destructor
// pre-condition: root node
// post-condition: N/A
//=========================================
template <class KeyType>
RedBlack<KeyType>::~RedBlack()
{
  destroy(root);
  delete root;
}

//=========================================
// empty
// pre-condition: existing root node
// post-condition: N/A
//=========================================
template <class KeyType>
bool RedBlack<KeyType>::empty() const
{
  return (root == NIL);
}


//=========================================
// leftRotate
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
void RedBlack<KeyType>::leftRotate(Node<KeyType>* x)
{
  Node<KeyType>* y;
  y = x->right;
  if (x->parent!=NIL)
  {
    if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right=y;
  }
  else
    root = y;
  y->parent = x->parent;
  x->parent = y;
  x->right = y->left;
  y->left = x;
  x->right->parent = x;
}

//=========================================
// rightRotate
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
void RedBlack<KeyType>::rightRotate(Node<KeyType>* x)
{
  Node<KeyType>* y;
  y = x->left;
  //x->parent = y;
  if (x->parent!=NIL)
  {
    if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left=y;
  }
  else
    root = y;
  y->parent = x->parent;
  x->parent = y;
  x->left = y->right;
  y->right = x;
  x->left->parent = x;

}

//=========================================
// insertFix
// pre-condition: existing RBT
// post-condition: balanced RBT
//=========================================
template <class KeyType>
void RedBlack<KeyType>::insertFix(Node<KeyType>* ptr)
{
  //cout << "jhi " <<endl;
  Node<KeyType>* uncle = NULL;
  while (ptr->parent->color == 'r')
  {
    if (ptr->parent == ptr->parent->parent->left)
    {
      uncle = ptr->parent->parent->right;
      if (uncle->color == 'r')
      {
        ptr->parent->color = 'b';
        uncle->color = 'b';
        ptr->parent->parent->color = 'r';
        ptr = ptr->parent->parent;
      }
      else
      {
      if (ptr == ptr ->parent ->right)
      {
        ptr=ptr->parent;
        leftRotate(ptr);
      }
      ptr->parent->color='b';
      ptr->parent->parent->color = 'r';
      rightRotate(ptr->parent->parent);
    }
  }
    else
    {
      uncle = ptr->parent->parent->left;
      if (uncle->color == 'r')
      {
        ptr->parent->color = 'b';
        uncle->color='b';
        ptr->parent->parent->color='r';
        ptr=ptr->parent->parent;
      }
      else
      {
        if (ptr==ptr->parent->left)
        {
          ptr=ptr->parent;
          rightRotate(ptr);
        }
        ptr->parent->color = 'b';
        ptr->parent->parent->color='r';
        leftRotate(ptr->parent->parent);
      }
    }

  }
  root->color = 'b';
}

//=========================================
// insertHelp
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
void RedBlack<KeyType>::insertHelp(Node<KeyType>* ptr)
{
  Node<KeyType>* y = NIL;
  Node<KeyType>* x = root;
  while (x != NIL)
  {
    y = x;
    if (*(ptr -> data) < *(x ->data))  //check if it is star
      x = x->left;
    else
      x = x->right;
  }
  ptr -> parent = y;
  if (y == NIL)
    root = ptr;   //tree was empty
  else if (*(ptr -> data) < *(y -> data))
    y ->left = ptr;    //left child
  else
    y ->right = ptr;  //right child
  ptr->left = NIL;
  ptr->right = NIL;
  ptr->color = 'r';
  insertFix(ptr);
}

//=========================================
// insert
// pre-condition: existing RBT
// post-condition: RBT with inserted value
//=========================================
template <class KeyType>
void RedBlack<KeyType>::insert(KeyType* k)
{
  Node<KeyType>* qtr = new Node<KeyType>();
  qtr->left = NIL;
  qtr->right= NIL;
  qtr->parent= NIL;
  qtr -> data = k;
  insertHelp(qtr);
}

//=========================================
// getHelp (recursive helper method for get)
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
Node<KeyType>* RedBlack<KeyType>::getHelp(Node<KeyType>* ptr, const KeyType& k)const
{
  if (ptr == NIL)
    return NIL;
  if (*(ptr -> data) == k)
    return ptr;
  if (*(ptr -> data) < k)
    return getHelp(ptr->right,k);
  if (*(ptr -> data) > k)
    return getHelp(ptr->left,k);
  else
  {
    throw KeyError();
  }
}

//=========================================
// get
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
KeyType* RedBlack<KeyType>::get(const KeyType& k) const
{
  Node<KeyType> *temp = getHelp(root,k);
  if(temp == NIL)
    return NIL->data ;
  return temp ->data;
}

//=========================================
// removeFix
// pre-condition: existing RBT
// post-condition: balanced RBT
//=========================================
template <class KeyType>
void RedBlack<KeyType>::removeFix(Node<KeyType>* x)
{
//  cout << "kakakka" <<endl;
  while ((x != root) and (x->color == 'b'))
  {
      if (x == x -> parent -> left)
      {
          Node<KeyType>* w;
          w = x-> parent->right;
          if (w->color == 'r')     //case1
          {
            w->color = 'b';
            x->parent->color='r';
            leftRotate(x->parent);
            w = x->parent -> right;
          }
          if ((w->left->color == 'b') and (w->right->color =='b'))  //case2
          {
            w->color = 'r';
            x = x->parent;
          }
          else
          {
            if (w->right->color == 'b')
            {
              w->left->color='b';
              w->color='r';
              rightRotate(w);
              w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = 'b';
            w->right->color = 'b';
            leftRotate(x->parent);
            x = root;
          }
      }
      else
      {
        Node<KeyType>* w;
        w = x-> parent->left;
        if (w->color == 'r')     //case1
        {
          w->color = 'b';
          x->parent->color='r';
          rightRotate(x->parent);
          w = x->parent -> left;
        }
        if ((w->right->color == 'b') and (w->left->color =='b'))  //case2
        {
          w->color = 'r';
          x = x->parent;
        }
        else
        {
          if (w->left->color == 'b')
          {
            w->right->color='b';
            w->color='r';
            leftRotate(w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = 'b';
          w->left->color = 'b';
          rightRotate(x->parent);
          x = root;
       }
     }
}
  x->color = 'b';
}

//=========================================
// transplant
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
void RedBlack<KeyType>::transplant(Node<KeyType>* u, Node<KeyType>* v)
{
  if (u->parent == NIL)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;

}

//=========================================
// remove
// pre-condition: existing RBT
// post-condition: RBT with removed value
//=========================================
template <class KeyType>
void RedBlack<KeyType>::remove(const KeyType& k)
{
  Node<KeyType> *del = getHelp(root,k);
  Node<KeyType> *y = del;
  Node<KeyType> *x;
  char ccolor = y->color;

  if (del->left == NIL)
  {
     x = del->right;
     transplant(del, del->right);
  }
  else if (del->right == NIL)
  {
     x = del->left;
     transplant(del, del->left);
  }
  else
   {
     y = minimumHelp(del->right);
     cout << *(y->data) <<endl;
     ccolor = y->color;
      x = y->right;

     if (y->parent == del)
     {
        x->parent = y;
      }
     else
     {
       transplant(y, y->right);
       y->right = del->right;
       y->right->parent = y;
     }

     transplant(del,y);
     y->left = del->left;
     y->left->parent = y;
     y->color = del->color;

    }
    if (ccolor == 'b')
      removeFix(x);
}

//=========================================
// maximumHelp
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
Node<KeyType>* RedBlack<KeyType>::maximumHelp(Node<KeyType>* k)const
{
  Node<KeyType>* ptr = k;
  if (ptr == NIL)
		return NIL;
	if (ptr->right == NIL)
		return ptr;
	else
		return maximumHelp(ptr->right);
}


//=========================================
// maximum
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
KeyType* RedBlack<KeyType>::maximum() const
{
  return maximumHelp(root) ->data;
}

//=========================================
// minimumHelp
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
Node<KeyType>* RedBlack<KeyType>::minimumHelp(Node<KeyType>* k)const
{
  Node<KeyType>* ptr = k;
  if (ptr == NIL)
		return NIL;
	if (ptr->left == NIL)
		return ptr;
	else
		return minimumHelp(ptr->left);
}

//=========================================
// minimum
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
KeyType* RedBlack<KeyType>::minimum()const
{
  return minimumHelp(root)->data;
}

//=========================================
// successorHelp
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
Node<KeyType>* RedBlack<KeyType>::successorHelp(Node<KeyType>* k)const
{
    Node<KeyType>* ptr;
    if (k->right != NIL)
      return minimumHelp(k->right);
    else
    {
      ptr = k->parent;
      while((ptr!=NIL) and (k == ptr->right))
      {
        k = ptr;
        ptr = ptr->parent;
      }
      return ptr;
    }
}

//=========================================
// successor
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
KeyType* RedBlack<KeyType>:: successor(const KeyType& k) const
{
  if (empty())
    throw "Empty!";
  else
    return successorHelp(getHelp(root,k))->data;
}

//=========================================
// predecessorHelp
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
Node<KeyType>* RedBlack<KeyType>::predecessorHelp(Node<KeyType>* k)const
{
  Node<KeyType>* ptr;
  if (k->left != NIL)
    return maximumHelp(k->left);
  else
  {
    ptr = k->parent;
    while((ptr!=NIL) and (k == ptr->left))
    {
      k = ptr;
      ptr = ptr->parent;
    }
    return ptr;
  }

}

//=========================================
// predecessor
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
KeyType* RedBlack<KeyType>::predecessor(const KeyType& k) const
{
  return predecessorHelp(getHelp(root,k))->data;
}

//=========================================
// inorderHelp
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
string RedBlack<KeyType>::inorderHelp(Node<KeyType>* k)const
{
  stringstream ls;
  if (k != NIL)
  {
    ls << inorderHelp(k->left);
    ls << *(k->data) << " " ;
    ls << inorderHelp(k->right);
  }
  return ls.str();
}

//=========================================
// inorder
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
string RedBlack<KeyType>::inOrder()const
{
    string pls;
    pls = inorderHelp(root);
   return pls.substr(0,pls.length()-1);
}

//=========================================
// preorderHelp
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
string RedBlack<KeyType>::preorderHelp(Node<KeyType>* k)const
{
  stringstream ls;
  if (k != NIL)
  {
    ls << *(k->data) << " " ;
    ls<< preorderHelp(k->left);
    ls<<preorderHelp(k->right);
  }
  return ls.str();
}

//=========================================
// preorder
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
string RedBlack<KeyType>::preOrder()const
{
  string pls;
  pls = preorderHelp(root);
  return pls.substr(0,pls.length()-1);
}

//=========================================
// postorderHelp
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
string RedBlack<KeyType>::postorderHelp(Node<KeyType>*k)const
{
  stringstream ls;
  if (k != NIL)
  {
    ls<<postorderHelp(k->left);
    ls<<postorderHelp(k->right);
    ls << *(k->data) << " " ;
  }
  return ls.str();
}

//=========================================
// postorder
// pre-condition: existing RBT
// post-condition: N/A
//=========================================
template <class KeyType>
string RedBlack<KeyType>::postOrder() const
{
  string pls;
  pls = postorderHelp(root);
  return pls.substr(0,pls.length()-1);
}

//=========================================
// assignment operator
// pre-condition: existing RBT
// post-condition: assigned RBT
//=========================================
template <class KeyType>
 RedBlack<KeyType>& RedBlack<KeyType>::operator= (const RedBlack<KeyType>& k) const
{
    if (&k != this)
    {
      destroy(k.root);
      copy(k.root);
    }
    return *this;
}

/*=========================================================================*/
