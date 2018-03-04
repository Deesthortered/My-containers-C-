#pragma once

namespace spaceBinominalHeap
{
	template<class T>
	class BinominalHeap
	{
		struct HeapNode
		{
			T key;
			HeapNode *parent;
			HeapNode *child;
			HeapNode *sibling;
			size_t degree;
			HeapNode(T _key) : key(_key), parent(nullptr), child(nullptr), sibling(nullptr), degree(0) {}
		};
		HeapNode *root;
		HeapNode *min_elem;

	public:
		BinominalHeap()
		{
			this->root = nullptr;
			this->min_elem = nullptr;
		}
		~BinominalHeap()
		{
			clear(this->root);
			this->root = nullptr;
			this->min_elem = nullptr;
		}

		bool IsEmpty()
		{
			return (this->root ? false : true);
		}
		void Insert(T key)
		{
			HeapNode *temp = new HeapNode(key);
			this->root = merge(this->root, temp);
		}
		T ExtractMin()
		{
			getMinimum();
			if (!this->min_elem) return T();
			T res = this->min_elem->key;

			HeapNode *p = this->root;
			if (p == this->min_elem)
			{
				this->root = this->root->sibling;
				p = p->child;
				delete this->min_elem;
			}
			else
			{
				while (p->sibling != this->min_elem) p = p->sibling;
				p->sibling = p->sibling->sibling;
				p = this->min_elem->child;
				delete this->min_elem;
			}
			HeapNode *tmp = p;
			while (tmp) { tmp->parent = nullptr; tmp = tmp->sibling; }

			inverseList(p, nullptr, p);
			this->root = merge(this->root, p);
			return res;
		}
		void DecreaseKey(T key, T new_val)
		{
			if (key <= new_val) return;
			HeapNode* x = nullptr;
			search(key, this->root, x);
			if (!x) return;
			x->key = new_val;
			HeapNode* p = x->parent;
			while (p && x->key < p->key)
			{
				swap(x->key, p->key);
				x = p; p = p->parent;
			}
		}
		void Delete(T key)
		{
			getMinimum();
			DecreaseKey(key, this->min_elem->key - 1);
			getMinimum();
			ExtractMin();
		}

	private:
		inline void getMinimum()
		{
			if (!this->root) this->min_elem = nullptr;
			this->min_elem = this->root;
			HeapNode *p = this->root;
			while (p)
			{
				if (p->key < this->min_elem->key) this->min_elem = p;
				p = p->sibling;
			}
		}
		static void search(T &val, HeapNode* node, HeapNode *&res)
		{
			if (!node) return;
			if (val == node->key) res = node;
			else
			{
				search(val, node->sibling, res);
				search(val, node->child, res);
			}
		}
		static void inverseList(HeapNode *&head, HeapNode *prev, HeapNode *cur)
		{
			if (!cur) return;
			if (cur->sibling) inverseList(head, cur, cur->sibling);
			else head = cur;
			cur->sibling = prev;
		}
		static HeapNode* merge(HeapNode *H1, HeapNode *H2)
		{
			if (!H1) return H2;
			if (!H2) return H1;
			HeapNode *res = nullptr;
			HeapNode *curH = nullptr;
			HeapNode *curH1 = H1;
			HeapNode *curH2 = H2;

			if (curH1->degree <= curH2->degree) curH = curH1, curH1 = curH1->sibling;
			else curH = curH2, curH2 = curH2->sibling;

			res = curH;

			while (curH1 && curH2)
			{
				if (curH1->degree <= curH2->degree)
				{
					curH->sibling = curH1;
					curH = curH1;
					curH1 = curH1->sibling;
				}
				else
				{
					curH->sibling = curH2;
					curH = curH2;
					curH2 = curH2->sibling;
				}
			}

			if (curH2) curH->sibling = curH2;
			else curH->sibling = curH1;

			curH = res;
			curH1 = curH;
			while (curH->sibling)
			{
				if (curH->degree == curH->sibling->degree)
				{
					HeapNode *t1 = curH, *t2 = curH->sibling;
					if (curH->key >= curH->sibling->key)
					{
						curH1->sibling = t2;
						t1->parent = t2;
						t1->sibling = t2->child;
						t2->child = t1;
						t2->degree++;
						if (curH == res) res = t2, curH1 = t2;
						curH = t2;
					}
					else
					{
						t2->parent = t1;
						t1->sibling = t2->sibling;
						t2->sibling = t1->child;
						t1->child = t2;
						t1->degree++;
					}
					continue;
				}
				curH1 = curH;
				curH = curH->sibling;
			}
			return res;
		}
		static void clear(HeapNode *node)
		{
			if (!node) return;
			clear(node->child);
			clear(node->sibling);
			delete node;
		}
	};
}