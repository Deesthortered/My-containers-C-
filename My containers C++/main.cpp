#include <vld.h>
#include <iostream>
#include "Red_Black_Tree.h"
using namespace std;

int main()
{
	spaceRed_Black_Tree::Red_Black_Tree<int> tree;
	for (size_t i = 0; i < 15; i++)
		tree.Insert(i);
	tree.Delete(3);
	system("pause");
	return 0;
}