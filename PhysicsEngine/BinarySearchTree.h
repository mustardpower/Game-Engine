#ifndef _BINARYSEARCHTREE_H_
#define _BINARYSEARCHTREE_H_
#include "Node.h"

#define NULL 0

template<class ComparableElement>
class BinarySearchTree
{
protected:
	Node<ComparableElement>* root;	// pointer to the root node in the tree

public:
	void add(ComparableElement anElement);
	void remove(ComparableElement anElement);
	int maxDepth();
	BinarySearchTree<ComparableElement>() { root = NULL; }
};

template <class ComparableElement>
void BinarySearchTree<ComparableElement>::add(ComparableElement data)
{
	if(root == nullptr)
	{
		root = new Node<ComparableElement>(data);
	}
	else
	{
		root->add(data);
	}
}

template <class ComparableElement>
int BinarySearchTree<ComparableElement>::maxDepth()
{
	if(root == nullptr)
	{
		return 0;
	}
	else
	{
		return root->maxDepth();
	}
}



#endif