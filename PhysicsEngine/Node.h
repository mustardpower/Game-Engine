#ifndef _NODE_H_
#define _NODE_H_

#define NULL 0

template <class ComparableElement>
class Node
{
protected:
	ComparableElement data;
	Node<ComparableElement>* left;
	Node<ComparableElement>* right;
public:
	ComparableElement getData();
	Node<ComparableElement>* getLeft();
	Node<ComparableElement>* getRight();
	ComparableElement find(ComparableElement data);
	virtual void add(ComparableElement newData);
	virtual void remove(Node<ComparableElement>* child);
	int maxDepth();

	Node() { left = NULL; right = NULL; }
	Node(ComparableElement _data) { data = _data; left = NULL; right = NULL; }
};
template <class ComparableElement> ComparableElement Node<ComparableElement>::getData()
{
	return data;
}
template <class ComparableElement> void Node<ComparableElement>::add(ComparableElement newData)
{
	if (data == NULL)
	{
		data = newData;
	}
	else
	{
		if(newData < data)
		{
			if(left == nullptr)
			{
				left = new Node<ComparableElement>(newData);
			}
			else
			{
				left->add(newData);
			}
		}
		else if(newData > data)
		{
			if(right == nullptr)
			{
				right = new Node<ComparableElement>(newData);
			}
			else
			{
				right->add(newData);
			}
		}
	}
}
template <class ComparableElement> void Node<ComparableElement>::remove(Node<ComparableElement>* child)
{
}
template <class ComparableElement>
int Node<ComparableElement>::maxDepth()
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

#endif