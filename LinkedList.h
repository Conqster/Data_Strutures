#pragma once
#include <iostream>






//////////////////////////////////
// Linked List 
//////////////////////////////////
template<typename T>
class LinkedList
{
	struct Node
	{
		T data;
		Node* next = nullptr;

		Node(T _data)
		{
			data = _data;
		}
	};

	Node* head = nullptr;

	unsigned int count = 0;
public:
	LinkedList()
	{
		std::cout << "Linked list created with count " << count << "\n";
	}

	inline Node* NodeHead() const { return head; }
	inline unsigned int Count() const { return count; }

	void Push(T data)
	{
		Node* new_node = new Node(data);

		//std::cout << "Created node with data: " << new_node << "\n";

		//set new_node as head
		if (head == nullptr)
		{
			head = new_node;
			count++;
			return;
		}

		//use to read down the list for vacancies, a next nullptr 
		Node* current = head;

		while (current->next != nullptr)
			current = current->next;

		current->next = new_node;
		count++;
	}


	T operator[](int idx)
	{
		if (head == nullptr || idx > count - 1)
		{
			std::cout << "out of bounds !!!!!!!!!\n";
		}

		//use to read down the list for vacancies, a next nullptr 
		Node* current = head;

		for (int i = 0; i < idx; i++)
			current = current->next;

		return current->data;
	}


	void Pop_At(int idx)
	{
		if (head == nullptr || idx > count - 1)
		{
			std::cout << "out of bounds !!!!!!!!!\n";
			return;
		}

		//use to read down the list for vacancies, a next nullptr 
		Node* current = head;


		//this is, if idx is at the head
		if (idx == 0)
		{
			head = current->next;
			count--;
			return;
		}

		Node* prev = head;

		for (int i = 0; i < idx; i++)
		{
			prev = current;
			current = current->next;
		}

		prev->next = current->next;
		count--;
		return;
	}

	/// <summary>
	/// might want to check the fastest start loop
	/// head or tail
	/// </summary>
	/// <param name="data"></param>
	/// <param name="idx"></param>
	void Insert_At(T data, int idx)
	{
		if (idx > count - 1)
		{
			std::cout << "out of bounds !!!!!!!!!\n";
			return;
		}

		Node* new_node = new Node(data);

		if (idx == 0)
		{
			//T old_head = this[idx];
			new_node->next = head;
			head = new_node;
			count++;
			return;
		}

		//use to read down the list for vacancies, a next nullptr 
		Node* current = head;
		Node* prev = head;

		for (int i = 0; i < idx; i++)
		{
			prev = current;
			current = current->next;
		}

		prev->next = new_node;
		new_node->next = current;
		count++;
	}


	int Find_idx(T data)
	{
		Node* current = head;

		if (!current)
			return -1;

		for (int i = 0; i < count; i++)
		{
			if (current->data == data)
				return i;

			current = current->next;
		}

		return -1;
	}

	void Debug_All_Nodes()
	{
		Node* current = head;
		int idx = 0;

		while (current != nullptr)
		{
			std::cout << "Element/Node " << idx << ": " << current->data << "\n";
			idx++;
			current = current->next;
		}
	}

	
};





