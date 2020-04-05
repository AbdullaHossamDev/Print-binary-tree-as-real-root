#include <iostream>
#include <string>
#include "Node.h"
#include "Tree.h"

using namespace std;

int main()
{
	Tree<int> t = Tree<int>();
	int x = 0;
	cout << "################### AVL Tree ###################\n\n\n";
	cout << "When you want to exit just enter -1\n";
	cout << "Enter Tree Numbers\n\n";
	while( x != -1){
		cin >> x;
		t.push(x);
		t.print();
	}
	cout << "Good bye :)\n";

	return 0;
}
