#include "Tree.h"

#include <iostream>

Tree::Tree()
{
	rootNode = NULL;
}

Tree::~Tree()
{
	if (rootNode)
	{
		delete rootNode;
		rootNode = NULL;
	}
}

Tree::Tree(ISplitter *splitter, IPredictor *predictor)
{
	this->splitter = splitter;
	this->predictor = predictor;
	rootNode = NULL;
	depth = 0;
	creationTime = 0;
}

void Tree::SetAsChild(Node* &currentNode,Node *parrentNode ,bool isLeftChild)
{
	if (rootNode == NULL)
	{
		currentNode = new Node();
		rootNode = currentNode;
	}
	else
	{
		currentNode = new Node(parrentNode);
		if (isLeftChild)
		{
			parrentNode->SetLeftChild(currentNode);
		}
		else
		{
			parrentNode->SetRightChild(currentNode);
		}
	}
}

bool Tree::checkIfLeaf(DataSet* currentDataSet, Node *currentNode, Node *parrentNode)
{
	if (currentDataSet->nrOfInstances <= 4)
	{
		//make into leaf
		if (currentDataSet->nrOfInstances == 0)
		{
			currentNode->SetAsLeaf(parrentNode->GetPrediction());
		}
		else
		{
			//sum awnser of currentDataSet
			currentNode->SetAsLeaf(SumAwnser(currentDataSet));
		}
		
		return true;
	}
	else
	{
		//sum up awnser for this node but do not make it a leaf
		currentNode->SetPrelimPrediction(SumAwnser(currentDataSet));
	}

	return false;
}

void Tree::ConstructTree(DataSet *currentDataSet, Node *parrentNode, bool isLeftChild)
{
	DataSet *leftDataSet;
	DataSet *rightDataSet;
	Node *currentNode;
	

	SetAsChild(currentNode,parrentNode,isLeftChild);
	
	if(checkIfLeaf(currentDataSet,currentNode,parrentNode))
	{
		return;
	}

	{
		SplitInfo *splitInfo;
		splitInfo = &splitter->ConsiderSplit(currentDataSet);
		if (splitInfo->splitIndex == -1)//means that no good split was found and so a leaf shall be constructed
		{
			currentNode->SetAsLeaf(SumAwnser(currentDataSet));
			return;
		}
		Partition(splitInfo->splitVal, splitInfo->splitIndex, currentDataSet, leftDataSet, rightDataSet);
		currentNode->SetTestVal(splitInfo->splitVal, splitInfo->splitIndex);
	}
	//delete currentDataset to clean up
	delete currentDataSet;
	ConstructTree(leftDataSet, currentNode, true); //grow the tree further with the now split data and finished node
	ConstructTree(rightDataSet, currentNode, false); //grow the tree further with the now split data and finished node
}

float Tree::AvgSum(int featureToSum, DataSet *dataSet)
{
	float avgSum = 0;

	for (int i = 0; i < dataSet->nrOfInstances; i++)
	{
		avgSum += dataSet->data[i]->output[featureToSum];
	}

	avgSum /= dataSet->nrOfInstances;

	return avgSum;
}

Instance* Tree::SumAwnser(DataSet* currentDataSet)
{
	Instance* predInstance = new Instance();

	float* predOutputs = new float[currentDataSet->nrOfOutputs];

	for (int i = 0; i < currentDataSet->nrOfOutputs; i++)
	{
		predOutputs[i] = AvgSum(i, currentDataSet);
	}
	predInstance->output = predOutputs;

	return predInstance;
}

void Tree::Partition(float splitVal, int splitIndex, DataSet *currentData, DataSet *&leftData, DataSet *&rightData)
{
	std::vector<Instance*> tempLeft;
	std::vector<Instance*> tempRight;

	for (int i = 0; i < currentData->nrOfInstances; i++)
	{
		Instance *inst = currentData->data[i];

		if (inst->input[splitIndex] >= splitVal) //go right
		{
			tempRight.push_back(inst);
		}
		else //go left
		{
			tempLeft.push_back(inst);
		}
	}

	rightData = new DataSet(tempRight.size(), currentData->nrOfInputs, currentData->nrOfOutputs);
	for (int i = 0; i < (int)tempRight.size(); i++)
	{
		rightData->data[i] = tempRight[i];
	}

	leftData = new DataSet(tempLeft.size(), currentData->nrOfInputs, currentData->nrOfOutputs);
	for (int i = 0; i < (int)tempLeft.size(); i++)
	{
		leftData->data[i] = tempLeft[i];
	}
}

Instance* Tree::Predict(Instance *inst, int &depth)
{
	return rootNode->Traverse(inst, depth);
}

void Tree::setTime(float time)
{
	this->creationTime = time;
}

float Tree::getTime()
{
	return creationTime;
}

