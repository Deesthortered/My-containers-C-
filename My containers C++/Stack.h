#pragma once

namespace spaceStack
{
	template<class T>
	class Stack
	{
		struct Node
		{
			T data;
			Node *next;
			Node(T _data, Node *_next) : data(_data), next(_next) {}
		};
		
		Node *head;

	public:
		Stack()
		{
			this->head = nullptr;
		}
		Stack(const Stack &obj)
		{
			Stack tmp;
			Node *p = obj.head;
			while (p)
			{
				tmp.Push(p->data);
				p = p->next;
			}
			while (!tmp.IsEmpty())
			{
				this->Push(tmp.Extract());
				tmp.Pop();
			}
		}
		~Stack()
		{
			Clear();
		}

		Stack& operator=(const Stack &obj)
		{
			Clear();
			Stack tmp;
			Node *p = obj.head;
			while (p)
			{
				tmp.Push(p->data);
				p = p->next;
			}
			while (!tmp.IsEmpty())
			{
				this->Push(tmp.Extract());
				tmp.Pop();
			}
			return *this;
		}

		void Push(T data)
		{
			this->head = new Node(data, this->head);
		}
		void Pop()
		{
			Node *p = this->head;
			this->head = this->head->next;
			delete p;
		}
		T Extract()
		{
			return head->data;
		}

		void Clear()
		{
			while (this->head)
			{
				Node *p = this->head;
				this->head = this->head->next;
				delete p;
			}
		}

		bool IsEmpty()
		{
			return (this->head ? false : true);
		}
	};
}