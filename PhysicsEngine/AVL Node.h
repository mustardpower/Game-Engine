#ifndef _AVLNODE_H_
#define _AVLNODE_H_

#define NULL 0

template <class ComparableElement>
class AVLNode
{
private:
	ComparableElement data;
	AVLNode<ComparableElement>* left;
	AVLNode<ComparableElement>* right;
public:
	ComparableElement getData();
	AVLNode<ComparableElement>* add(AVLNode<ComparableElement>* node,ComparableElement data);
	AVLNode<ComparableElement>* getLeft();
	AVLNode<ComparableElement>* getRight();
	AVLNode<ComparableElement>* leftRotation();
	AVLNode<ComparableElement>* rightRotation();
	AVLNode<ComparableElement>* doubleLeftRotation();
	AVLNode<ComparableElement>* doubleRightRotation();
	void setLeft(AVLNode<ComparableElement>* node);
	void setRight(AVLNode<ComparableElement>* node);
	int balanceFactor();
	AVLNode<ComparableElement>* balance();
	AVLNode<ComparableElement>(ComparableElement _data) { data = _data; left = NULL; right = NULL; }
	int maxDepth();
};

template <class ComparableElement>
ComparableElement AVLNode<ComparableElement>::getData()
{
	return data;
}
template <class ComparableElement>
int AVLNode<ComparableElement>::maxDepth()
{
	int lDepth = 0;
	int rDepth = 0;

	if(this == NULL)
	{
		return 0;
	}

	if(left != NULL)
	{
		lDepth = left->maxDepth();
	}
	if(right != NULL)
	{
		rDepth = right->maxDepth();
	}

	if(lDepth > rDepth) { return lDepth+1; }
	else return rDepth+1;
}

template <class ComparableElement>
AVLNode<ComparableElement>* AVLNode<ComparableElement>::getLeft()
{
	return left;
}
template <class ComparableElement>
AVLNode<ComparableElement>* AVLNode<ComparableElement>::getRight()
{
	return right;
}
template <class ComparableElement>
void AVLNode<ComparableElement>::setLeft(AVLNode<ComparableElement>* node)
{
	left = node;
}
template <class ComparableElement>
void AVLNode<ComparableElement>::setRight(AVLNode<ComparableElement>* node)
{
	right = node;
}

template <class ComparableElement>
AVLNode<ComparableElement>* AVLNode<ComparableElement>::add(AVLNode<ComparableElement>* root,ComparableElement newComparableElement)
{
	if (data == NULL)
	{
		data = child->getData();
	}
	else
	{
		if(child->getData() < data)
		{
			if(left == nullptr)
			{
				left = child;
			}
			else
			{
				left->add(child);
			}
		}
		else if(child->getData() > data)
		{
			if(right == nullptr)
			{
				right = child;
			}
			else
			{
				right->add(child);
			}
		}
	}

	return balance();
}

template <class ComparableElement>
AVLNode<ComparableElement>* AVLNode<ComparableElement>::leftRotation()
{
	cout<<"Perform left rotation"<<endl;
	AVLNode<ComparableElement>* temp;
    temp = right;
	setRight(right->getLeft());
	temp->setLeft(this);
	
    return temp;
}
template <class ComparableElement>
AVLNode<ComparableElement>* AVLNode<ComparableElement>::rightRotation()
{
	cout<<"Perform right rotation"<<endl;
	AVLNode<ComparableElement>* temp;
    temp = left;
	setLeft(left->getRight());
	temp->setRight(this);

	return temp;
}
template <class ComparableElement>
AVLNode<ComparableElement>* AVLNode<ComparableElement>::doubleLeftRotation()
{
	cout<<"Performed double left rotation"<<endl;
	right = right->rightRotation ();
    return leftRotation ();
}
template <class ComparableElement>
AVLNode<ComparableElement>* AVLNode<ComparableElement>::doubleRightRotation()
{
	cout<<"Performed double right rotation"<<endl;
	left = left->leftRotation ();
    return rightRotation ();
}

template <class ComparableElement>
int AVLNode<ComparableElement>::balanceFactor()
{
	if(this != NULL)
	{
		return left->maxDepth() - right->maxDepth();
	}
	else
	{
		return 0;
	}
}

template <class ComparableElement>
AVLNode<ComparableElement>* AVLNode<ComparableElement>::balance()
{
	AVLNode<ComparableElement>* currentNode = this;
	int diff = balanceFactor();

	if(diff < -1) // right child is longer than left
	{
		if(right->balanceFactor()>0)
		{
			cout<<"do a double left rotation"<<endl;
			currentNode = doubleLeftRotation();
		}
		else
		{
			cout<<"do a left - left rotation"<<endl; // if the right child is balanced
			currentNode = leftRotation();	
		}

	}
	else if(diff > 1) // left child is longer than the right
	{
		if(right->balanceFactor()>0)		// if the left child node is unbalanced
		{
			cout<<"do a right - left rotation"<<endl;
			currentNode = doubleRightRotation();
		}
		else										// if the left child node is balanced
		{
			cout<<"do a right - right rotation"<<endl;
			currentNode = rightRotation();
		}
	}

	return currentNode;
}

#endif