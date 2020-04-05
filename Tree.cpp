#include "Tree.h"
#include <string>
#include <map>
#include <iterator>
#include <sstream>

using namespace std;

template <class T>
Tree<T>::Tree()
{
  this->root = NULL;
}

template <class T>
Node<T> *Tree<T>::searchKey(T key)
{
  if (this->root == NULL)
  {
    return NULL;
  }

  Node<T> *itr = this->root;
  while (itr && itr->getVal() != key)
  {
    if (itr->getVal() <= key)
    {
      itr = itr->getRight();
    }
    else
    {
      itr = itr->getLeft();
    }
  }
  return itr;
}

template <class T>
Node<T> *Tree<T>::get_ST_big(Node<T> *node)
{

  while (node->getLeft() != NULL)
  {
    node = node->getLeft();
  }
  return node;
}

template <class T>
Node<T> *Tree<T>::get_ST_small(Node<T> *node)
{
  while (node->getRight() != NULL)
  {
    node = node->getRight();
  }
  return node;
}

template <class T>
void Tree<T>::push(T val)
{
  if(this->searchKey(val)){
    return;
  }
  cout << "ADD " << val << endl;
  Node<T> *newNode = new Node<T>(val);
  if (this->root == NULL)
  {
    this->root = newNode;
    return;
  }

  Node<T> *itr = this->root;
  while (newNode->getParent() == NULL)
  {
    if (itr->getVal() <= val)
    {
      if (itr->getRight() == NULL)
      {
        itr->setRight(newNode);
      }
      else
      {
        itr = itr->getRight();
      }
    }
    else
    {
      if (itr->getLeft() == NULL)
      {
        itr->setLeft(newNode);
      }
      else
      {
        itr = itr->getLeft();
      }
    }
  }
  this->EditBalanceFactor();

  itr = this->getFirstHeigherFactor(newNode);

  int factor = itr->getFactor();

  if (factor > 1 && val > itr->getRight()->getVal())
  {
    this->leftRotate(itr);
  }
  else if (factor > 1 && val < itr->getRight()->getVal())
  {
    this->rightRotate(itr->getRight());
    this->leftRotate(itr);
  }
  else if (factor < -1 && val < itr->getLeft()->getVal())
  {
    this->rightRotate(itr);
  }
  else if (factor < -1 && val > itr->getLeft()->getVal())
  {
    this->leftRotate(itr->getLeft());
    this->rightRotate(itr);
  }
}

template <class T>
void Tree<T>::del(T key)
{
  Node<T> *delNode = this->searchKey(key);
  if (delNode == NULL)
  {
    return;
  }
  else
  {
    if (delNode == this->root)
    {

      Node<T> *dump = new Node<T>(-1);

      this->root->setParent(dump);

      dump->setRight(this->root);

      this->root = dump;
      del(key);
      this->root = this->root->getRight();
      if (this->root == NULL)
      {
        delete dump;
        return;
      }
      this->root->setParent(NULL);
      if (this->root->getRight() == NULL)
      {
        delete dump;
        return;
      }
      this->root->getRight()->setParent(this->root);

      delete dump;
      return;
    }
    if (delNode->getLeft() && delNode->getRight())
    {
      if (delNode->getVal() < delNode->getParent()->getVal())
      {
        Node<T> *st_big = get_ST_big(delNode->getRight());

        if (st_big == delNode->getRight())
        {
          delNode->getParent()->setLeft(st_big);

          st_big->setParent(delNode->getParent());

          st_big->setLeft(delNode->getLeft());
        }
        else
        {
          st_big->getParent()->setLeft(st_big->getRight());
          if (st_big->getRight())
          {
            st_big->getRight()->setParent(st_big->getParent());
          }
          st_big->setRight(delNode->getRight());
          st_big->setLeft(delNode->getLeft());
          st_big->setParent(delNode->getParent());

          delNode->getParent()->setLeft(st_big);
        }
      }
      else
      {
        Node<T> *st_small = get_ST_small(delNode->getLeft());

        if (st_small == delNode->getLeft())
        {
          delNode->getParent()->setRight(st_small);

          st_small->setParent(delNode->getParent());

          st_small->setRight(delNode->getRight());
        }
        else
        {
          st_small->getParent()->setRight(st_small->getLeft());
          if (st_small->getLeft())
          {
            st_small->getLeft()->setParent(st_small->getParent());
          }

          st_small->setRight(delNode->getRight());
          st_small->setLeft(delNode->getLeft());
          st_small->setParent(delNode->getParent());

          delNode->getParent()->setRight(st_small);
        }
      }
    }
    else if (delNode->getLeft())
    {
      if (delNode->getVal() < delNode->getParent()->getVal())
      {
        delNode->getParent()->setLeft(delNode->getLeft());
      }
      else
      {
        delNode->getParent()->setRight(delNode->getLeft());
      }
    }
    else if (delNode->getRight())
    {
      if (delNode->getVal() < delNode->getParent()->getVal())
      {
        delNode->getParent()->setLeft(delNode->getRight());
      }
      else
      {
        delNode->getParent()->setRight(delNode->getRight());
      }
    }
    else
    {
      if (delNode->getVal() < delNode->getParent()->getVal())
      {
        delNode->getParent()->setLeft(NULL);
      }
      else
      {
        delNode->getParent()->setRight(NULL);
      }
    }
  }
  delete delNode;
}

