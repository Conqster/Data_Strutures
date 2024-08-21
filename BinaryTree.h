#pragma once


template<typename T>
struct Node
{
	T key;  ///probably a varible to check if the node meet citerias
	Node* left = nullptr;
	Node* right = nullptr;


	Node() : key(0), left(nullptr), right(nullptr)
	{
		std::cout << "In Action !!!!!!!!!\n";
	}

	Node(T _key)
		: key(_key), left(nullptr), right(nullptr) {}
};


template<typename T>
class BinaryTree
{
	Node<T>* root = nullptr;

public:
	BinaryTree()
	{
		std::cout << "binary tree initialized !!!!!!!!!!!!!!!!!!!!!!!!\n";
	}

	Node<T>* GetRoot() { return root; }


	void Add(T key)
	{
		Node<T>* new_node = new Node<T>(key);

		if (!root)
		{
			root = new_node;
			return;
		}

		Node<T>* current = root;
		Node<T>* prev = nullptr;

		while (current)
		{
			prev = current;   //for tracking
			if (new_node->key < current->key)
				current = current->left;
			else if (new_node->key > current->key)
				current = current->right;
		}


		if (prev != current)
			if (new_node->key < prev->key)
				prev->left = new_node;
			else if (new_node->key > prev->key)
				prev->right = new_node;

		current = new_node;
	}


	/////////////////////////////////////////////////////////
	// IN-ORDER, will sort the data in order no matter
	// how the data is add/inserted into the tree unlike Pre Order
	// after a child is validated/checked, node is validated before check other childrens
	/////////////////////////////////////////////////////////
	void InOrderTraversal(Node<T>* node)
	{
		if (!node)
			return;

		InOrderTraversal(node->left);
		std::cout << node->key << "\n";
		InOrderTraversal(node->right);
	}


	/////////////////////////////////////////////////////////
	// PRE-ORDER, relies on how the data is add/inserted into the tree 
	// unlike In Order
	// unlike Post, node is validate on traversal even before checking children
	/////////////////////////////////////////////////////////
	void PreOrderTraversal(Node<T>* node)
	{
		if (!node)
			return;

		std::cout << node->key << "\n";
		PreOrderTraversal(node->left);
		PreOrderTraversal(node->right);
	}

	/////////////////////////////////////////////////////////
	// POST-ORDER: almost as similar to pre-order 
	// but for a node to be vaildated as traversed both/all children need to have been vaildated or tranversed 
	/////////////////////////////////////////////////////////
	void PostOrderTraversal(Node<T>* node)
	{
		if (!node)
			return;

		PostOrderTraversal(node->left);
		PostOrderTraversal(node->right);
		std::cout << node->key << "\n";
	}


};






void SampleTree()
{
	std::cout << "Hello Tree !!!!!!\n ";


	BinaryTree<int> myTree;

	myTree.Add(12);
	myTree.Add(3);
	myTree.Add(6);
	myTree.Add(1);
	myTree.Add(19);
	myTree.Add(22);
	myTree.Add(14);
	myTree.Add(23);
	myTree.Add(20);


	std::cout << "======================================In-Order Tranversal=============================================\n";
	myTree.InOrderTraversal(myTree.GetRoot());
	std::cout << "======================================Pre-Order Tranversal=============================================\n";
	myTree.PreOrderTraversal(myTree.GetRoot());
	std::cout << "======================================Post-Order Tranversal=============================================\n";
	myTree.PostOrderTraversal(myTree.GetRoot());


}