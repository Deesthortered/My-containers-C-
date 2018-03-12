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
			HeapNode *prevMin = this->min_element;
			unionLists(this->min_element, this->min_element->child);

			//HeapNode *p = this->min_element;
			//do { p->parent = nullptr; p = p->right; } while (p != this->min_element);

			this->min_element->left->right = this->min_element->right;
			this->min_element->right->left = this->min_element->left;

			T res = prevMin->key;
			if (prevMin->right == prevMin)
			{
				delete prevMin;
				this->min_element = nullptr;
				this->size--;
				return res;
			}

			this->min_element = this->min_element->right;
			delete prevMin;
			this->size--;
			consolidate();
			return res;
		}
		bool DecreaseKey(T key, T new_val)
		{
			if (key < new_val) return false;
			HeapNode *p = nullptr;
			search(this->min_element, key, p);
			if (!p) return false;
			p->key = new_val;
			HeapNode *parent = p->parent;
			if (parent && p->key < parent->key) 
			{
				cut(p, parent);
				cascadingCut(parent);
			}
			if (p->key < this->min_element->key) this->min_element = p;
			return true;
		}
		void Delete(T key)
		{
			if (DecreaseKey(key, this->min_element->key - 1)) ExtractMin();
		}
		void Merge(FibonacciHeap &that)
		{
			if (!that.size) return;
			if (!this->size)
			{
				this->min_element = that.min_element;
				this->size = that.size;
			}
			else
			{
				unionLists(this->min_element, that.min_element);
				this->size += that.size;
				if (that.min_element->key < this->min_element->key)
					this->min_element = that.min_element;
			}
			that.min_element = nullptr;
			that.size = 0;
		}

	private:
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
		static void search(HeapNode *node, T &key, HeapNode *&res)
		{
			if (!node || res) return;
			HeapNode *p = node->right;
			bool ready = false;
			while (true)
			{
				if (p->key == key)
				{
					res = p;
					return;
				}
				if (p->key < key) search(p->child, key, res);
				p = p->right;
				if (p == node) ready = true;
				else if (ready) break;
			}
		}
		static void linkHeap(HeapNode *first, HeapNode *second)
		{
			if (!second || !first) return;
			if (!first->child) first->child = second;
			else unionLists(second, first->child);
			second->parent = first;
			first->degree++;
			second->mark = false;
		}
		static void unionLists(HeapNode *first, HeapNode *second)
		{
			if (!first || !second) return;
			first->left->right = second->right;
			second->right->left = first->left;
			second->right = first;
			first->left = second;
		}
		void consolidate()
		{
			if (this->size == 1) return;
			HeapNode **cons_arr = new HeapNode*[this->size];
			for (size_t i = 0; i < this->size; i++) cons_arr[i] = nullptr;

			HeapNode *current = this->min_element, *next = this->min_element->right;
			this->min_element = nullptr;
			bool ready = false;

			while (true)
			{
				size_t cur_degree = current->degree;
				current->right->left = current->left;
				current->left->right = current->right;
				current->left = current->right = current;
				while (cons_arr[cur_degree])
				{
					HeapNode *tmp = cons_arr[cur_degree];
					if (current->key > tmp->key) { linkHeap(tmp, current); current = tmp; }
					else linkHeap(current, tmp);
					cons_arr[cur_degree] = nullptr;
					cur_degree++;
				}
				cons_arr[cur_degree] = current;

				if (ready) break;
				if (next == next->right) ready = true;
				current = next;
				next = next->right;
			}
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
		void cut(HeapNode *first, HeapNode *second)
		{
			first->left->right = first->right;
			first->right->left = first->left;
			second->degree--;
			if (second->child == first)
			{
				if (first->right == first) second->child = nullptr;
				else second->child = first->right;
			}
			first->parent = nullptr;
			first->left = first->right = first;
			unionLists(this->min_element, first);
		}
		void cascadingCut(HeapNode *node)
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
	};
}