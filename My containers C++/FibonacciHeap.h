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
		HeapNode *min_element;
		size_t size;

	public:
		FibonacciHeap()
		{
			this->min_element = nullptr;
			this->size = 0;
		}
		~FibonacciHeap()
		{
			clear(this->min_element);
			this->min_element = nullptr;
			this->size = 0;
		}

		bool IsEmpty()
		{
			return (this->min_element ? false : true);
		}
		void Insert(T key)
		{
			if (!this->min_element)
			{
				this->min_element = new HeapNode(key);
				this->size++;
				return;
			}
			HeapNode *p = new HeapNode(key, this->min_element->left, this->min_element);
			p->left->right = p;
			p->right->left = p;
			if (p->key < this->min_element->key) this->min_element = p;
			this->size++;
		}
		T ExtractMin() 
		{
			if (!this->min_element) return T();
			HeapNode *res = this->min_element;
			if (this->min_element->child) 
			{
				HeapNode *current = this->min_element->child;
				do
				{
					HeapNode *R = current->right;
					current->parent = nullptr;
					current->left = current->right = current;
					unionLists(this->min_element, current);
					current = R;
				} while (current != this->min_element->child);
				this->min_element->child = nullptr;
			}
			HeapNode *L = this->min_element->left, *R = this->min_element->right;
			L->right = R;
			R->left = L;
			this->size--;
			if (res->right == res) 
			{
				this->min_element = nullptr;
				return res->key;
			}
			this->min_element = this->min_element->right;
			consolidate();
			return res->key;
		}
		void DecreaseKey(T key, T new_val)
		{
			if (key < new_val) return;
			HeapNode *p = nullptr;
			search(this->min_element, key, p);
			if (!p) return;

			p->key = new_val;
			HeapNode *parent = p->parent;
			if (parent && p->key < parent->key) 
			{
				cut(p, parent);
				cascadingCut(parent);
			}
			if (p->key < this->min_element->key) this->min_element = p;
		}
		void Delete(T key)
		{
			HeapNode *p = nullptr;
			search(this->min_element, key, p);
			if (!p || p->key < new_val) return;
			DecreaseKey(key, this->min_element->key - 1);
			ExtractMin();
		}

	private:
		static void search(HeapNode *node, T &key, HeapNode *&res)
		{
			if (!node || res) return;
			HeapNode *p = node->right;
			while (p != node)
			{
				if (p->key == key)
				{
					res = p;
					return;
				}
				if (p->key < key) search(p->child, key, res);
				p = p->right;
			}

			if (p->key == key)
			{
				res = p;
				return;
			}
			if (p->key < key) search(p->child, key, res);
			p = p->right;
		}
		static void clear(HeapNode *node)
		{
			if (!node) return;
			HeapNode *p = node->right;
			while (p != node)
			{
				clear(p->child);
				HeapNode *k = p;
				p = p->right;
				delete k;
			}
			clear(node->child);
			delete node;
		}

		void consolidate() 
		{
			HeapNode **cons_arr = new HeapNode*[this->size];
			for (size_t i = 0; i < this->size; i++) cons_arr[i] = nullptr;
			HeapNode *current = this->min_element->right;
			bool ready = false;
			while (true)
			{
				HeapNode *X = current, *R = current->right, *L = current->left;
				size_t cur_degree = X->degree;
				R->left = L;
				L->right = R;
				X->left = X->right = X;
				while (cons_arr[cur_degree]) 
				{
					HeapNode *tmp = cons_arr[cur_degree];
					if (X->key > tmp->key) swap(X, tmp);
					linkHeap(X, tmp);
					cons_arr[cur_degree] = nullptr;
					cur_degree++;
				}
				cons_arr[cur_degree] = X;
				current = R;
				if (current == this->min_element) ready = true;
				else if (ready) break;
			}
			this->min_element = nullptr;
			for (size_t i = 0; i < this->size; i++)
			{
				if (cons_arr[i]) 
				{
					if (this->min_element)
					{
						unionLists(this->min_element, cons_arr[i]);
						if (cons_arr[i]->key < this->min_element->key) this->min_element = cons_arr[i];
					}
					else this->min_element = cons_arr[i];
				}
			}
			delete[] cons_arr;
		}
		void merge(FibonacciHeap *that)
		{
			if (!that->size) return;
			if (!this->size)
			{
				this->min_element = that->min_element;
				this->size = that->size;
			}
			else
			{
				unionLists(this->min_element, that->min_element);
				this->size += that->size;
				if (that->min_element->key < this->min_element->key) 
					this->min_element = that->min_element;
			}
		}
		static void cascadingCut(HeapNode *node)
		{
			HeapNode *current = node->parent;
			if (current) 
			{
				if (node->mark == false) node->mark = true;
				else 
				{
					cut(node, current);
					cascadingCut(current);
				}
			}
		}
		static void cut(HeapNode *X, HeapNode *Y)
		{
			HeapNode *L = X->left, *R = X->right;
			L->right = R;
			R->left = L;
			Y->degree--;
			if (Y->child == X)
			{
				if (X->right == X) Y->child = nullptr;
				else Y->child = X->right;
			}
			X->parent = nullptr;
			X->left = X->right = X;
			unionLists(this->min_element, X);
		}
		static void linkHeap(HeapNode *first, HeapNode *second)
		{
			if (!second || !first) return;
			HeapNode *L = second->left, *R = second->right;
			L->right = R;
			R->left = L;
			second->left = second->right = second;
			if (!first->child) first->child = second;
			else unionLists(first->child, second);
			second->parent = first;
			first->degree++;
			second->mark = false;
		}
		static void unionLists(HeapNode *first, HeapNode *second)
		{
			HeapNode *l = first->left, *r = second->right;
			second->right = first;
			first->left = second;
			l->right = r;
			r->left = l;
		}
	};
}