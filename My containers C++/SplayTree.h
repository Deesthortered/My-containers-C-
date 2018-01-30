#pragma once

namespace spaceSplayTree
{
	template<class T>
	class SplayTree
	{
		struct TreeNode
		{
			T data;
			TreeNode *left;
			TreeNode *right;
			TreeNode *parent;
			TreeNode(T _data, TreeNode *_parent) : data(_data), left(nullptr), right(nullptr), parent(_parent) {}
		};

		TreeNode *root;

	public:
		SplayTree()
		{
			this->root = nullptr;
		}
		SplayTree(SplayTree &obj)
		{
			copy(this->root, obj.root);
		}
		~SplayTree()
		{
			clear(this->root);
			this->root = nullptr;
		}

		SplayTree& operator=(SplayTree &obj)
		{
			clear(this->root);
			copy(this->root, obj.root);
			return *this;
		}

		T Search(T data)
		{
			TreeNode *res = search(data, this->root);
			return (res ? res->data : T());
		}
		bool Insert(T data)
		{
			if (!this->root)
			{
				this->root = new TreeNode(data, nullptr);
				return false;
			}
			TreeNode *p = this->root, *current = nullptr;
			while (p)
			{
				current = p;
				if (p->data < data) p = p->right;
				else if (p->data > data) p = p->left;
				else return true;
			}
			if (current->data < data)
			{
				current->right = new TreeNode(data, current);
				splay(current->right);
			}
			else
			{
				current->left = new TreeNode(data, current);
				splay(current->left);
			}
			return false;
		}
		bool Delete(T data)
		{
			TreeNode *p = search(data);
			if (!p) return false;
			this->root = merge(p->left, p->right);
			delete p;
			return true;
		}

	private:
		void splay(TreeNode *node)
		{
			while (node->parent)
			{
				if (!node->parent->parent)
				{
					if (node->parent->left == node) R_rotate(node->parent);
					else L_rotate(node->parent);
				}
				else
				{
					if (node->parent->left == node)
					{
						if (node->parent->parent->left == node->parent) { R_rotate(node->parent->parent); R_rotate(node->parent); }
						else RL_rotate(node->parent->parent);
					}
					else
					{
						if (node->parent->parent->left == node->parent) LR_rotate(node->parent->parent);
						else { L_rotate(node->parent->parent); L_rotate(node->parent); };
					}
				}
			}
		}
		TreeNode* search(T data)
		{
			TreeNode *p = this->root;
			while (p)
			{
				if (p->data < data) p = p->right;
				else if (p->data > data) p = p->left;
				else break;
			}
			if (!p) return nullptr;
			splay(p);
			return p;
		}
		TreeNode* merge(TreeNode *p1, TreeNode *p2)
		{
			if (p1 && p2)
			{
				p1->parent = nullptr;
				p2->parent = nullptr;
				while (p1->right) p1 = p1->right;
				splay(p1);
				p1->right = p2;
			}
			else return(p1 ? p1 : p2);
			return p1;
		}

		// По идее (по википедии) должна использоваться для Insert, но я не вижу смысла.
		void split(TreeNode *&p1, TreeNode *&p2, T pivot)
		{
			p1 = search(pivot);
			p2 = p1->left;
			p1->left = nullptr;
		}

		void clear(TreeNode *node)
		{
			if (!node) return;
			clear(node->left);
			clear(node->right);
			delete node;
		}
		void copy(TreeNode *&into, TreeNode *&from, TreeNode *parent = nullptr)
		{
			if (!from) return;
			into = new TreeNode(from->data, parent);
			copy(into->left, from->left, into);
			copy(into->right, from->right, into);
		}

		inline void L_rotate(TreeNode *p1)
		{
			TreeNode *p2 = p1->right;
			p1->right = p2->left;
			if (p2->left != nullptr) p2->left->parent = p1;
			p2->parent = p1->parent;
			if (p1->parent != nullptr)
			{
				if (p1->parent->left == p1) p1->parent->left = p2;
				else p1->parent->right = p2;
			}
			p1->parent = p2;
			p2->left = p1;
			if (p1 == this->root) this->root = p2;
		}
		inline void R_rotate(TreeNode *p1)
		{
			TreeNode *p2 = p1->left;
			p1->left = p2->right;
			if (p2->right != nullptr) p2->right->parent = p1;
			p2->parent = p1->parent;
			if (p1->parent != nullptr)
			{
				if (p1->parent->left == p1) p1->parent->left = p2;
				else p1->parent->right = p2;
			}
			p1->parent = p2;
			p2->right = p1;
			if (p1 == this->root) this->root = p2;
		}
		inline void LR_rotate(TreeNode *p1)
		{
			TreeNode *p2 = p1->left;
			TreeNode *p3 = p2->right;
			p2->right = p3->left;
			if (p3->left != nullptr) p3->left->parent = p2;
			p3->left = p2;
			p3->parent = p1->parent;
			p2->parent = p3;
			if (p1->parent != nullptr)
			{
				if (p1->parent->left == p1) p1->parent->left = p3;
				else p1->parent->right = p3;
			}
			p1->left = p3->right;
			if (p3->right != nullptr) p3->right->parent = p1;
			p3->right = p1;
			p1->parent = p3;
			if (this->root == p1) this->root = p3;
		}
		inline void RL_rotate(TreeNode *p1)
		{
			TreeNode *p2 = p1->right;
			TreeNode *p3 = p2->left;
			p2->left = p3->right;
			if (p3->right != nullptr) p3->right->parent = p2;
			p3->right = p2;
			p3->parent = p1->parent;
			p2->parent = p3;
			if (p1->parent != nullptr)
			{
				if (p1->parent->left == p1) p1->parent->left = p3;
				else p1->parent->right = p3;
			}
			p1->right = p3->left;
			if (p3->left != nullptr) p3->left->parent = p1;
			p3->left = p1;
			p1->parent = p3;
			if (this->root == p1) this->root = p3;
		}
	};
}