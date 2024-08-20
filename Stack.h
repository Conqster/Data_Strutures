/* Implementing a stack data structure using array and linked list
* 
* Using array
* data is stored contagionsly in memory (advantage)
* extra memory overhead, data does not have to point to next data (advantage)
* memory is preallocated, can not stored more than preallocated data without have to resize (Disadvantage)
* if preallocated memory is more than required its a waste of unused memory (Disadvantage) 
* 
* Using Linked list
* memory is not preallocated, more dynamic (advantage) 
* memory overhead, an extra variable pointer to track next data is required (disadvantage) 
* data stored is not contagious
*/

#pragma once

template<typename T>
class Stack
{
	T* arr;

	int count;
	int max;

public:
	Stack(int size)
	{
		arr = new T[size];
		count = 0;
		max = size;
	}

	~Stack()
	{
		if (count)
			delete[] arr;
	}

	void Push(T key)
	{

		if(count >= max)
		{
			std::cout << "Stack is full !!!!!!!!!!\n";
			return; 
		}

		arr[count++] = key;
	}

	void Pop()
	{
		if (count == 0)
		{
			std::cout << "Stack is empty!!!!!!!!!!!!!!!!!\n";
			return;
		}
		

		count--;
	}


	T Top()
	{
		if (count == 0)
		{
			throw std::out_of_range("Stack is empty!!!!!!!!!!!!!!!!!!!!!!!!!!!");

		}

		return arr[count - 1];
	}


	bool IsEmpty()
	{
		return count == 0;
	}


	/////////////////////////////////////////////////////////
	// DEBUGGER'S
	/////////////////////////////////////////////////////////

	void Debug_All_Keys()
	{

		//In the hope that template T supports operator << for printing
		//using a for loop, as a while loop might cause an endless loop
		for (int i = 0; i < count; i++)
			std::cout << "Key in Stack: " << arr[i] << std::endl;
	}

};


template<typename T>
class LinkStack
{
	LinkedList<T> list;

public:
	LinkStack()
	{
		std::cout << "Linked list stack created !!!!!!!!!!!!!!!\n";
	}


	void Push(T key)
	{
		//A stack c, b, a
		// to add d to become d , c, b, a, 
		//similar to push_front of a list 

		list.Push_Front(key);
	}

	T Top()
	{
		return list.Top_Front();
	}

	T Pop()
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





void SampleLinkStack()
{

	LinkStack<int> linkStack;

	std::cout << "Linked stack is empty : " << linkStack.Empty() << "\n";

	linkStack.Push(6);
	linkStack.Push(3);
	linkStack.Push(30);
	linkStack.Push(13);

	linkStack.Debug_All_Keys();
	std::cout << "Linked stack is empty : " << linkStack.Empty() << "\n";

	std::cout << "Get the top/last in element in the stack: " << linkStack.Top() << "\n";
	linkStack.Debug_All_Keys();

	std::cout << "Get & Pop the top/last in element in the stack: " << linkStack.Pop() << "\n";
	linkStack.Debug_All_Keys();
	

	std::cout << "Get & Pop the top/last in element in the stack: " << linkStack.Pop() << "\n";
	linkStack.Debug_All_Keys();
}



void SampleStack()
{
	std::cout << "Hello stack!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";


	Stack<int> stack(5);

	std::cout << "Is my stack empty: " << stack.IsEmpty() << "\n";

	stack.Push(2);
	stack.Push(6);
	stack.Push(1);
	stack.Push(10);
	stack.Push(14);
	stack.Push(11);
	stack.Push(31);
	std::cout << "Is my stack empty: " << stack.IsEmpty() << "\n";
	stack.Debug_All_Keys();

	stack.Pop();
	std::cout << "key at the top is: " << stack.Top() <<"\n";
	stack.Debug_All_Keys();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();

}