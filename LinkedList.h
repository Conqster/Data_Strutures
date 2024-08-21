#pragma once
#include <iostream>

#include "TimeTaken.h"




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

		Node() : data(0), next(nullptr){}

		Node(T _data)
			: data(_data), next(nullptr)
		{}
	};

	Node* head = nullptr;

	unsigned int count = 0;
public:
	LinkedList()
	{
		std::cout << "Linked list created with count " << count << "\n";
	}

	~LinkedList()
	{
		if (head)
		{
			Node* current = head;

			head = nullptr;

			while (current)
			{
				Node* temp = current;
				current = current->next;
				delete temp;
			}

		}
	}

	inline Node* NodeHead() const { return head; }
	inline unsigned int Count() const { return count; }

	void Push_Back(T data)
	{
		Node* new_node = new Node(data);

		//std::cout << "Created node with data: " << new_node << "\n";

		//set new_node as head
		if (!head)
		{
			head = new_node;
			count++;
			return;
		}

		//use to read down the list for vacancies, a next nullptr 
		Node* current = head;

		while (current->next)
			current = current->next;

		current->next = new_node;
		count++;
	}

	void Push_Front(T data)
	{
		Node* new_node = new Node(data);

		//A list a, b, c, 
		// to as an element d @ front to become => d, a, b, c, i.e head == d 
		// d next> a, a next> remains the same b 
		// head becomes d from a 

		if (head)
			new_node->next = head;

		head = new_node;
		count++;
	}

	T Top_Front()
	{
		if (!head)
			throw std::out_of_range("List is empty!!!!!!!!");

		return head->data;
	}

	T Top_Back()
	{
		//return the last element 
		//since i am keeping track of the count should be fine

		if (!head)
			throw std::out_of_range("List is empty!!!!!!!!");



		Node* current = head;

		for (int i = 0; i < (count - 1); i++)
			current = current->next;

		return current->data;

		//return (LinkedList<T>)*this[count];
	}


	T operator[](int idx)
	{
		if (!head || idx > count - 1)
		{
			std::cout << "out of bounds !!!!!!!!!\n";
		}


		Node* current = head;

		for (int i = 0; i < idx; i++)
			current = current->next;

		return current->data;
	}


	void Pop_At(int idx)
	{
		if (!head || idx > count - 1)
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




	void Pop_Back()
	{
		if (count == 0)
		{
			std::cout << "List is empty.........\n";
			return;
		}

		Node* current = head;

		//this get the secons to the last node/element
		for (int i = 0; i < count - 2; i++)
		{
			current = current->next;
		}
		delete current->next;
		current->next = nullptr;
		count--;

	}

	void Pop_Front()
	{
		if (!head)
		{
			//throw std::out_of_range("List is empty!!!!!!!!");
			return;
		}

		//A list a, b, c, d
		//Pop_Front removes a 
		//prev, head == a & (a next> b )
		//after head == b  & (b next> c remains the same) 

		head = head->next;
		count--;
	}


	void Remove(T data)
	{
		int idx = Find_idx(data);

		if (idx == -1)
			std::cout << "Node/Element does not exist \n";
		else
			Pop_At(idx);
	}


	void Remove_At(int idx)
	{
		Pop_At(idx);
	}

	void Reverse()
	{
		TimeTaken("Reversing List Time Taken");
		//Let say we have a list of integers 
		//0 1 2
		//by recursively swaping curr with nxt 
		//1 0 2
		//1 2 0
		//2 1 0
		head = RecursiveTranversalSwaping(head, nullptr);
		//head = RecursiveTranversalSwaping();
	}



	Node* RecursiveTranversalSwaping(Node* current, Node* prev)
	{
		//current sample will null, if we are sampling the last (tail) node's next
		//i.e its prev is the last node
		if (!current)
			return prev;

		Node* nxt = current->next;
		current->next = prev;    //swap the current's to the prev node "to reverse current sample)

		return RecursiveTranversalSwaping(nxt, current);
	}

	Node* RecursiveTranversalSwaping()
	{
		Node* prev = nullptr;
		Node* current = head;
		Node* nxt = nullptr;

		while (current)
		{
			nxt = current->next;
			current->next = prev;
			prev = current;
			current = nxt;
		}

		return prev;
	}


	/////////////////////////////////////////////////////////
	// DEBUGGER'S
	/////////////////////////////////////////////////////////
	/// <summary>
	/// Your data type should support operator << 
	/// </summary>
	void Debug_All_Nodes()
	{
		Node* current = head;
		int idx = 0;

		if (!current)
			return;

		//In the hope that template T supports operator << for printing
		while (current)
		{
			std::cout << "Element/Node " << idx << ": " << current->data << "\n";
			idx++;
			current = current->next;
		}
	}


	
};




