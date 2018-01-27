#include <vld.h>
#include <iostream>
#include "Red_Black_Tree.h"
using namespace std;

int main()
{
	spaceRed_Black_Tree::Red_Black_Tree<int> tree;
	tree.Insert(20);
	tree.Insert(40);
	tree.Insert(60);
	tree.Insert(50);
	tree.Insert(30);
	tree.Insert(25);
	tree.Insert(27);
	tree.Insert(10);
	tree.Insert(15);
	tree.Insert(28);
	tree.Insert(23);
	tree.Insert(35);

	 
	system("pause");
	return 0;
}