template <class T>
void Tree<T>::Postorder()
{
  if (this->root == NULL)
    return;
  Postorder(this->root->getLeft());
  Postorder(this->root->getRight());
  cout << this->root->getVal() << " ";
}

template <class T>
void Tree<T>::Inorder()
{
  this->Inorder(this->root);
  cout << endl;
}

template <class T>
void Tree<T>::Inorder(Node<T> *root)
{
  if (root == NULL)
    return;
  Inorder(root->getLeft());
  cout << root->getVal() << " ";
  Inorder(root->getRight());
}

template <class T>
void Tree<T>::Preorder()
{
  if (this->root == NULL)
    return;
  cout << this->root->getVal() << " ";
  Preorder(this->root->getLeft());
  Preorder(this->root->getRight());
}

template <class T>
Tree<T>::~Tree()
{
  while (this->root->getLeft() || this->root->getRight())
  {
    del(this->root->getVal());
  }
  delete this->root;
}

template <class T>
void Tree<T>::print()
{
  string x = collectSTR(this->root);

  cout << "Tree:-\n"
       << x << endl;
}

template <class T>
string Tree<T>::collectSTR(Node<T> *root)
{
  if (root == NULL)
  {
    return "";
  }
  int lenLeft = 0, lenRight = 0, Lcount = 0, Rcount = 0, st_ind = -1, nd_ind = -1;
  string returned = "";

  string left = collectSTR(root->getLeft());
  string right = collectSTR(root->getRight());

  istringstream Sleft(left);
  istringstream Sright(right);

  string Lleft = "", Lright = "";
  getline(Sleft, Lleft);
  getline(Sright, Lright);
  while (Lleft != "" && Lright != "")
  {
    if (Lcount == 0 && Rcount == 0)
    {
      st_ind = Lleft.find_first_not_of("_ ");
      nd_ind = Lright.find_last_not_of("_ ");
    }

    lenLeft = Lleft.length();
    lenRight = Lright.length();

    returned.append(Lleft);
    returned.append(string(to_string(root->getVal()).length(), ' '));
    returned.append(Lright);
    returned.append("\n");

    Lleft = "";
    Lright = "";

    getline(Sleft, Lleft);
    getline(Sright, Lright);

    Lcount++;
    Rcount++;
  }

  while (Lleft != "")
  {
    if (Lcount == 0)
    {

      st_ind = Lleft.find_first_not_of("_ ");
      Lcount++;
    }

    lenLeft = Lleft.length();

    returned.append(Lleft);
    returned.append(string(to_string(root->getVal()).length(), ' '));
    returned.append(string(lenRight, ' '));
    returned.append("\n");

    Lleft = "";

    getline(Sleft, Lleft);
  }

  while (Lright != "")
  {
    if (Rcount == 0)
    {
      nd_ind = Lright.find_last_not_of("_ ");
      Rcount++;
    }

    lenRight = Lright.length();

    returned.append(string(lenLeft, ' '));
    returned.append(string(to_string(root->getVal()).length(), ' '));
    returned.append(string(Lright));
    returned.append("\n");

    Lright = "";

    getline(Sright, Lright);
  }

  if (Lcount == 0 && Rcount == 0)
  {
    returned = string(lenLeft, ' ') + to_string(root->getVal()) + string(lenRight, ' ') + "\n" + returned;
  }
  else if (Lcount != 0 && Rcount == 0)
  {
    returned = string(st_ind + 1, ' ') + string(lenLeft - (st_ind + 1), '_') + to_string(root->getVal()) + string((nd_ind == -1 ? 0 : nd_ind), '_') + string(lenRight - (nd_ind == -1 ? 0 : nd_ind), ' ') + "\n" + string(st_ind, ' ') + "/" + string(lenLeft - (st_ind + 1) + to_string(root->getVal()).length(), ' ') + "\n" + returned;
  }
  else if (Lcount == 0 && Rcount != 0)
  {
    returned = string(0, ' ') + string(0, '_') + to_string(root->getVal()) + string(nd_ind, '_') + string(lenRight - nd_ind, ' ') + "\n" + string(lenLeft, ' ') + string(to_string(root->getVal()).length(), ' ') + string((nd_ind == 0 ? 1 : nd_ind + 1) - 1, ' ') + "\\" + string(lenRight - (nd_ind + 1), ' ') + "\n" + returned;
  }
  else
  {
    returned = string(st_ind + 1, ' ') + string(lenLeft - (st_ind + 1), '_') + to_string(root->getVal()) + string(nd_ind, '_') + string(lenRight - nd_ind, ' ') + "\n" + string(st_ind, ' ') + "/" + string(lenLeft - (st_ind + 1) + to_string(root->getVal()).length(), ' ') + string((nd_ind == 0 ? 1 : nd_ind + 1) - 1, ' ') + "\\" + string(lenRight - (nd_ind + 1), ' ') + "\n" + returned;
  }
  return returned;
}

