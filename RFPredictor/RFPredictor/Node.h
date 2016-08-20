#ifndef NODE_H
#define NODE_H

#include "Utils.h"

class Node
{
public:
	Node();
	Node(Node *parent);
	~Node();

	//Sets
	void SetLeftChild(Node *child);
	void SetRightChild(Node *child);
	void SetTestVal(float testVal, int valIndex);
	void SetAsLeaf(Instance *predictedInstance);
	void SetPrelimPrediction(Instance *predictedInstance);

	//Gets
	Node* GetParent();
	Node* GetLeftChild();
	Node* GetRightChild();
	float GetTestVal();
	int GetValIndex();
	Instance* GetPrediction();
	
	//traverse the nodes
	Instance* Traverse(Instance *inst, int &depth);

private:
	Node *parent;
	float testVal;
	int valIndex;
	
	Node *leftChild;
	Node *rightChild;

	bool isLeaf;
	Instance *predictedInstance;

};

#endif
