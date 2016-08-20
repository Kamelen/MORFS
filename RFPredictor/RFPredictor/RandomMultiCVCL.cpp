#include "RandomMultiCVCL.h"
#include <iostream>

RandomMultiCVCL::RandomMultiCVCL()
{
	this->maxNrOfConsideredVariables = 5;
	this->maxNrOfVars = 5;
}

RandomMultiCVCL::RandomMultiCVCL(int maxNrOfConsideredVariables, float(*calcMetricfunc)(int outputIndex, DataSet* leftTest, DataSet *rightTest))
{
	this->maxNrOfConsideredVariables = sqrt(maxNrOfConsideredVariables);
	this->maxNrOfVars = maxNrOfConsideredVariables;
	this->calcMetric = calcMetricfunc;
}


RandomMultiCVCL::~RandomMultiCVCL()
{

}


SplitInfo RandomMultiCVCL::ConsiderSplit(DataSet *currentDataSet)
{
	SplitInfo splitInfo;
	splitInfo.splitIndex = 0;
	splitInfo.splitVal = 0;

	std::vector<int> featuresToConsider = GetRandomFeatures();
	LinkNode *headNode = 0;

	//first calculate the metric for all the featuresToConsider
	for (int i = 0; i < (int)featuresToConsider.size(); i++)
	{
		if (i >= this->mTry && headNode != 0)
		{
			//has gone through all variables it should, send down to the correlation ranking
			i = featuresToConsider.size();
		}
		else
		{
			int index = featuresToConsider[i];
			float splitVal = 0;
			DataSet *leftTest;
			DataSet *rightTest;
			CalculatedSplit calculatedSplit;

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
						CombinedMSE += calcMetric(k, leftTest, rightTest);

					}

					CombinedMSE /= currentDataSet->nrOfOutputs;
					//CombinedMSE = sqrt(CombinedMSE);
					calculatedSplit.errorMetric = CombinedMSE;
					calculatedSplit.splitIndex = index;
					calculatedSplit.splitVal = splitVal;
					insertSplitSorted(headNode, calculatedSplit);

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
	}

	

	//make sure the metrics are sorted with 0 = best, n = worst
	LinkNode *walker = headNode;
	//while (walker != 0)
	//{
	//	std::cout << "splitmetric: " << walker->split.errorMetric << std::endl;

	//	walker = walker->nextNode;
	//}


	int k = 5;
	walker = headNode;
	int bestSplittingIndex = -1;
	float highestCorrelation = 0;
	float bestSplittingVal = 0;
	//then calculate the correlation for the k best metrics
	for (int i = 0; i < k; i++)
	{
		if (walker == 0)//list stops before i == k
		{
			i = k;
		}
		else
		{
			CalculatedSplit split = walker->split;

			float correlation = 0;

			for (int j = 0; j < currentDataSet->nrOfOutputs; j++)
			{
				float covariance = CalcCovariance(split.splitIndex, j, currentDataSet);
				if (covariance < 0.0)
				{
					covariance *= -1;
				}
				correlation += CalcCorrelation(split.splitIndex, j, currentDataSet, covariance);
			}

			correlation /= currentDataSet->nrOfOutputs;

			if (correlation > highestCorrelation)
			{
				highestCorrelation = correlation;
				bestSplittingIndex = split.splitIndex;
				bestSplittingVal = split.splitVal;
			}

			walker = walker->nextNode;
		}
		
		//calc correlation for walker->split
		//if correlation is better than highest corr then choose that one.(start with highest being 0 to ensure first calc is inputed)
	}
	if (headNode)
	{
		delete headNode;
	}
	

	splitInfo.splitIndex = bestSplittingIndex;
	splitInfo.splitVal = bestSplittingVal;
	return splitInfo;
}


std::vector<int> RandomMultiCVCL::GetRandomFeatures()
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

void RandomMultiCVCL::insertSplitSorted(LinkNode *&head, CalculatedSplit item)
{

	if (head == 0)//insert first if it is the first item to be inserted
	{
		head = new LinkNode();
		head->split = item;
	}
	else if (item.errorMetric < head->split.errorMetric)
	{
		LinkNode *newNode = new LinkNode();

		newNode->split = item;

		newNode->nextNode = head;
		head->PreviousNode = newNode;

	}
	else
	{
		LinkNode* walker = head;
		bool found = false;

		while (!found && walker->nextNode != 0)
		{
			if (item.errorMetric == walker->split.errorMetric)
			{
				found = true;
			}
			else if (item.errorMetric < walker->split.errorMetric)
			{
				LinkNode *newNode = new LinkNode();
				newNode->split = item;

				walker->PreviousNode->nextNode = newNode;
				newNode->PreviousNode = walker->PreviousNode;
				newNode->nextNode = walker;
				walker->PreviousNode = newNode;

				found = true;
			}

			walker = walker->nextNode;
		}
		if (!found)//walker is lastnode and newnode(item should be inserted as walker->nextnode)
		{
			LinkNode *newNode = new LinkNode();

			if (item.errorMetric == walker->split.errorMetric)
			{
				found = true;
			}
			else if (item.errorMetric < walker->split.errorMetric) //insert before walker(walker is last)
			{
				newNode->split = item;

				walker->PreviousNode->nextNode = newNode;
				newNode->PreviousNode = walker->PreviousNode;
				newNode->nextNode = walker;
				walker->PreviousNode = newNode;
			}
			else //insert after walker(last)
			{
				newNode->split = item;
				newNode->PreviousNode = walker;
				walker->nextNode = newNode;
			}
			

			found = true;
		}
	}
	

}