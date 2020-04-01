#include "Node.h"

template <class T>
Node<T>::Node(T val)
{
  this->value = val;
  this->left = NULL;
  this->right = NULL;
  this->parent = NULL;
  this->factor = 0;
}

template <class T>
T Node<T>::getVal()
{
  return this->value;
}

template <class T>
Node<T> *Node<T>::getParent()
{
  return this->parent;
}

template <class T>
Node<T> *Node<T>::getLeft()
{
  return this->left;
}

template <class T>
Node<T> *Node<T>::getRight()
{
  return this->right;
}

template <class T>
void Node<T>::setLeft(Node<T> *node)
{
  this->left = node;
  if (node != NULL)
  {
    node->setParent(this);
  }
}

template <class T>
void Node<T>::setRight(Node<T> *node)
{
  this->right = node;
  if (node != NULL)
  {
    node->setParent(this);
  }
}

template <class T>
void Node<T>::setParent(Node<T> *node)
{
  this->parent = node;
}

template <class T>
void Node<T>::delLeft()
{
  delete this->left;
  this->left = NULL;
}

template <class T>
void Node<T>::delRight()
{
  delete this->right;
  this->right = NULL;
}

template <class T>
void Node<T>::setFactor(int fac){
  this->factor = fac;
}

template <class T>
int Node<T>::getFactor(){
  return this->factor; 
}