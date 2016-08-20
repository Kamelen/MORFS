#include "Node.h"
#include <iostream>

Node::Node()
{
	this->parent = NULL;
	this->testVal = 0;

	this->valIndex = 0;
	this->isLeaf = false;
	

	this->leftChild = NULL;
	this->rightChild = NULL;

}

Node::Node(Node *parent)
{
	this->parent = parent;
	this->testVal = 0;
	this->predictedInstance = NULL;
	
	this->valIndex = 0;
	this->isLeaf = false;

	this->leftChild = NULL;
	this->rightChild = NULL;
}


Node::~Node()
{
	if (this->predictedInstance)
	{
		delete this->predictedInstance;
	}
	

	if (this->leftChild)
	{
		delete this->leftChild;
		this->leftChild = NULL;
	}

	if (this->rightChild)
	{
		delete this->rightChild;
		this->rightChild = NULL;
	}
}

void Node::SetLeftChild(Node *child)
{
	this->leftChild = child;
}

void Node::SetRightChild(Node *child)
{
	this->rightChild = child;
}

void Node::SetTestVal(float testVal, int valIndex)
{
	this->testVal = testVal;
	this->valIndex = valIndex;
}

void Node::SetAsLeaf(Instance *predictedInstance)
{
	isLeaf = true;
	this->predictedInstance = predictedInstance;
}
void Node::SetPrelimPrediction(Instance *predictedInstance)
{
	this->predictedInstance = predictedInstance;
}

Instance* Node::Traverse(Instance *instance, int &depth)
{
	depth++;
	if (isLeaf)
	{
		return predictedInstance;
	}

	if (instance->input[valIndex] >= testVal)
	{
		return rightChild->Traverse(instance, depth);
	}
	else
	{
		return leftChild->Traverse(instance, depth);
	}
}

Node* Node::GetParent()
{
	return parent;
}

Node* Node::GetLeftChild()
{
	return leftChild;
}

Node* Node::GetRightChild()
{
	return rightChild;
}

float Node::GetTestVal()
{
	return testVal;
}

int Node::GetValIndex()
{
	return valIndex;
}
Instance* Node::GetPrediction()
{
	return this->predictedInstance;
}