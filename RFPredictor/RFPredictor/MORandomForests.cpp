#include "MORandomForests.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "RandomMultiMSE.h"
#include "RandomMultiCVCL.h"

MORandomForests::MORandomForests()
{
	
}

MORandomForests::MORandomForests(ISplitter* splitter)
{
	this->splitter = splitter;
	modelTime = 0;
	treeTime = 0;
	this->trees = NULL;
}


MORandomForests::~MORandomForests()
{
	delete splitter;
	delete trees;
}


void MORandomForests::Train(DataSet* input, int nrOfTrees)
{

	if (trees != NULL)
	{
		delete trees;
		trees = new std::vector<Tree*>;
	}
	trees = new std::vector<Tree*>;

	this->nrOfOutputs = input->nrOfOutputs;
	for (int i = 0; i < nrOfTrees; i++)
	{
		DataSet * baggedTrainingSet = ConstructBaggedSet(input);
		Tree *tree = new Tree(this->splitter, NULL);
		auto begin = std::chrono::high_resolution_clock::now();
		tree->ConstructTree(baggedTrainingSet, NULL, false);
		auto end = std::chrono::high_resolution_clock::now(); 
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
		tree->setTime(time);
		trees->push_back(tree);
	}
	this->modelTime = 0;
	for (int i = 0; i < (int)trees->size(); i++)
	{
		this->modelTime += trees->at(i)->getTime();
	}
	this->treeTime = modelTime / trees->size();
}

Instance* MORandomForests::Predict(Instance* instToBePredicted)
{
	//for every tree in the forest, predict output from input

	Instance *realPrediction = new Instance();
	realPrediction->input = instToBePredicted->input;
	realPrediction->output = new float[this->nrOfOutputs];
	for (int i = 0; i < this->nrOfOutputs; i++)
	{
		realPrediction->output[i] = 0;
	}
	
	int avgDepth = 0;
	for (int i = 0; i < (int)trees->size(); i++)
	{
		Instance* predictedInstance = trees->at(i)->Predict(instToBePredicted, avgDepth);


		for (int j = 0; j < this->nrOfOutputs; j++)
		{
			realPrediction->output[j] += predictedInstance->output[j];
		}
		
	}
	avgDepth /= (int)trees->size();
	//std::cout << "avgDepth" << avgDepth << std::endl;

	for (int i = 0; i < this->nrOfOutputs; i++)
	{
		realPrediction->output[i] /= trees->size();
	}
	

	//sum up all the predictions to make a final prediction

	return realPrediction;
}

DataSet* MORandomForests::ConstructBaggedSet(DataSet* trainingSet)
{
	int x = 0;
	srand((unsigned int)time(NULL));

	DataSet *baggedTrainingSet = new DataSet(trainingSet->nrOfInstances, trainingSet->nrOfInputs, trainingSet->nrOfOutputs);

	for (int j = 0; j < trainingSet->nrOfInstances; j++)
	{
		x = rand() % trainingSet->nrOfInstances;
		baggedTrainingSet->data[j] = (trainingSet->data[x]);
	}

	return baggedTrainingSet;
}

float MORandomForests::getModelTime()
{
	return modelTime;
} 

float MORandomForests::getTreeTime()
{
	return treeTime;
}