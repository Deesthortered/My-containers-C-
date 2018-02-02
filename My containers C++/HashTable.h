#pragma once
#include "Array.h"

namespace spaceHashTable
{
	// ¬ј∆Ќќ!!!!  ласс расчитан только на Ќ≈” ј«ј“≈Ћ» и на те типы данных, которые не содержат указателей (потому строки отпадают).
	template<class TKey, class TData>
	class HashTableChain
	{
		struct HashTableNode
		{
			TKey key;
			TData data;
			HashTableNode *next;
			HashTableNode(TKey _key, TData _data, HashTableNode *_next) : key(_key), data(_data), next(_next) {}
		};

		spaceArray::Array<HashTableNode*> table;
		size_t tableSize;
		size_t primeHash;
		size_t byte_sz;

	public:
		HashTableChain(size_t tableSz)
		{
			this->tableSize = tableSz;
			this->table.Resize(tableSz);
			for (register size_t i = 0; i < tableSz; i++)
				this->table[i] = nullptr; 
			this->byte_sz = sizeof(TKey);
			this->primeHash = 1;
			while ((this->tableSize % this->primeHash == 0) || (this->primeHash % this->tableSize == 0)) this->primeHash++;
		}
		~HashTableChain()
		{
			this->table.~Array();
		}

		bool Insert(TKey key, TData data)
		{
			cout << key << "\t" << Hash(key) << endl;
			return false;
		}
		bool Delete(TKey key)
		{
			return false;
		}
		TData Find(TKey key)
		{
			return TData();
		}
	private:
		size_t Hash(TKey key)
		{
			size_t hash = 0;
			char *c = (char *)&key;
			for (register size_t i = 0; i < this->byte_sz; i++)
			{
				hash = ((size_t)(hash*this->primeHash + (size_t)(c[i]) )) % this->tableSize;
			}
			return hash;
		}
	};
}