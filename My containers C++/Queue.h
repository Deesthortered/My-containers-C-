#pragma once

namespace spaceQueue
{
	template<class T>
	class Queue
	{
		struct Node
		{
			T data;
			Node *next;
			Node(T _data, Node *_next) : data(_data), next(_next) {}
		};

		Node *head;
		Node *tail;

	public:
		Queue()
		{
			this->head = nullptr;
			this->tail = nullptr;
		}		
		Queue(const Queue &obj)
		{
			Node *p = obj.head;
			while (p)
			{
				Push(p->data);
				p = p->next;
			}
		}
		~Queue()
		{
			Clear();
		}

		Queue& operator=(const Queue &obj)
		{
			Clear();
			Node *p = obj.head;
			while (p)
			{
				Push(p->data);
				p = p->next;
			}
			return *this;
		}

		void Push(T data)
		{
			if (!this->head)
			{
				this->head = new Node(data, this->head);
				this->tail = this->head;
				return;
			}
			this->tail->next = new Node(data, nullptr);
			this->tail = this->tail->next;
		}
		void Pop()
		{
			Node *p = this->head;
			this->head = this->head->next;
			delete p;
		}
		T Extract()
		{
			return this->head->data;
		}

		void Clear()
		{
			while (this->head)
			{
				this->tail = this->head;
				this->head = this->head->next;
				delete this->tail;
			}
			this->tail = nullptr;
		}

		bool IsEmpty()
		{
			return (this->head ? false : true);
		}
	};
}