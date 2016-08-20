#ifndef RANDOMMULTIMSE_H
#define RANDOMMULTIMSE_H
#include "ISplitter.h"

class RandomMultiMSE : public ISplitter
{
public:
	RandomMultiMSE();
	RandomMultiMSE(int maxNrOfConsideredVariables);
	~RandomMultiMSE();

	SplitInfo ConsiderSplit(DataSet *currentDataSet) override;

private:
	int maxNrOfConsideredVariables; //must not be larger than the number of variables available
	int maxNrOfVars;
	int mTry;

private:
	std::vector<int> GetRandomFeatures();
};


#endif
