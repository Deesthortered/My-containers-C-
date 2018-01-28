#include <vld.h>
#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

int main()
{
	spaceBinarySearchTree::BinarySearchTree<int> bst;

	bst.Insert(5);
	bst.Insert(3);
	bst.Insert(9);
	//bst.Insert(12);
	bst.Insert(4);
	bst.Insert(7);
	bst.Insert(6);
	bst.Insert(8);

	bst.Delete(9);

	system("pause");
	return 0;
}