void NewSampleList()
{
	LinkedList<std::string> list;

	list.Push_Back("Jack");
	list.Push_Back("Jake");


	std::cout << "Print all the element in the list and Jake should be the last item!!!!!!!\n";

	list.Debug_All_Nodes();

	std::cout << "The first element of the list should be 'Jack' : " << list.Top_Front() << "\n";

	std::cout << " Adding Sam at the front !!!!!!!!\n";

	list.Push_Front("Sam");

	list.Debug_All_Nodes();

	std::cout << "The last element of the list should be 'Jake' : " << list.Top_Back() << "\n";

	list.Pop_Back();

	std::cout << "Deleted / Pop the last element in the list. \n ";

	list.Debug_All_Nodes();

	list.Push_Back("Nick");
	list.Push_Back("Nike");
	std::cout << "Added Nick & Nike !!!!!!!\n";

	list.Pop_Front();

	std::cout << "Deleted / Pop the first elment in the list.\n";
	list.Pop_Front();
	list.Pop_Front();
	list.Pop_Front();
	list.Pop_Front();
	list.Debug_All_Nodes();
}


/////////////////////////////////////////////////////////
// Sample
/////////////////////////////////////////////////////////


void SampleLinkedList()
{
	LinkedList<std::string> list;

	///////////////////////////////////////////////
	// For integers 
	///////////////////////////////////////////////
	//list.Push(10);
	//list.Push(23);
	//list.Push(35);
	//list.Push(29);

	//std::cout << "List Count " << list.Count() << "\n";
	//std::cout << "Node at idx 0: " << list[0] << "\n";
	//std::cout << "Node at idx 1: " << list[1] << "\n";



	////////////////////////////////////////////////
	// For strings 
	////////////////////////////////////////////////
	std::cout << "My list count " << list.Count() << "\n";

	////////////////////////////////////////////////
	//Adding element to list using Push()
	////////////////////////////////////////////////
	list.Push_Back("Hill");
	list.Push_Back("Jack");
	list.Push_Back("Nick");
	list.Push_Back("Jill");
	list.Push_Back("Jay");

	std::cout << "My list count " << list.Count() << "\n";
	std::cout << "First/Head node is " << list.NodeHead()->data << "\n";


	//////////////////////////////////////////////////
	// test operator[] to retrived data 
	//////////////////////////////////////////////////
	std::cout << "Node at idx 0 is " << list[0] << "\n";
	std::cout << "Node at idx 1 is " << list[1] << "\n";
	std::cout << "Node at idx 2 is " << list[2] << "\n";
	std::cout << "Node at idx 3 is " << list[3] << "\n";

	std::cout << "========================================================================================\n";
	std::cout << "========================================================================================\n";
	std::cout << "========================================================================================\n";

	//////////////////////////////////////////////////
	// Test Poping element at a specific index
	//////////////////////////////////////////////////
	std::cout << "count before poping " << list.Count() << "\n";
	std::cout << "Going to Pop_At idx 3 which element is " << list[3] << "\n";
	list.Pop_At(3);
	std::cout << "count after poping " << list.Count() << "\n";

	////////////////////////////////////////////////////
	// Test Inserting at a specific idx using, .Insert_At(data,idx)
	////////////////////////////////////////////////////
	std::cout << "========================================================================================\n";
	std::cout << "===================================USING.Insert_At======================================\n";
	std::cout << "========================================================================================\n";
	list.Debug_All_Nodes();
	std::cout << "count before " << list.Count() << "\n";
	std::cout << "========================================================================================\n";
	list.Insert_At("Frank", 2);
	std::cout << "Added to idx 2 Frank\n";
	list.Debug_All_Nodes();
	std::cout << "count after " << list.Count() << "\n";

	std::cout << "========================================================================================\n";
	std::cout << "===================================USING Find_idx=======================================\n";
	std::cout << "========================================================================================\n";

	////////////////////////////////////////////////////
	// Test Find_idx(data) returns -1 if does not exist
	////////////////////////////////////////////////////
	std::cout << "Find idx of 'Jack': " << list.Find_idx("Jack") << "\n";
	std::cout << "Find idx of 'wgru': " << list.Find_idx("wgru") << "\n";


	std::cout << "========================================================================================\n";
	std::cout << "======================================USING Remove, Remove_At & Pop_At=====================\n";
	std::cout << "========================================================================================\n";

	////////////////////////////////////////////////////
	// Test Remove, Remove_At & Pop_At 
	////////////////////////////////////////////////////
	std::cout << "Before removeing Jill & Jack, if they exist\n";
	list.Debug_All_Nodes();
	list.Remove("Jill");
	list.Remove("Jack");
	std::cout << "After removeing Jill\n";
	list.Debug_All_Nodes();
	list.Remove_At(0);
	std::cout << "removeing at idx 0 \n";
	list.Pop_At(0);
	std::cout << "Pop at idx 0 \n";
	std::cout << "Pop_At & Remove_At are similar\n";

	std::cout << "========================================================================================\n";
	std::cout << "===================================USING Reversing the list=============================\n";
	std::cout << "========================================================================================\n";


	////////////////////////////////////////////////////
	// Test Reversing  List
	////////////////////////////////////////////////////
	std::cout << "list before reverse" << "\n";
	list.Debug_All_Nodes();
	list.Reverse();
	std::cout << "list after reverse" << "\n";
	list.Debug_All_Nodes();


	std::cout << "========================================================================================\n";
	std::cout << "===================================USING Pop============================================\n";
	std::cout << "========================================================================================\n";

	////////////////////////////////////////////////////
	// Test Pop, to delete last element
	////////////////////////////////////////////////////
	std::cout << "count before Pop " << list.Count() << "\n";
	list.Pop_Back();
	std::cout << "count after Pop " << list.Count() << "\n";
}

