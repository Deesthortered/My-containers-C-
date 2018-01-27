#include <vld.h>
#include <iostream>
#include "Red_Black_Tree.h"
using namespace std;

int main()
{
	spaceRed_Black_Tree::Red_Black_Tree<int> tree;

	tree.Insert(1);
	tree.Insert(2);
	tree.Insert(3);

	spaceRed_Black_Tree::Red_Black_Tree<int> tree1(tree);

	system("pause");
	return 0;
}