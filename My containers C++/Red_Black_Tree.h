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
			nil = new TreeNode();
			nil->red = false;
			nil->left = nil;
			nil->right = nil;
			nil->parent = nil;
			this->main_root = nil;
		}
		Red_Black_Tree(const Red_Black_Tree &obj)
		{
			nil = new TreeNode();
			nil->red = false;
			nil->left = nil;
			nil->right = nil;
			nil->parent = nil;
			if (obj.main_root == obj.nil)
				this->main_root = this->nil;
			else
			{
				this->main_root = new TreeNode;
				this->main_root->parent = this->nil;
				copy(this->main_root, obj.main_root, obj.nil);
			}
		}
		~Red_Black_Tree()
		{
			clear(this->main_root);
			delete nil;
			this->main_root = nullptr;
			this->nil = nullptr;
		}

		Red_Black_Tree& operator=(const Red_Black_Tree &obj)
		{
			if (&obj == this) return *this;
			clear(this->main_root);
			if (obj.main_root == obj.nil)
				this->main_root = this->nil;
			else
			{
				this->main_root = new TreeNode;
				this->main_root->parent = this->nil;
				copy(this->main_root, obj.main_root, obj.nil);
			}
			return *this;
		}

		bool Insert(T data)
		{
			if (this->main_root == nil)
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
			if (sub == this->main_root)
			{
				delete this->main_root;
				this->main_root = nil;
				return true;
			}
			if (sub->left == nil && sub->right == nil)
			{
				if (sub->red)
				{
					if (sub->parent->left == sub) sub->parent->left = nil;
					else sub->parent->right = nil;
					delete sub;
				}
				else
				{
					deleteBalance(sub);
					if (sub->parent->left == sub) sub->parent->left = nil;
					else sub->parent->right = nil;
					delete sub;
				}
			}
			else
			{
				if (sub->left != nil)
				{
					sub->data = sub->left->data;
					delete sub->left;
					sub->left = nil;
				}
				else
				{
					sub->data = sub->right->data;
					delete sub->right;
					sub->right = nil;
				}
			}
			return true;
		}

	private:
		void clear(TreeNode *node)
		{
			if (node == nil) return;
			clear(node->left);
			clear(node->right);
			delete node;
		}
		void copy(TreeNode *into, TreeNode *from, TreeNode *nil_from)
		{
			if (from == nil_from)
			{
				*into = *nil;
				return;
			}
			into->data = from->data;
			into->red = from->red;

			into->left = new TreeNode;
			into->left->parent = into;
			into->right = new TreeNode;
			into->right->parent = into;

			copy(into->left, from->left, nil_from);
			copy(into->right, from->right, nil_from);
		}

		inline void insertBalance(TreeNode *current)
		{
			if (!current->red || !current->parent->red) return;
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
				grandparent->red = true;
				if (current->parent->left == current)
				{
					if (grandparent->left == uncle) { current->red = false; RL_rotate(grandparent); }
					else { current->parent->red = false; R_rotate(grandparent); }
				}
				else
				{
					if (grandparent->left == uncle) { current->parent->red = false; L_rotate(grandparent); }
					else { current->red = false; LR_rotate(grandparent); }
				}
			}
			this->main_root->red = false;
		}
		inline void deleteBalance(TreeNode *current)
		{
			while (current != this->main_root)
			{
				TreeNode *parent = current->parent;
				TreeNode *bro = (parent->left == current ? parent->right : parent->left);
				if (parent->red)
				{
					if (bro->left->red || bro->right->red) // 1.1
					{
						parent->red = false;
						if (parent->left == current)
						{
							if (bro->left->red) RL_rotate(parent);
							else { bro->red = true; bro->right->red = false; L_rotate(parent); }
						}
						else
						{
							if (bro->left->red) { bro->red = true; bro->left->red = false; R_rotate(parent); }
							else LR_rotate(parent);
						}
						return;
					}
					else // 1.2
					{
						bro->red = true;
						parent->red = false;
						return;
					}
				}
				else
				{
					if (bro->red)
					{
						if (bro->left->left->red || bro->left->right->red || bro->right->left->red || bro->right->right->red) // 2.1.1
						{
							if (bro->parent->left == bro)
							{
								if (bro->left->left->red || bro->left->right->red) { bro->red = false; bro->right->red = true; R_rotate(parent); }
								else if (bro->right->left->red) { bro->right->left->red = false; LR_rotate(parent); }
								else if (bro->right->right->red) { bro->right->right->red = false; L_rotate(bro->right); LR_rotate(parent); }
							}
							else
							{
								if (bro->left->left->red) { bro->left->left->red = false; R_rotate(bro->left); RL_rotate(parent); }
								else if (bro->left->right->red) { bro->left->right->red = false; RL_rotate(parent); }
								else if (bro->right->left->red || bro->right->right->red) { bro->red = false; bro->left->red = true; L_rotate(parent); }
							}
							return;
						}
						else // 2.1.2
						{
							bro->red = false;
							if (bro == bro->parent->left)
							{
								bro->right->red = true;
								R_rotate(parent);
							}
							else
							{
								bro->left->red = true;
								L_rotate(parent);
							}
							return;
						}
					}
					else
					{
						if (bro->left->red || bro->right->red) // 2.2.1
						{
							if (parent->left == current)
							{
								if (bro->left->red) { bro->left->red = false; RL_rotate(parent); }
								else { bro->right->red = false; L_rotate(parent); }
							}
							else
							{
								if (bro->left->red) { bro->left->red = false; R_rotate(parent);}
								else { bro->right->red = false; LR_rotate(parent); }
							}
							return;
						}
						else // 2.2.2
						{
							bro->red = true;
							current = current->parent;
						}
					}
				}
			}
		}
		inline void L_rotate(TreeNode *p1)
		{
			TreeNode *p2 = p1->right;
			p1->right = p2->left;
			if (p2->left != nil) p2->left->parent = p1;
			p2->parent = p1->parent;
			if (p1->parent != nil)
			{
				if (p1->parent->left == p1) p1->parent->left = p2;
				else p1->parent->right = p2;
			}
			p1->parent = p2;
			p2->left = p1;
			if (p1 == this->main_root) this->main_root = p2;
		}
		inline void R_rotate(TreeNode *p1)
		{
			TreeNode *p2 = p1->left;
			p1->left = p2->right;
			if (p2->right != nil) p2->right->parent = p1;
			p2->parent = p1->parent;
			if (p1->parent != nil)
			{
				if (p1->parent->left == p1) p1->parent->left = p2;
				else p1->parent->right = p2;
			}
			p1->parent = p2;
			p2->right = p1;
			if (p1 == this->main_root) this->main_root = p2;
		}
		inline void LR_rotate(TreeNode *p1)
		{
			TreeNode *p2 = p1->left;
			TreeNode *p3 = p2->right;
			p2->right = p3->left;
			if (p3->left != nil) p3->left->parent = p2;
			p3->left = p2;
			p3->parent = p1->parent;
			p2->parent = p3;
			if (p1->parent != nil)
			{
				if (p1->parent->left == p1) p1->parent->left = p3;
				else p1->parent->right = p3;
			}
			p1->left = p3->right;
			if (p3->right != nil) p3->right->parent = p1;
			p3->right = p1;
			p1->parent = p3;
			if (this->main_root == p1) this->main_root = p3;
		}
		inline void RL_rotate(TreeNode *p1)
		{
			TreeNode *p2 = p1->right;
			TreeNode *p3 = p2->left;
			p2->left = p3->right;
			if (p3->right != nil) p3->right->parent = p2;
			p3->right = p2;
			p3->parent = p1->parent;
			p2->parent = p3;
			if (p1->parent != nil)
			{
				if (p1->parent->left == p1) p1->parent->left = p3;
				else p1->parent->right = p3;
			}
			p1->right = p3->left;
			if (p3->left != nil) p3->left->parent = p1;
			p3->left = p1;
			p1->parent = p3;
			if (this->main_root == p1) this->main_root = p3;
		}
	};
}