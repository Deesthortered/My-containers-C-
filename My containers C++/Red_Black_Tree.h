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
				Balance(current->right);
			}
			else
			{
				current->left = new TreeNode(data, current, nil);
				Balance(current->left);
			}
			while (current != nil)
			{
				Balance(current);
				current = current->parent;
			}
			return false;
		}

	private:
		void clear(TreeNode *node)
		{
			if (node == nil || !node) return;
			clear(node->left);
			clear(node->right);
			delete node;
		}

		inline void Balance(TreeNode *&current)
		{
			if (!current->parent->red) return;
			TreeNode *grandparent = current->parent->parent;
			TreeNode *uncle = (grandparent->left == current->parent ? grandparent->right : grandparent->left);
			if (uncle->red)
			{
				if (grandparent != this->main_root) grandparent->red = true;
				uncle->red = false;
				current->parent->red = false;
			}
			else
			{
				current->parent->red = false;
				grandparent->red = true;
				if (current->parent->left == current)
				{
					if (grandparent->left == uncle) LR_rot(grandparent);
					else R_rot(grandparent);
				}
				else
				{
					if (grandparent->left == uncle) L_rot(grandparent);
					else RL_rot(grandparent);;
				}
			}
			this->main_root->red = false;
		}
		inline void L_rot(TreeNode *&p1)
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
		inline void R_rot(TreeNode *&p1)
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
		inline void LR_rot(TreeNode *&p1)
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
		inline void RL_rot(TreeNode *&p1)
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