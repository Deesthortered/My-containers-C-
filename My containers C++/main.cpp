#include "vld.h"
#include <iostream>
#include <cstdlib>
#include "BinominalHeap.h"
using namespace std;

int main()
{
	spaceBinominalHeap::BinominalHeap<int> heap;
	for (size_t i = 0; i < 50; i++)
	{
		heap.Insert(i);
		heap.Insert(100 - i);
	}

	for (size_t i = 0; i < 10; i++)
		cout << heap.ExtractMin() << endl;

	system("pause");
	return 0;
}

