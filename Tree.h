#include "Node.h"
#include <map>
#include <string>
using namespace std;
#ifndef _Tree_H_
#define _Tree_H_
template <class T>
class Tree
{
private:
  Node<T> *root;
  Node<T> *searchKey(T key);
  Node<T> *get_ST_big(Node<T> *node);
  Node<T> *get_ST_small(Node<T> *node);
  void Inorder(Node<T> *root);

  int height(Node<T> *root);

  int BalanceFactor(Node<T> *root);

  void rightRotate(Node<T> *root);

  void leftRotate(Node<T> *root);
public:
  Tree();

  void push(T val);

  void del(T key);

  void Postorder();

  void Inorder();

  void Preorder();

  ~Tree();

  void print();

  string collectSTR(Node<T> *root);

  void printHeight();

  void EditBalanceFactor();

  Node<T> * getFirstHeigherFactor(Node<T> *root);

};

#include "Tree.cpp"
#endif