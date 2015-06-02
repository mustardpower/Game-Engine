#include "Node.h"

template <class Object> Object Node<Object>::getData()
{
	return data;
}
template <class Object> void Node<Object>::add(Node<Object>* child)
{
	if (data == null)
	{
		data = child;
	}
	else
	{
		if(child->getData() < data)
		{
			left->add(child);
		}
		else if(child->getData() > data)
		{
			right->add(child);
		}
	}
}
template <class Object> void Node<Object>::remove(Node<Object>* child)
{
	if (data == null)
	{
		data = child;
	}
	else
	{
		if(child->getData() < data)
		{
			left->add(child);
		}
		else if(child->getData() > data)
		{
			right->add(child);
		}
	}
}