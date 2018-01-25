#pragma once

namespace spaceRed_Black_Tree
{
	template<class T>
	class Red_Black_Tree
	{
		struct TreeNode
		{
			T data;
			bool red;
			TreeNode *left;
			TreeNode *right;
			TreeNode *parent;
			TreeNode() = default;
			TreeNode(T _data, TreeNode * _parent, TreeNode *nil) : data(_data), red(true), parent(_parent), left(nil), right(nil) {}
		};

		TreeNode *main_root;
		TreeNode *nil;
	public:
		Red_Black_Tree()
		{
			main_root = nullptr;
			nil = new TreeNode();
			nil->red = false;
		}
		~Red_Black_Tree()
		{
			clear(this->main_root);
			delete nil;
		}

		bool Insert(T data)
		{
			if (!this->main_root)
			{
				this->main_root = new TreeNode(data, nil, nil);
				this->main_root->red = false;
				return false;
			}
			TreeNode *p = this->main_root, *current = nullptr;
			while (p != nil)
			{
				current = p;
				if (p->data < data) p = p->right;
				else if (p->data > data) p = p->left;
				else return true;
			}
			if (current->data < data) 
			{
				current->right = new TreeNode(data, current, nil);
				insertBalance(current->right);
			}
			else
			{
				current->left = new TreeNode(data, current, nil);
				insertBalance(current->left);
			}
			while (current != nil)
			{
				insertBalance(current);
				current = current->parent;
			}
			return false;
		}
		bool Delete(T data)
		{
			TreeNode *current = this->main_root;
			while (current->data != data && current != nil)
			{
				if (current->data > data) current = current->left;
				else if (current->data < data) current = current->right;
			}
			if (current == nil) return false;
			TreeNode *sub = current;
			if (current->left != nil)
			{
				sub = current->left;
				while (sub->right != nil) sub = sub->right;
			}
			else if (current->right != nil)
			{
				sub = current->right;
				while (sub->left != nil) sub = sub->left;
			}
			current->data = sub->data;
			deleteBalance(sub);
			if (sub->parent->left == sub) sub->parent->left = nil;
			else sub->parent->right = nil;
			delete sub;
			return true;
		}

	private:
		void clear(TreeNode *node)
		{
			if (node == nil || !node) return;
			clear(node->left);
			clear(node->right);
			delete node;
		}

		inline void insertBalance(TreeNode *&current)
		{
			if (!current->parent->red) return;
			TreeNode *grandparent = current->parent->parent;
			TreeNode *uncle = (grandparent->left == current->parent ? grandparent->right : grandparent->left);
			if (uncle->red)
			{
				grandparent->red = true;
				uncle->red = false;
				current->parent->red = false;
			}
			else
			{
				current->parent->red = false;
				grandparent->red = true;
				if (current->parent->left == current)
				{
					if (grandparent->left == uncle) LR_rotate(grandparent);
					else R_rotate(grandparent);
				}
				else
				{
					if (grandparent->left == uncle) L_rotate(grandparent);
					else RL_rotate(grandparent);;
				}
			}
			this->main_root->red = false;
		}
		inline void deleteBalance(TreeNode *&current)
		{
			if (current->red)
			{
				if (current->parent->left == current) current->parent->left = nil;
				else current->parent->right = nil;
				return;
			}
			TreeNode *p = (current->left->red ? current->left : current->right);
			if (p->red)
			{
				current->data = p->data;
				if (current->left == p) current->left = nil;
				else current->right = nil;
				current = p;
				return;
			}
			if (current == this->main_root)
			{
				delete this->main_root;
				this->main_root = nullptr;
				return;
			}
			TreeNode *node = current;
			while (!node->red && node != this->main_root)
			{
				TreeNode *bro = (node->parent->left == node ? node->parent->right : node->parent->left);
				TreeNode *parent = bro->parent;
				if (bro->red)
				{
					bro->red = false;
					node->parent->red = true;
					if (node->parent->left == bro) R_rotate(parent);
					else L_rotate(parent);
				}
				else
				{
					if (bro->right->red)
					{
						bro->red = node->parent->red;
						bro->right->red = false;
						bro->parent->red = false;
						if (bro->parent->left == bro) R_rotate(parent);
						else L_rotate(parent);
						return;
					}
					else if (bro->left->red)
					{
						bro->red = true;
						bro->left->red = false;
						if (bro->parent->left == bro) L_rotate(parent);
						else R_rotate(parent);
					}
					else if (bro != nil)
					{
						bro->red = true;
						node->parent->red = false;
					}
				}
				node = node->parent;
			}
		}
		inline void L_rotate(TreeNode *&p1)
		{
			TreeNode *p2 = p1->right;
			p1->right = p2->left;
			if (p2->left != nil && p2->left) p2->left->parent = p1;
			p2->parent = p1->parent;
			if (p1->parent != nil && p1->parent)
			{
				if (p1->parent->left == p1) p1->parent->left = p2;
				else p1->parent->right = p2;
			}
			p1->parent = p2;
			p2->left = p1;
			if (p1 == this->main_root) this->main_root = p2;
		}
		inline void R_rotate(TreeNode *&p1)
		{
			TreeNode *p2 = p1->left;
			p1->left = p2->right;
			if (p2->right && p2->right != nil) p2->right->parent = p1;
			p2->parent = p1->parent;
			if (p1->parent != nil && p1->parent)
			{
				if (p1->parent->left == p1) p1->parent->left = p2;
				else p1->parent->right = p2;
			}
			p1->parent = p2;
			p2->right = p1;
			if (p1 == this->main_root) this->main_root = p2;
		}
		inline void LR_rotate(TreeNode *&p1)
		{
			TreeNode *p2 = p1->left;
			TreeNode *p3 = p2->right;
			p2->right = p3->left;
			if (p3->left && p3->left != nil) p3->left->parent = p2;
			p3->left = p2;
			p3->parent = p1->parent;
			p2->parent = p3;
			if (p1->parent && p1->parent != nil)
			{
				if (p1->parent->left == p1) p1->parent->left = p3;
				else p1->parent->right = p3;
			}
			p1->left = p3->right;
			if (p3->right && p3->right != nil) p3->right->parent = p1;
			p3->right = p1;
			p1->parent = p3;
			if (this->main_root == p1) this->main_root = p3;
		}
		inline void RL_rotate(TreeNode *&p1)
		{
			TreeNode *p2 = p1->right;
			TreeNode *p3 = p2->left;
			p2->left = p3->right;
			if (p3->right && p3->right != nil) p3->right->parent = p2;
			p3->right = p2;
			p3->parent = p1->parent;
			p2->parent = p3;
			if (p1->parent && p1->parent != nil)
			{
				if (p1->parent->left == p1) p1->parent->left = p3;
				else p1->parent->right = p3;
			}
			p1->right = p3->left;
			if (p3->left && p3->left != nil) p3->left->parent = p1;
			p3->left = p1;
			p1->parent = p3;
			if (this->main_root == p1) this->main_root = p3;
		}
	};
}