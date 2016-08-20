#include "SORandomForests.h"
#include "RandomSingleMSE.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>


SORandomForests::SORandomForests()
{
	modelTime = 0;
	treeTime = 0;
	trees = NULL;
	trees = new std::vector<Tree*>;
}


SORandomForests::~SORandomForests()
{
	if (trees)

	if (trees)
	{
		delete trees;
	}

}


void SORandomForests::Train(DataSet* input, int nrOfTrees)
{
	RandomSingleMSE *randomSingleMSE;
	randomSingleMSE = new RandomSingleMSE(input->nrOfInputs - 1);
	
	if (trees != NULL)
	{
		delete trees;
		trees = new std::vector<Tree*>;
	}
	else
	{
		trees = new std::vector<Tree*>;
	}
		

	for (int i = 0; i < nrOfTrees; i++)
	{
		DataSet * baggedTrainingSet = ConstructBaggedSet(input);
		Tree *tree = new Tree(randomSingleMSE,NULL);
		//start timing
		auto begin = std::chrono::high_resolution_clock::now();
		tree->ConstructTree(baggedTrainingSet, NULL, false);
		//end timing
		auto end = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
		tree->setTime(time);
		trees->push_back(tree);
	}
	//creationTime = sumOfAllTree creation times
	this->modelTime = 0;
	for (int i = 0; i < (int)trees->size(); i++)
	{
		this->modelTime += trees->at(i)->getTime();
	}
	this->treeTime = modelTime / trees->size();
	
	delete randomSingleMSE;
}

Instance* SORandomForests::Predict(Instance* instToBePredicted)
{
	//for every tree in the forest, predict output from input

	Instance *realPrediction = new Instance();
	realPrediction->input = instToBePredicted->input;
	realPrediction->output = new float[1];
	realPrediction->output[0] = 0;
	int avgDepth = 0;
	
	for (int i = 0; i < (int)trees->size(); i++)
	{
		Instance* predictedInstance = trees->at(i)->Predict(instToBePredicted, avgDepth);

		realPrediction->output[0] += predictedInstance->output[0];
	}
	avgDepth /= (int)trees->size();
	//std::cout << "avgDepth" << avgDepth << std::endl;
	realPrediction->output[0] /= trees->size();


	return realPrediction;
}

DataSet* SORandomForests::ConstructBaggedSet(DataSet* trainingSet)
{
	int x = 0;
	srand((unsigned int)time(NULL));

	DataSet *baggedTrainingSet = new DataSet(trainingSet->nrOfInstances,trainingSet->nrOfInputs,trainingSet->nrOfOutputs);

	for (int j = 0; j < trainingSet->nrOfInstances; j++)
	{
		x = rand() % trainingSet->nrOfInstances;
		baggedTrainingSet->data[j] = (trainingSet->data[x]);
	}

	return baggedTrainingSet;
}

float SORandomForests::getModelTime()
{
	return this->modelTime;
}
float SORandomForests::getTreeTime()
{
	return this->treeTime;
}