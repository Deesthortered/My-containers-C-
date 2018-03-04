#include "vld.h"
#include <iostream>
#include "BinominalHeap.h"
using namespace std;

int main()
{
	spaceBinominalHeap::BinominalHeap<int> heap;
	for (size_t i = 0; i < 10; i++)
		heap.Insert(i);

	heap.DecreaseKey(6, -10);
	heap.Delete(5);


	while (!heap.IsEmpty()) 
		cout << heap.ExtractMin() << endl;

	system("pause");
	return 0;
}

