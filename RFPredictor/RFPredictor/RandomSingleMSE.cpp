#include "RandomSingleMSE.h"
#include <iostream>

#include <stdlib.h>
#include <time.h>


RandomSingleMSE::RandomSingleMSE()
{
	this->maxNrOfConsideredVariables = 5;
	this->maxNrOfVars = 5;
}

RandomSingleMSE::RandomSingleMSE(int maxNrOfVariables)
{
	this->maxNrOfConsideredVariables = sqrt(maxNrOfVariables);
	this->maxNrOfVars = maxNrOfVariables;
}

RandomSingleMSE::~RandomSingleMSE()
{

}

SplitInfo RandomSingleMSE::ConsiderSplit(DataSet *currentDataSet)
{
	//om programmet kommer hit så skall noden inte bli ett löv utan currentData ska splittas upp till två sets.
	//functionen är till för att hitta detta splitvärdet och splitindex så att trädet sedan kan göra splitten
	/*std::vector<Instance*> dataset;

	for (int i = 0; i < currentDataSet->nrOfInstances; i++)
	{
		dataset.push_back(currentDataSet->data[i]);
	}*/
	
	SplitInfo splitInfo;
	//srand((unsigned int)time(NULL));
	float bestSplittingVal = 0;
	float lowestMSE = 0;
	int bestSplittingIndex = -1;

	std::vector<int> featuresToConsider = GetRandomFeatures();

	for (int i = 0; i < (int)featuresToConsider.size(); i++)
	{
		if (i >= this->mTry && lowestMSE != 0)
		{
			splitInfo.splitIndex = bestSplittingIndex;
			splitInfo.splitVal = bestSplittingVal;
			if (lowestMSE != 0)
			{
				//std::cout << "lowestMSE: " << lowestMSE << std::endl;
			}
			return splitInfo; //valid splittingvalue found
		}
		int index = featuresToConsider[i];
		float splitVal = 0;
		DataSet *leftTest;
		DataSet *rightTest;


		for (int j = 0; j < currentDataSet->nrOfInstances; j++)
		{
			//j = currentDataSet->nrOfInstances;
			splitVal = currentDataSet->data[j]->input[index];
		
			
			Partition(splitVal, index,currentDataSet, leftTest, rightTest);

			if (leftTest->nrOfInstances == 0 || rightTest->nrOfInstances == 0)
			{
				//crappy split, do nothing
			}
			else
			{
				float avgMSE = 0;
				avgMSE = CalcRMSE(0, leftTest, rightTest);


				if (bestSplittingIndex == -1) //this is the first check, so set the bestsplitval and index to the current ones
				{
					bestSplittingIndex = index;
					bestSplittingVal = splitVal;
					lowestMSE = avgMSE;
				}
				else
				{
					//determin if the new avgMSE is lower than lowestMSE
					if (avgMSE < lowestMSE)
					{
						//this variable and splitpoint is best so far
						bestSplittingIndex = index;
						bestSplittingVal = splitVal;
						lowestMSE = avgMSE;
					}
			
				}
			}

			if (leftTest)
			{
				delete leftTest;
			}
			if (rightTest)
			{
				delete rightTest;
			}

		}

	}
	if (lowestMSE != 0)
	{
		std::cout << "lowestMSE: " << lowestMSE << std::endl;
	}
	

	splitInfo.splitIndex = bestSplittingIndex;
	splitInfo.splitVal = bestSplittingVal;
	return splitInfo;
}

void RandomSingleMSE::Partition(float splitVal,int splitIndex , DataSet *currentData, DataSet *&leftData, DataSet *&rightData)
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

std::vector<int> RandomSingleMSE::GetRandomFeatures()
{
	std::vector<int> featuresToConsider;
	for (int i = 0; i < this->maxNrOfVars +1 ; i++)
	{
		featuresToConsider.push_back(i);
	}

	this->mTry = rand() % maxNrOfConsideredVariables + 1;

	for (int i = 0; i < featuresToConsider.size(); i++)
	{
		int k = rand() % featuresToConsider.size();

		int temp = featuresToConsider[k];
		featuresToConsider[k] = featuresToConsider[i];
		featuresToConsider[i] = temp;

	}

	return featuresToConsider;
}