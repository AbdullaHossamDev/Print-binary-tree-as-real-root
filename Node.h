#ifndef _Node_H_
#define _Node_H_
template <class T>
class Node
{
private:
	Node<T> *parent;
	Node<T> *left;
	Node<T> *right;
	T value;
	int factor;

public:
	Node(T val);

	T getVal();

	Node<T> *getParent();

	Node<T> *getLeft();

	Node<T> *getRight();

	void setLeft(Node<T> *node);

	void setRight(Node<T> *node);

	void setParent(Node<T> *node);

	void delLeft();

	void delRight(); 

	void setFactor(int fac);
	
	int getFactor();
};

#include "Node.cpp"
#endif