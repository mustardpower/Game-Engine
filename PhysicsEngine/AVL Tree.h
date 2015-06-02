#ifndef _AVLSEARCHTREE_H_
#define _AVLTREE_H_
#include "AVL Node.h"

#define NULL 0

template <class ComparableElement>
class AVLTree
{
public:
	AVLTree<ComparableElement>() { }
	AVLNode<ComparableElement>* add(AVLNode<ComparableElement>* root, ComparableElement data);
	int maxDepth(AVLNode<ComparableElement>* root);
	AVLNode<ComparableElement>* balance(AVLNode<ComparableElement>* node);
};

template <class ComparableElement>
AVLNode<ComparableElement>* AVLTree<ComparableElement>::add(AVLNode<ComparableElement>* root,ComparableElement data)
{

	if(root == nullptr)
	{
		root = new AVLNode<ComparableElement>(data);
		return root;
	}
	else
	{
		if(root->getData() > data)
		{
			root->setLeft(add(root->getLeft(),data));
			root = balance(root);
		}
		else if(root->getData() < data)
		{
			root->setRight(add(root->getRight(),data));
			root = balance(root);
		}
	}

	return root;
}

template<class ComparableElement>
AVLNode<ComparableElement>* AVLTree<ComparableElement>::balance(AVLNode<ComparableElement>* node)
{
	int bal_factor = node->balanceFactor();
    if (bal_factor < -1)
    {
		if (node->getLeft()->balanceFactor() > 0)
		{
			node = node->doubleLeftRotation();
		}
        else
		{
			node = node->leftRotation();
		}
    }
    else if (bal_factor > 1)
    {
		if (node->getRight()->balanceFactor() > 0)
		{
			node = node->doubleRightRotation();
		}
        else
		{
			node = node->rightRotation();
		}
    }
    return node;
}

template <class ComparableElement>
int AVLTree<ComparableElement>::maxDepth(AVLNode<ComparableElement>* root)
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