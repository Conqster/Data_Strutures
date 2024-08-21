#pragma once




template<typename T>
class Queue
{
	LinkedList<T> list;

public:
	Queue()
	{
		std::cout << "Queue created !!!!!!!!!!!!!!!\n";
	}

	inline unsigned int Count() const { return list.Count(); }


	void Enqueue(T key)
	{
		//A queue a, b, c
		// to add d to become  a, b, c, d
		//similar to push_front of a list 

		list.Push_Back(key);
	}

	T Dequeue()
	{
		//not really efficient but fix later
		T key = list.Top_Front();

		list.Pop_Front();
		return key;
	}


	bool Empty()
	{
		return list.Count() == 0;
	}


	/////////////////////////////////////////////////////////
	// DEBUGGER'S
	/////////////////////////////////////////////////////////

	void Debug_All_Keys()
	{
		list.Debug_All_Nodes();
	}
};





void SampleQueue()
{
	Queue<std::string> queue;

	std::cout << "queue count: " << queue.Count() << "\n";
	

	queue.Enqueue("Jack");
	queue.Enqueue("Paul");
	queue.Enqueue("Saul");
	queue.Enqueue("Jake");
	queue.Enqueue("Luke");

	std::cout << "========================================Loop All queue===========================================\n";

	queue.Debug_All_Keys();

	std::cout << "====Dequeuing / retriving from queue!!!!!\n";

	std::cout << "Dequeuing ..... " << queue.Dequeue() << "\n";
	std::cout << "Is Empty : " << queue.Empty() << "\n";
	std::cout << "Dequeuing ..... " << queue.Dequeue() << "\n";
	std::cout << "Is Empty : " << queue.Empty() << "\n";
	std::cout << "Dequeuing ..... " << queue.Dequeue() << "\n";
	std::cout << "Is Empty : " << queue.Empty() << "\n";
	std::cout << "Dequeuing ..... " << queue.Dequeue() << "\n";
	std::cout << "Is Empty : " << queue.Empty() << "\n";
	std::cout << "Dequeuing ..... " << queue.Dequeue() << "\n";
	std::cout << "Is Empty : " << queue.Empty() << "\n";

	std::cout << "========================================Loop All queue===========================================\n";

	queue.Debug_All_Keys();

}