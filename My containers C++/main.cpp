#include <vld.h>
#include <iostream>
#include "IdealHashTable.h"
using namespace std;

int main()
{
	vector<pair<size_t, char>> data;
	for (size_t i = 1; i < (size_t)(rand() % 100) + 100; i++)
		data.push_back(pair<size_t, char>(i, (rand() % 128) + 128));

	spaceIdealHashTable::IdealHashTable<char> table(data);

	if (table.Exist(10)) cout << 1 << endl; else cout << 0 << endl;
	cout << table.Find(10) << endl;

	system("pause");
	return 0;
}