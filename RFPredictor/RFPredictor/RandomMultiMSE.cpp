#include "RandomMultiMSE.h"
#include <iostream>

#include <stdlib.h>
#include <time.h>


RandomMultiMSE::RandomMultiMSE()
{
	this->maxNrOfConsideredVariables = 5;
	this->maxNrOfVars = 5;
}

RandomMultiMSE::RandomMultiMSE(int maxNrOfConsideredVariables)
{
	this->maxNrOfConsideredVariables = sqrt(maxNrOfConsideredVariables);
	this->maxNrOfVars = maxNrOfConsideredVariables;
}


RandomMultiMSE::~RandomMultiMSE()
{

}

SplitInfo RandomMultiMSE::ConsiderSplit(DataSet *currentDataSet)
{
	SplitInfo splitInfo;
	splitInfo.splitIndex = 0;
	splitInfo.splitVal = 0;
	float bestSplittingVal = 0;
	float lowestCombinedMSE = 0;
	int bestSplittingIndex = -1;

	std::vector<int> featuresToConsider = GetRandomFeatures();
	
	for (int i = 0; i < (int)featuresToConsider.size(); i++)
	{
		if (i >= this->mTry && lowestCombinedMSE != 0)
		{
			splitInfo.splitIndex = bestSplittingIndex;
			splitInfo.splitVal = bestSplittingVal;
			if (lowestCombinedMSE != 0)
			{
				//std::cout << "lowestMSE: " << lowestCombinedMSE << std::endl;
			}
			return splitInfo; //valid splittingvalue found
		}

		int index = featuresToConsider[i];
		float splitVal = 0;
		DataSet *leftTest;
		DataSet *rightTest;

		for (int j = 0; j < currentDataSet->nrOfInstances; j++)
		{
			splitVal = currentDataSet->data[j]->input[index];

			Partition(splitVal, index, currentDataSet, leftTest, rightTest);

			if (leftTest->nrOfInstances == 0 || rightTest->nrOfInstances == 0)
			{
				//crappy split, do nothing
			}
			else
			{
				float CombinedMSE = 0;
				//test the combined MSE here
				for (int k = 0; k < currentDataSet->nrOfOutputs; k++)
				{
					float avgMSE = 0;
					avgMSE = CalcRMSE(k, leftTest, rightTest);

					CombinedMSE += avgMSE;
				}
				CombinedMSE /= currentDataSet->nrOfOutputs;
				//CombinedMSE = sqrt(CombinedMSE);

				if (bestSplittingIndex == -1) //this is the first check, so set the bestsplitval and index to the current ones
				{
					bestSplittingIndex = index;
					bestSplittingVal = splitVal;
					lowestCombinedMSE = CombinedMSE;
				}
				else
				{
					if (CombinedMSE < lowestCombinedMSE)
					{
						//this variable and splitpoint is best so far
						bestSplittingIndex = index;
						bestSplittingVal = splitVal;
						lowestCombinedMSE = CombinedMSE;
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

	if (lowestCombinedMSE != 0)
	{
		std::cout << "lowestMSE: " << lowestCombinedMSE << std::endl;
	}
	
	splitInfo.splitIndex = bestSplittingIndex;
	splitInfo.splitVal = bestSplittingVal;
	return splitInfo;
}


std::vector<int> RandomMultiMSE::GetRandomFeatures()
{
	std::vector<int> featuresToConsider;
	for (int i = 0; i < this->maxNrOfVars + 1; i++)
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


