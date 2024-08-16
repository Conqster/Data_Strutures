#include <iostream>

#include "LinkedList.h"



int main()
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
	list.Push("Hill");

	list.Push("Jack");
	std::cout << "My list count " << list.Count() << "\n";
	list.Push("Nick");
	std::cout << "My list count " << list.Count() << "\n";
	list.Push("Jill");
	std::cout << "My list count " << list.Count() << "\n";

	std::cout << "First/Head node is " << list.NodeHead()->data << "\n";

	std::cout << "Node at idx 0 is " << list[0] << "\n";
	std::cout << "Node at idx 1 is " << list[1] << "\n";
	std::cout << "Node at idx 2 is " << list[2] << "\n";
	std::cout << "Node at idx 3 is " << list[3] << "\n";

	std::cout << "========================================================================================\n";
	std::cout << "========================================================================================\n";
	std::cout << "========================================================================================\n";
	//list.Pop_At(0);
	std::cout << "My list count " << list.Count() << "\n";
	list.Insert_At("Frank", 2);
	std::cout << "My list count " << list.Count() << "\n";
	std::cout << "First/Head node is " << list.NodeHead()->data << "\n";
	std::cout << "Node at idx 0 is " << list[0] << "\n";
	std::cout << "Node at idx 1 is " << list[1] << "\n";
	std::cout << "Node at idx 2 is " << list[2] << "\n";
	std::cout << "Node at idx 3 is " << list[3] << "\n";
	std::cout << "Node at idx 4 is " << list[4] << "\n";


	std::cout << "========================================================================================\n";
	std::cout << "========================================================================================\n";
	std::cout << "========================================================================================\n";

	list.Debug_All_Nodes();

	std::cin.get();
}