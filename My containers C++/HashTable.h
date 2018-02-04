#pragma once
#include "Array.h"

namespace spaceHashTable
{
	// ВАЖНО!!!! Класс расчитан только на НЕУКАЗАТЕЛИ (потому строки отпадают).
	template<class TKey, class TData>
	class HashTableChain
	{
		struct HashTableNode
		{
			TKey key;
			TData data;
			HashTableNode *next;
			HashTableNode(TKey _key, TData _data) : key(_key), data(_data), next(nullptr) {}
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
			this->primeHash = rand() % tableSz;
			while (NOD(this->primeHash, this->tableSize) != 1) this->primeHash++;
		}
		~HashTableChain()
		{
			for (size_t i = 0; i < this->table.Size(); i++) clear(this->table[i]);
			this->table.~Array();
		}

		bool Insert(TKey key, TData data)
		{
			size_t i = Hash(key);
			HashTableNode *p = this->table[i];
			if (!p)
			{
				this->table[i] = new HashTableNode(key, data);
				return false;
			}
			while (p->next && p->key != key) p = p->next;
			if (p->key != key)
			{
				p->next = new HashTableNode(key, data);
				return false;
			}
			return true;
		}
		bool Delete(TKey key)
		{
			size_t i = Hash(key);
			HashTableNode *p = this->table[i];
			if (!p) return false;
			while (p->next && p->next->key != key) p = p->next;
			if (p->next)
			{
				HashTableNode *k = p->next;
				p->next = p->next->next;
				delete k;
				return true;
			}
			return false;
		}
		bool Exist(TKey key)
		{
			size_t i = Hash(key);
			HashTableNode *p = this->table[i];
			while (p && p->key != key) p = p->next;
			if (p) return true;
			return false;
		}
		TData Find(TKey key)
		{
			size_t i = Hash(key);
			HashTableNode *p = this->table[i];
			while (p && p->key != key) p = p->next;
			if (p) return p->data;
			return TData();
		}

	private:
		size_t Hash(TKey key)
		{
			size_t hash = 0;
			char *c = (char *)&key;
			for (register size_t i = 0; i < this->byte_sz; i++)
				hash = ((size_t)(hash*this->primeHash + (size_t)(c[i]) )) % this->tableSize;
			return hash;
		}
		void clear(HashTableNode *&node)
		{
			HashTableNode *p = node;
			while (p)
			{
				HashTableNode *k = p;
				p = p->next;
				delete k;
			}
		}
		size_t NOD(size_t a, size_t b)
		{
			while (a && b)
			{
				if (a > b) a %= b;
				else b %= a;
			}
			return a + b;
		}
	};
}