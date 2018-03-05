#include "vld.h"
#include <iostream>
#include "FibonacciHeap.h"
using namespace std;

int main()
{
	spaceFibonacciHeap::FibonacciHeap<int> heap;

	heap.Insert(5);
	heap.Insert(7);
	heap.Insert(3);
	heap.Insert(8);
	heap.Insert(9);

	system("pause");
	return 0;
}

