#include <iostream>
#include <string>
#include "Node.h"
#include "Tree.h"

using namespace std;

int main()
{
	Tree<int> t = Tree<int>();
	int x = 0;

	while( x != -1){
		cin >> x;
		t.push(x);
		t.print();
	}


	return 0;
}
