#include "vld.h"
#include <iostream>
#include "FibonacciHeap.h"
using namespace std;

int main()
{
	spaceFibonacciHeap::FibonacciHeap<int> h1, h2;

	//inserting - ok
	h1.Insert(5);
	h1.Insert(7);
	h1.Insert(3);
	h1.Insert(8);
	h2.Insert(9);
	h2.Insert(1);
	h2.Insert(2);
	h2.Insert(4);

	h1.Merge(h2);
	while (!h1.IsEmpty()) // empty - ok
		cout << h1.ExtractMin() << endl; // extractMin - 

	system("pause");
	return 0;
}

