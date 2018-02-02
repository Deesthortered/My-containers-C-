#include <vld.h>
#include <iostream>
#include <ctime>
#include "HashTable.h"
using namespace std;

int main()
{
	srand((size_t)time(NULL));
	spaceHashTable::HashTableChain<double, int> table(100);
	
	//for (size_t i = 0; i < 30; i++)
		//table.Insert(rand() % 100, 0);

	table.Insert(0.1, 0);
	table.Insert(2.11, 0);
	table.Insert(5.31, 0);
	table.Insert(2.81, 0);
	table.Insert(6.21, 0);
	table.Insert(2.61, 0);
	table.Insert(0.001, 0);

	system("pause");
	return 0;
}