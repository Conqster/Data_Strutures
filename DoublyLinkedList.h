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


	Node* GetNode_At(int idx)
	{
		Node* current = head;

		if (idx < count / 2)
		{
			std::cout << "Forward traversing......\n";

			for (int i = 0; i < idx; i++)
				current = current->next;

			return current;
		}
		else
		{
			std::cout << "Backward traversing......\n";

			current = tail;

			for (int i = count - 1; i > idx; i--)
				current = current->prev;

			return current;
		}
	}

public:
	DoublyLinkedList()
	{
		std::cout << "Doubly Linked list created with count " << count << "\n";
	}

	~DoublyLinkedList()
	{
		std::cout << "================================Closing Closing================================\n ";
		Debug_All_Nodes();
		if (head)
		{
			Node* current = head;

			//for safety
			head = nullptr;
			tail = nullptr;

			int interation = 0;

			while (current)
			{
				//Self deletion 
				if (current->next)
				{
					//set prev ptr to self = nullptr 
					if(current->prev)
						current->prev->next = nullptr;

					//move forward
					current = current->next;

					//the deletion, as i've advanced then set to nullptr
					delete current->prev;
					current->prev = nullptr;
				}
				else
				{
					//if next does not exist, self destruct
					delete current;
					current = nullptr;
				}

				interation++;
			}

			std::cout << "Closing Loop interations : " << interation << "\n";

			std::cout << "================================Closing Finished deletion================================\n ";
			Debug_All_Nodes();

		}
	}

	inline Node* DebugHeadNode() const { return head; }
	inline Node* DebugTailNode() const { return tail; }
	inline unsigned int Count() const { return count; }

	void Push(T data)
	{
		Node* new_node = new Node(data);

		if (!head)
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
		if (!head || idx > count - 1)
		{
			std::cout << "out of bounds !!!!!!!!!\n";
		}

		return GetNode_At(idx)->data;
	}


	void Pop_At(int idx)
	{
		if (!head || idx > count - 1)
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
		Node* current = GetNode_At(idx);

		//Np N Nn ===== Goal to remove N
		// N - current node, Np - its previous, Nn - its next
		//Np's new next (current->prev->next) = Nn
		//Nn's new prev (current->next->prev) = Np

		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
		count--;
	}


	void Insert_At(int idx, T data)
	{
		if (idx > count)
		{
			std::cout << "out of bounds !!!!!!!!!\n";
			return;
		}


		Node* new_node = new Node(data);
		//New head is required, as inserting to idx 0 
		//the old head is fighting for its place and would shift new node back which make it look it tail
		if (idx == 0)
		{
			new_node->prev = tail;
			new_node->next = head;

			tail->next = new_node;
			head->prev = new_node;

			head = new_node;
			count++;
			return;
		}
		else if (idx == count)  //means requiring to add to the end of the list, the Push function will handle insertion
		{
			Push(data);
			return;
		}

		
		Node* current = GetNode_At(idx);

		std::cout << "This current node is " << current->data << "\n";


		current->prev->next = new_node;

		new_node->prev = current->prev;
		new_node->next = current;

		current->prev = new_node;
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


	void Pop()
	{
		if (count == 0)
		{
			std::cout << "List is empty.........\n";
			return;
		}

		Node* temp = tail->prev; //secons to the last element become tail;
		//the next element for the "Previous element to the tail" is now the head
		temp->next = head;
		head->prev = temp;    //heads prev is now second to the last element 

		delete tail;
		tail = temp; //second to the last became tail

		count--;
	}


	void Remove(T data)
	{

		Node* current = head;
		Node* found = nullptr;

		if (!current)
			return;

		if (current->data == data)
		{
			head = head->next;
			tail->next = head;
			head->prev = tail;
			count--;
			return;
		}

		int iterations = 0;
		for (int i = 0; i < count; i++)
		{
			iterations++;
			if (current->data == data)
			{
				found = current;
				break;
			}
			current = current->next;
		}

		if (!found)
			return;

		std::cout << "found after " << iterations << " iterations!!!!!!\n";

		found->prev->next = found->next;
		found->next->prev = found->prev;
		delete found;
		count--;
	}

	void Remove_At(int idx)
	{
		Pop_At(idx);
	}


	void Reverse()
	{

	}


	/////////////////////////////////////////////////////////
	// DEBUGGER'S
	/////////////////////////////////////////////////////////

	void Debug_All_Nodes()
	{
		DebugLoop_AllNode(1);
	}

	void DebugLoop_AllNode(int times = 2)
	{
		if (!head)
			return;

		Node* current = head;

		//In the hope that template T supports operator << for printing
		//using a for loop, as a while loop might cause an endless loop
		for (int i = 0; i < count * times; i++)
		{
			std::cout << "Element/Node " << i % count << ": " << current->data << "\n";
			current = current->next;
		}
	}

	void Debug_All_Nodes_Wc_Links()
	{
		if (!head)
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
	list.Push(5);
	list.Push(4);
	list.Push(2);
	list.Push(6);
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
	std::cout << "Old element at idx 1: " << list[1] << "\n";
	//list.Pop_At(1);
	std::cout << "New element at idx 1 after popping previous: " << list[1] << "\n";
	list.Debug_All_Nodes();

	std::cout << "========================================================================================\n";
	std::cout << "==================================using Insert at========================================\n";
	std::cout << "========================================================================================\n";

	////////////////////////////////////////////////////
	// Insert_At
	////////////////////////////////////////////////////
	list.Insert_At(4, 10);
	std::cout << "About to debug all nodes with links\n";
	list.Debug_All_Nodes_Wc_Links();


	std::cout << "========================================================================================\n";
	std::cout << "New List......\n";
	std::cout << "========================================================================================\n";
	list.Debug_All_Nodes();



	////////////////////////////////////////////////////
	// Find_idx
	////////////////////////////////////////////////////

	std::cout << "========================================================================================\n";
	std::cout << "==================================using Find_idx=========================================\n";
	std::cout << "========================================================================================\n";

	std::cout << "What is the idx of 10:  " << list.Find_idx(10) << "\n";
	std::cout << "What is the idx of 4:  " << list.Find_idx(4) << "\n";
	std::cout << "What is the idx of 6:  " << list.Find_idx(6) << "\n";


	////////////////////////////////////////////////////
	// Pop
	////////////////////////////////////////////////////
	std::cout << "========================================================================================\n";
	std::cout << "==================================using Pop==============================================\n";
	std::cout << "========================================================================================\n";
	//std::cout << "Debuging all nodes\n";
	//list.Debug_All_Nodes();

	//list.Pop();
	//std::cout << "Debuging all nodes\n";
	//list.Debug_All_Nodes();

	//list.Pop();
	//std::cout << "Debuging all nodes\n";
	//list.Debug_All_Nodes();

	//list.Pop();
	//std::cout << "Debuging all nodes\n";
	//list.Debug_All_Nodes();



	////////////////////////////////////////////////////
	// Remove
	////////////////////////////////////////////////////
	std::cout << "========================================================================================\n";
	std::cout << "==================================using Remove===========================================\n";
	std::cout << "========================================================================================\n";

	std::cout << "Debuging all nodes\n";
	//list.Debug_All_Nodes_Wc_Links();
	list.Debug_All_Nodes();
	list.Remove(5);
	std::cout << "Debuging all nodes after removing 2 \n";
	//list.Debug_All_Nodes_Wc_Links();
	list.Debug_All_Nodes();


	std::cout << "Debuging all nodes 3 interations\n";
	list.DebugLoop_AllNode(3);
	list.Pop();
	list.Pop();
}