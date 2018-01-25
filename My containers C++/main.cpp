#include <vld.h>
#include <iostream>
#include "Red_Black_Tree.h"
using namespace std;

int main()
{
	spaceRed_Black_Tree::Red_Black_Tree<int> tree;
	for (size_t i = 5; i > 0; i--)
		tree.Insert(i);
	for (size_t i = 5; i < 10; i++)
		tree.Insert(i);
	system("pause");
	return 0;
}