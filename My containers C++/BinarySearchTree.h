#pragma once

namespace spaceBinarySearchTree
{
	template<class T>
	class BinarySearchTree
	{
		struct TreeNode
		{
			T data;
			TreeNode *left;
			TreeNode *right;
			TreeNode(T _data) : data(_data), left(nullptr), right(nullptr) {}
		};

		TreeNode *root;

	public:
		BinarySearchTree()
		{
			this->root = nullptr;
		}
		BinarySearchTree(BinarySearchTree &obj)
		{
			copy(this->root, obj.root);
		}
		~BinarySearchTree()
		{
			clear(this->root);
			this->root = nullptr;
		}

		BinarySearchTree& operator=(BinarySearchTree &obj)
		{
			Clear();
			copy(this->root, obj.root);
			return *this;
		}

		bool IsEmpty()
		{
			return (this->main_root ? false : true);
		}
		T Find(T data)
		{
			TreeNode *p = this->main_root;
			while (p && p->data != data)
			{
				if (p->data < data) p = p->right;
				else if (p->data > data) p = p->left;
			}
			if (!p) return T();
			return p->data;
		}
		bool Insert(T data)
		{
			return insert(data, this->root);
		}
		bool Delete(T data)
		{
			return deletenode(data, this->root);
		}
		void Clear()
		{
			clear(this->root);
		}

	private:
		bool insert(T data, TreeNode *&node)
		{
			if (!node)
			{
				node = new TreeNode(data);
				return false;
			}
			if (data > node->data)
			{
				if (node->right != nullptr) return insert(data, node->right);
				else node->right = new TreeNode(data);
			}
			else if (data < node->data)
			{
				if (node->left != nullptr) return insert(data, node->left);
				else node->left = new TreeNode(data);
			}
			else if (data == node->data) { return true; }
			return false;
		}
		bool deletenode(T data, TreeNode *&node)
		{
			if (!node) return false;
			if (data < node->data) return deletenode(data, node->left);
			else if (data > node->data) return deletenode(data, node->right);
			else
			{
				if ((node->left == nullptr) || (node->right == nullptr))
				{
					TreeNode *temp = (node->left ? node->left : node->right);
					if (temp == nullptr)
					{
						temp = node;
						node = nullptr;
					}
					else *node = *temp;
					delete temp;
				}
				else
				{
					TreeNode *temp = node->right;
					while (temp->left != nullptr) temp = temp->left;
					node->data = temp->data;
					deletenode(temp->data, node->right);
				}
			}
			return true;
		}
		void clear(TreeNode *node)
		{
			if (!node) return;
			clear(node->left);
			clear(node->right);
			delete node;
		}
		void copy(TreeNode *&into, TreeNode *&from)
		{
			if (!from) return;
			into = new TreeNode(from->data);
			copy(into->left, from->left);
			copy(into->right, from->right);
		}
	};
}