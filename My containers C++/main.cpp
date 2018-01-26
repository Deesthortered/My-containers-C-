#include <vld.h>
#include <iostream>
#include "Red_Black_Tree.h"
using namespace std;

int main()
{
	spaceRed_Black_Tree::Red_Black_Tree<int> tree;
	for (size_t i = 2; i < 30; i+=2)
		tree.Insert(i);
	tree.Insert(30);
	tree.Insert(29);

	tree.Delete(4);

	system("pause");
	return 0;
}