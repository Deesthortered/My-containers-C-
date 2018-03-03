#pragma once
#include <vector>
#include <ctime>
using namespace std;

namespace spaceIdealHashTable
{
	template<class TData>
	class IdealHashTable
	{
		struct HashTableNode
		{
			size_t key;
			TData data;
			HashTableNode() : key(0), data(TData()) {};
			HashTableNode(size_t _key, TData _data) : key(_key), data(_data) {};
		};

		vector<vector<HashTableNode*>> table;
		size_t mA, mB, mP, mM;
		vector<size_t> A, B, P, M;
	public:
		IdealHashTable() = default;
		~IdealHashTable()
		{
			clear();
			table.clear();
			A.clear(); B.clear(); P.clear(); M.clear();
		}
		IdealHashTable(vector<pair<size_t,TData>> inputs)
		{
			srand((size_t)time(NULL));
			this->mM = inputs.size();

			this->mP = 0;
			for (register size_t i = 0; i < this->mM; i++)
				if (inputs[i].first > this->mP) this->mP = inputs[i].first;
			this->mP++;
			while (!IsPrime(this->mP)) this->mP++;

			if (this->mP <= 2) this->mA = 0;
			else while (!this->mA) this->mA = (rand() % this->mP);

			this->mB = rand() % this->mP;
			this->table.assign(this->mM, {});

			this->A.resize(this->mM);
			this->B.resize(this->mM);
			this->P.resize(this->mM);
			this->M.resize(this->mM);

			vector<size_t> keys_in_bucket(this->mM), max_key(this->mM);
			for (register size_t i = 0; i < this->mM; i++)
			{
				size_t h = Hash(inputs[i].first, mA, mB, mM, mP);
				keys_in_bucket[h]++;
				if (inputs[i].first > max_key[h])
					max_key[h] = inputs[i].first;
			}

			bool all_ok = false;
			while (!all_ok)
			{
				all_ok = true;
				for (register size_t i = 0; i < this->mM; i++)
				{
					this->M[i] = keys_in_bucket[i] * keys_in_bucket[i];
					if (M[i] <= 1)
					{
						this->P[i] = 2;
						this->A[i] = 0;
						this->B[i] = 0;
					}
					else
					{
						this->P[i] = max_key[i] + 1;
						while (!IsPrime(this->P[i])) this->P[i]++;
						this->A[i] = this->mA; this->B[i] = this->mB;
						while (this->A[i] == this->mA || !this->A[i]) this->A[i] = rand() % this->P[i];
						while (this->B[i] == this->mB) this->B[i] = rand() % this->P[i];
					}
					this->table[i].assign(this->M[i], nullptr);
				}
				for (register size_t i = 0; i < this->mM; i++)
				{
					size_t first = Hash(inputs[i].first, mA, mB, mM, mP);
					size_t second = Hash(inputs[i].first, A[first], B[first], M[first], P[first]);
					if (table[first][second])
					{
						clear();
						all_ok = false;
						break;
					}
					table[first][second] = new HashTableNode(inputs[i].first, inputs[i].second);
				}
			}
		}

		bool Exist(size_t key)
		{
			size_t h = Hash(key, mA, mB, mM, mP);
			return (this->table[h][Hash(key, A[h], B[h], M[h], P[h])] == nullptr ? false : true);
		}
		TData Find(size_t key)
		{
			size_t h = Hash(key, mA, mB, mM, mP);
			return this->table[h][Hash(key, A[h], B[h], M[h], P[h])]->data;
		}

	private:
		static bool IsPrime(size_t a)
		{
			if (a < 2) return false;
			for (register size_t i = 2; i*i <= a; i++)
				if (a % i == 0) return false;
			return true;
		}
		static size_t Hash(size_t key, size_t a, size_t b, size_t m, size_t p)
		{
			return (((key * a) + b) % p) % m;
		}
		void clear()
		{
			for (register size_t i = 0; i < table.size(); i++)
				for (register size_t j = 0; j < table[i].size(); j++)
					if (table[i][j]) delete table[i][j];
		}
	};
}