template <class T>
void Tree<T>::printHeight()
{
  int h = this->height(this->root);
  cout << "height: " << h << endl;
}

template <class T>
int Tree<T>::height(Node<T> *root)
{
  if (root == NULL)
  {
    return 0;
  }

  int Hleft = height(root->getLeft());
  int Hright = height(root->getRight());

  if (Hleft > Hright)
  {
    return Hleft + 1;
  }
  else
  {
    return Hright + 1;
  }
}

template <class T>
void Tree<T>::EditBalanceFactor()
{
  this->BalanceFactor(this->root);
}

template <class T>
int Tree<T>::BalanceFactor(Node<T> *root)
{
  if (root == NULL)
  {
    return 0;
  }
  int BFleft = BalanceFactor(root->getLeft());
  int BFright = BalanceFactor(root->getRight());

  int Hleft = height(root->getLeft());
  int Hright = height(root->getRight());

  root->setFactor(Hright - Hleft);

  return Hright - Hleft;
}

template <class T>
void Tree<T>::rightRotate(Node<T> *root)
{ 
  Node<T> *B = root->getLeft();

  root->setLeft(B->getRight());
  if (B->getRight())
  {
    B->getRight()->setParent(root);
  }

  if (root == this->root)
  {
    B->setParent(NULL);
    this->root = B;
  }
  else if (root->getParent()->getVal() < B->getVal())
  {
    root->getParent()->setRight(B);
    B->setParent(root->getParent());
  }
  else
  {
    root->getParent()->setLeft(B);
    B->setParent(root->getParent());
  }

  B->setRight(root);
  root->setParent(B);
}

template <class T>
void Tree<T>::leftRotate(Node<T> *root)
{
  Node<T> *B = root->getRight();

  root->setRight(B->getLeft());
  if (B->getLeft())
  {
    B->getLeft()->setParent(root);
  }

  if (root == this->root)
  {
    B->setParent(NULL);
    this->root = B;
  }
  else if (root->getParent()->getVal() < B->getVal())
  {
    root->getParent()->setRight(B);
    B->setParent(root->getParent());
  }
  else
  {
    root->getParent()->setLeft(B);
    B->setParent(root->getParent());
  }

  B->setLeft(root);
  root->setParent(B);

}

template <class T>
Node<T> *Tree<T>::getFirstHeigherFactor(Node<T> *root)
{
  if (root->getParent() == NULL)
  {
    return root;
  }
  int factor = root->getFactor();
  if ((factor > 1 || factor < -1) && factor != 0)
  {
    return root;
  }
  return getFirstHeigherFactor(root->getParent());
}