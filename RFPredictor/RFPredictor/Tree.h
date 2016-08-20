#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "ISplitter.h"
#include "IPredictor.h"

class Tree
{

public:
	Tree();
	Tree(ISplitter *splitter, IPredictor *predictor);
	~Tree();

	void ConstructTree(DataSet *dataSet, Node* parentNode,bool isLeftChild);
	Instance* Predict(Instance *inst, int &depth);
	void setTime(float time);
	float getTime();

private:
	Node *rootNode;

	ISplitter *splitter;
	IPredictor *predictor;

private:
	void Partition(float splitVal, int splitIndex, DataSet *currentData, DataSet *&leftData, DataSet *&rightData);
	float AvgSum(int featureToSum, DataSet *dataSet);
	void SetAsChild(Node* &currentNode,Node *parrentNode ,bool isLeftChild);
	bool checkIfLeaf(DataSet* currentDataSet, Node *currentNode, Node *parrentNode);
	Instance* SumAwnser(DataSet* currentDataSet);

	int depth;
	float creationTime;
};

#endif
