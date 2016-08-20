#ifndef RANDOMSINGLEMSE_H
#define RANDOMSINGLEMSE_H

#include "ISplitter.h"

class RandomSingleMSE : public ISplitter
{
public:
	RandomSingleMSE();
	RandomSingleMSE(int maxNrOfConsideredVariables);
	~RandomSingleMSE();

	SplitInfo ConsiderSplit(DataSet *currentDataSet) override;

private:
	int maxNrOfConsideredVariables; //must not be larger than the number of variables available
	int maxNrOfVars;
	int mTry;

private:
	void Partition(float splitVal,int splitIndex ,DataSet *currentData, DataSet *&leftData, DataSet *&rightData);
	std::vector<int> GetRandomFeatures();

};

#endif