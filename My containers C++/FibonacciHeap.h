#pragma once

namespace spaceFibonacciHeap
{
	template<class T>
	class FibonacciHeap
	{
		struct HeapNode
		{
			T key;
			HeapNode* parent;
			HeapNode* child;
			HeapNode* left;
			HeapNode* right;
			size_t degree;
			bool mark;
			HeapNode(T _key) : key(_key), parent(nullptr), child(nullptr), left(this), right(this), degree(0), mark(false) {}
			HeapNode(T _key, HeapNode* _left, HeapNode* _right) : key(_key), parent(nullptr), child(nullptr), left(_left), right(_right), degree(0), mark(false) {}
		};
		HeapNode* min_element;

	public:
		FibonacciHeap()
		{
			this->min_element = nullptr;
		}
		~FibonacciHeap()
		{
			clear(this->min_element);
			this->min_element = nullptr;
		}

		void Insert(T key)
		{
			if (!this->min_element)
			{
				this->min_element = new HeapNode(key);
				return;
			}
			HeapNode *p = new HeapNode(key, this->min_element->left, this->min_element);
			p->left->right = p;
			p->right->left = p;
			if (p->key < this->min_element->key) this->min_element = p;
		}


	private:

		static void clear(HeapNode* node)
		{
			if (!node) return;
			HeapNode* p = node->right;
			while (p != node)
			{
				clear(p->child);
				HeapNode* k = p;
				p = p->right;
				delete k;
			}
			clear(node->child);
			delete node;
		}
	};
}