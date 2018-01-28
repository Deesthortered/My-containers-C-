#pragma once
#include "Array.h"

namespace spaceHeap
{
	template<class T>
	class HeapMin
	{
		spaceArray::Array<T> arr;
	public:
		HeapMin() = default;
		HeapMin(const HeapMin &obj)
		{
			this->arr = obj.arr;
		}
		~HeapMin()
		{
			this->arr.~Array();
		}

		HeapMin& operator=(const HeapMin &obj)
		{
			this->arr = obj.arr;
			return *this;
		}

		bool IsEmpty()
		{
			return (this->arr.IsEmpty() ? true : false);
		}
		void Push(T data)
		{
			int i = this->arr.Size();
			this->arr.Push_back(data);
			while (i && this->arr[i] < this->arr[(i - 1) >> 1])
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
					if (this->arr[(i << 1) + 1] < this->arr[(i << 1) + 2])
					{
						if (this->arr[(i << 1) + 1] < this->arr[i])
						{
							swap(this->arr[(i << 1) + 1], this->arr[i]);
							i = (i << 1) + 1;
						}
						else break;
					}
					else
					{
						if (this->arr[(i << 1) + 2] < this->arr[i])
						{
							swap(this->arr[(i << 1) + 2], this->arr[i]);
							i = (i << 1) + 2;
						}
						else break;
					}
				}
				else if (this->arr[(i << 1) + 1] < this->arr[i])
				{
					swap(this->arr[(i << 1) + 1], this->arr[i]);
					i = (i << 1) + 1;
				}
				else break;
			}
		}
		T	 ExtractMin()
		{
			if (this->arr.IsEmpty()) throw "Empty queue";
			return this->arr[0];
		}
		void ShrinkToFit()
		{
			this->arr.ShrinkToFit();
		}
	};

	template<class T>
	class HeapMax
	{
	public:
		spaceArray::Array<T> arr;
	public:
		HeapMax() = default;
		HeapMax(const HeapMax &obj)
		{
			this->arr = obj.arr;
		}
		~HeapMax()
		{
			this->arr.~Array();
		}

		HeapMax& operator=(const HeapMax &obj)
		{
			this->arr = obj.arr;
			return *this;
		}

		bool IsEmpty()
		{
			return (this->arr.IsEmpty() ? true : false);
		}
		void Push(T data)
		{
			int i = this->arr.Size();
			this->arr.Push_back(data);
			while (i && this->arr[i] > this->arr[(i - 1) >> 1])
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
					if (this->arr[(i << 1) + 1] > this->arr[(i << 1) + 2])
					{
						if (this->arr[(i << 1) + 1] > this->arr[i])
						{
							swap(this->arr[(i << 1) + 1], this->arr[i]);
							i = (i << 1) + 1;
						}
						else break;
					}
					else
					{
						if (this->arr[(i << 1) + 2] > this->arr[i])
						{
							swap(this->arr[(i << 1) + 2], this->arr[i]);
							i = (i << 1) + 2;
						}
						else break;
					}
				}
				else if (this->arr[(i << 1) + 1] > this->arr[i])
				{
					swap(this->arr[(i << 1) + 1], this->arr[i]);
					i = (i << 1) + 1;
				}
				else break;
			}
		}
		T	 ExtractMax()
		{
			if (this->arr.IsEmpty()) throw "Empty queue";
			return this->arr[0];
		}
		void ShrinkToFit()
		{
			this->arr.ShrinkToFit();
		}
	};
}