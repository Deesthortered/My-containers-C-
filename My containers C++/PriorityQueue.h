#pragma once
#include "Array.h"

namespace spacePriorityQueue
{
	template <class T1, class T2>
	class PriorityQueueMin
	{
		struct Pair
		{
			T1 data;
			T2 key;
			Pair() = default;
			Pair(T1 _data, T2 _key) : data(_data), key(_key) {}
		};
		spaceArray::Array<Pair> arr;

	public:
		PriorityQueueMin() = default;
		PriorityQueueMin(const PriorityQueueMin &obj)
		{
			this->arr = obj.arr;
		}
		~PriorityQueueMin()
		{
			this->arr.~Array();
		}

		PriorityQueueMin& operator=(const PriorityQueueMin &obj)
		{
			if (&obj == this) return *this;
			this->arr = obj.arr;
			return *this;
		}

		bool IsEmpty()
		{
			return (this->arr.IsEmpty() ? true : false);
		}
		void Push(T1 data, T2 key)
		{
			int i = this->arr.Size();
			this->arr.Push_back(Pair(data, key));
			while (i && this->arr[i].key < this->arr[(i - 1) >> 1].key)
			{
				swap(this->arr[(i - 1) >> 1], this->arr[i]);
				i = (i - 1) >> 1;
			}
		}
		void Pop()
		{
			if (this->arr.IsEmpty()) return;
			size_t sz = this->arr.Size() - 1;
			size_t i = 0;

			this->arr[0] = this->arr[sz];
			this->arr.Pop_back();

			while ((i << 1) + 1 < sz)
			{
				if ((i << 1) + 2 < sz)
				{
					if (this->arr[(i << 1) + 1].key < this->arr[(i << 1) + 2].key)
					{
						if (this->arr[(i << 1) + 1].key < this->arr[i].key)
						{
							swap(this->arr[(i << 1) + 1], this->arr[i]);
							i = (i << 1) + 1;
						}
						else break;
					}
					else
					{
						if (this->arr[(i << 1) + 2].key < this->arr[i].key)
						{
							swap(this->arr[(i << 1) + 2], this->arr[i]);
							i = (i << 1) + 2;
						}
						else break;
					}
				}
				else if (this->arr[(i << 1) + 1].key < this->arr[i].key)
				{
					swap(this->arr[(i << 1) + 1], this->arr[i]);
					i = (i << 1) + 1;
				}
				else break;
			}
		}
		T1	 ExtractMin()
		{
			if (this->arr.IsEmpty()) throw "Empty queue";
			return this->arr[0].data;
		}
		void ShrinkToFit()
		{
			this->arr.ShrinkToFit();
		}
	};

	template <class T1, class T2>
	class PriorityQueueMax
	{
		struct Pair
		{
			T1 data;
			T2 key;
			Pair() = default;
			Pair(T1 _data, T2 _key) : data(_data), key(_key) {}
		};
		spaceArray::Array<Pair> arr;

	public:
		PriorityQueueMax() = default;
		PriorityQueueMax(const PriorityQueueMax &obj)
		{
			this->arr = obj.arr;
		}
		~PriorityQueueMax()
		{
			this->arr.~Array();
		}

		PriorityQueueMax& operator=(const PriorityQueueMax &obj)
		{
			if (&obj == this) return *this;
			this->arr = obj.arr;
			return *this;
		}

		bool IsEmpty()
		{
			return (this->arr.IsEmpty() ? true : false);
		}
		void Push(T1 data, T2 key)
		{
			int i = this->arr.Size();
			this->arr.Push_back(Pair(data, key));
			while (i && this->arr[i].key > this->arr[(i - 1) >> 1].key)
			{
				swap(this->arr[(i - 1) >> 1], this->arr[i]);
				i = (i - 1) >> 1;
			}
		}
		void Pop()
		{
			if (this->arr.IsEmpty()) return;
			size_t sz = this->arr.Size() - 1;
			size_t i = 0;

			this->arr[0] = this->arr[sz];
			this->arr.Pop_back();

			while ((i << 1) + 1 < sz)
			{
				if ((i << 1) + 2 < sz)
				{
					if (this->arr[(i << 1) + 1].key > this->arr[(i << 1) + 2].key)
					{
						if (this->arr[(i << 1) + 1].key > this->arr[i].key)
						{
							swap(this->arr[(i << 1) + 1], this->arr[i]);
							i = (i << 1) + 1;
						}
						else break;
					}
					else
					{
						if (this->arr[(i << 1) + 2].key > this->arr[i].key)
						{
							swap(this->arr[(i << 1) + 2], this->arr[i]);
							i = (i << 1) + 2;
						}
						else break;
					}
				}
				else if (this->arr[(i << 1) + 1].key > this->arr[i].key)
				{
					swap(this->arr[(i << 1) + 1], this->arr[i]);
					i = (i << 1) + 1;
				}
				else break;
			}
		}
		T1	 ExtractMax()
		{
			if (this->arr.IsEmpty()) throw "Empty queue";
			return this->arr[0].data;
		}
		void ShrinkToFit()
		{
			this->arr.ShrinkToFit();
		}
	};
}