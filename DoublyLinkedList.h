/*Purpose experimentimg doubly link list list after singly linked list 
  Diff
  Requires more memeory to store prev node
  Used for more complex data management, due to its bidirectional tranversal*/

#pragma once

template<typename T>
class DoublyLinkedList
{
	struct Node
	{
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;


		Node() : data(0), next(nullptr), prev(nullptr) {}

		Node(T _data)
			: data(_data), next(nullptr), prev(nullptr) {}
	};

	Node* head = nullptr;
	Node* tail = nullptr;

	unsigned int count = 0;

public:
	DoublyLinkedList()
	{
		std::cout << "Doubly Linked list created with count " << count << "\n";
	}

	inline Node* DebugHeadNode() const { return head; }
	inline Node* DebugTailNode() const { return tail; }
	inline unsigned int Count() const { return count; }

	void Push(T data)
	{
		Node* new_node = new Node(data);

		if (head == nullptr)
		{
			head = new_node;
			tail = new_node;
			count++;
			return;
		}

		//////
		// The tail 
		// This made it efficient to add to the list, unlike
		// singly linked link that you have to tranverse down the list to add 
		//////

		//old tail next is the new node 
		tail->next = new_node;
		new_node->prev = tail;         //the new node's (new_node) prev would be the old prev
		tail = new_node;

		//(Quick hack): readjust head & tail 
		head->prev = tail;
		tail->next = head;
		count++;
	}


	T operator[](int idx)
	{
		if (head == nullptr || idx > count - 1)
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
		if (head == nullptr || idx > count - 1)
		{
			std::cout << "out of bounds !!!!!!!!!\n";
			return;
		}

		//this is, if idx is at the head,
		//This might be bad, as i have an allocated memory that is now loss in track
		if (idx == 0)
		{
			head = head->next;
			tail->next = head;
			head->prev = tail;
			count--;
			return;
		}

		//To-do: later check to traversal forwards / backward based on the list count and provided idx
		Node* current = head;
		//Node* current = tail;

		//for(int i = count - 1; i > idx; i--)
		//	current = current->prev;

		for (int i = 0; i < idx; i++)
			current = current->next;

		//Np N Nn ===== Goal to remove N
		// N - current node, Np - its previous, Nn - its next
		//Np's new next (current->prev->next) = Nn
		//Nn's new prev (current->next->prev) = Np

		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
		count--;
	}



	void Debug_All_Nodes()
	{
		if (head == nullptr)
			return;

		Node* current = head;

		//In the hope that template T supports operator << for printing
		//using a for loop, as a while loop might cause an endless loop
		for (int i = 0; i < count; i++)
		{
			std::cout << "Element/Node " << i << ": " << current->data << "\n";
			current = current->next;
		}
	}

	void Debug_All_Nodes_Wc_Links()
	{
		if (head == nullptr)
			return;

		Node* current = head;

		//In the hope that template T supports operator << for printing
		//using a for loop, as a while loop might cause an endless loop
		for (int i = 0; i < count; i++)
		{
		

			std::cout << "Element/Node " << i << ": " << current->data << "\n";

			if (current->prev)
				std::cout << "Its prev: " << current->prev->data << "\n";
			else
				std::cout << "No Prev for " << current->data << "\n";

			if (current->next)
				std::cout << "Its next: " << current->next->data << "\n";
			else
				std::cout << "No next for " << current->data << "\n";
			
			current = current->next;
		}
	}
};



/////////////////////////////////////////////////////////
// Sample
/////////////////////////////////////////////////////////


void SampleDoublyLinkedList()
{
	std::cout << "Hello Doubly Linked List !!!!!!!!!!!!!!!\n";

	///////////////////////////////////////////////
	// For integers 
	///////////////////////////////////////////////
	DoublyLinkedList<int> list;
	list.Push(32);
	list.Push(325);
	list.Push(352);
	list.Push(3520);
	std::cout << "My list count " << list.Count() << "\n";


	std::cout << "========================================================================================\n";
	std::cout << "========================================================================================\n";
	std::cout << "========================================================================================\n";

	list.Debug_All_Nodes();


	std::cout << "========================================================================================\n";
	std::cout << "============================test operator[] to retrived data ===========================\n";
	std::cout << "========================================================================================\n";


	//////////////////////////////////////////////////
	// test operator[] to retrived data 
	//////////////////////////////////////////////////
	std::cout << "Node at idx 0 is " << list[0] << "\n";
	std::cout << "Node at idx 1 is " << list[1] << "\n";
	std::cout << "Node at idx 2 is " << list[2] << "\n";


	std::cout << "========================================================================================\n";
	std::cout << "==================================================Using Pop_At==========================\n";
	std::cout << "========================================================================================\n";

	////////////////////////////////////////////////////
	// Pop_At 
	////////////////////////////////////////////////////
	std::cout << "Old element at idx 0: " << list[0] << "\n";
	std::cout << "========================================================================================\n";
	//list.Debug_All_Nodes_Wc_Links();
	std::cout << "========================================================================================\n";
	list.Pop_At(2);
	std::cout << "New element at idx 0 after popping previous: " << list[0] << "\n";
	list.Debug_All_Nodes();
}