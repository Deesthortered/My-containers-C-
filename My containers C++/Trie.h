#pragma once
#include "Array.h"

namespace spaceTrie
{
	template<class T>
	class Trie
	{
		struct TrieNode
		{
			char key_val;
			spaceArray::Array<TrieNode*> children;

			bool isTerminal;
			T data_value;

			TrieNode() : key_val(char()), isTerminal(false), data_value(T()) {}
			TrieNode(char _val): key_val(_val), isTerminal(false), data_value(T()) {}
		};
		TrieNode *root;

	public:
		Trie()
		{
			root = new TrieNode();
		}
		Trie(const Trie &obj)
		{
			copy(this->root, obj.root);
			return *this;
		}
		~Trie()
		{
			clear(this->root);
			this->root = nullptr;
		}

		bool Insert(const char* key, size_t str_size, T value)
		{
			TrieNode *p = this->root;
			size_t char_cnt = 0;
			size_t iter = 0;
			bool pref = true;
			while (pref && iter < str_size)
			{
				pref = false;
				for (register size_t i = 0; i < p->children.Size(); i++)
				{
					if (p->children[i]->key_val == key[iter])
					{
						p = p->children[i];
						pref = true;
						iter++;
						break;
					}
				}
			}
			if (iter == str_size)
			{
				p->data_value = value;
				if (p->isTerminal) return false;
				else { p->isTerminal = true; return true; }
			}
			for (; iter < str_size; iter++)
			{
				TrieNode *k = new TrieNode(key[iter]);
				p->children.Push_back(k);
				p = k;
			}
			p->data_value = value;
			p->isTerminal = true;
			return true;
		}
		bool Delete(const char* key, size_t str_size)
		{
			TrieNode *p = this->root, *term1 = this->root, *term2 = this->root;
			size_t iter = 0, t1 = 0, t2 = 0;;
			bool is = false, first = true;
			while (iter < str_size)
			{
				is = true;
				for (register size_t i = 0; i < p->children.Size(); i++)
				{
					if (p->children[i]->key_val == key[iter])
					{
						p = p->children[i];
						if (first)
						{
							t2 = i;
							t1 = i;
							first = false;
						}
						if (p->isTerminal) 
						{ 
							term2 = term1; 
							term1 = p; 
							t2 = t1;
							t1 = i;
						}
						is = false;
						iter++;
						break;
					}
				}
				if (is) return false;
			}
			if (!p->isTerminal) return false;
			if (!p->children.IsEmpty())
			{
				p->isTerminal = false;
				return true;
			}
			p = term2->children[t2];
			term2->children.Remove(t2, 1);
			while (p)
			{
				TrieNode *k = p;
				if (p->children.IsEmpty()) p = nullptr;
				else p = p->children[0];
				delete k;
			}
			return true;
		}
		bool KeyExist(const char* key, size_t str_size)
		{
			TrieNode *p = this->root;
			size_t iter = 0;
			bool is = false;
			while (iter < str_size)
			{
				is = true;
				for (register size_t i = 0; i < p->children.Size(); i++)
				{
					if (p->children[i]->key_val == key[iter])
					{
						p = p->children[i];
						is = false;
						iter++;
						break;
					}
				}
				if (is) return false;
			}
			if (!p->isTerminal) return false;
			return true;
		}
		T GetValue(const char* key, size_t str_size)
		{
			TrieNode *p = this->root;
			size_t iter = 0;
			bool is = false;
			while (iter < str_size)
			{
				is = true;
				for (register size_t i = 0; i < p->children.Size(); i++)
				{
					if (p->children[i]->key_val == key[iter])
					{
						p = p->children[i];
						is = false;
						iter++;
						break;
					}
				}
				if (is) throw "Key is not found";
			}
			if (!p->isTerminal) throw "Key is not found";
			return p->data_value;
		}

		Trie& operator=(Trie &obj)
		{
			if (&obj == this) return *this;
			clear(this->root);
			this->root = nullptr;
			copy(this->root, obj.root);
			return *this;
		}

	private:
		void clear(TrieNode * node)
		{
			for (register size_t i = 0; i < node->children.Size(); i++)
				clear(node->children[i]);
			delete node;
		}
		void copy(TrieNode *&into, TrieNode *&from)
		{
			if (!from) { into = nullptr; return; }
			into = new TrieNode;

			into->key_val = from->key_val;
			into->children = from->children;
			into->isTerminal = from->isTerminal;
			into->data_value = from->data_value;

			size_t s = into->children.Size();
			for (register size_t i = 0; i < s; i++)
				copy(into->children[i], from->children[i]);
		}
	};
}