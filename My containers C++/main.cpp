#include <vld.h>
#include <iostream>
#include <ctime>
#include "HashTable.h"
using namespace std;

int main()
{
	srand((size_t)time(NULL));
	spaceHashTable::HashTableChain<int, int> table(100);
	


	system("pause");
	return 0;
}