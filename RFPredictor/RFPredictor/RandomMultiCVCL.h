#ifndef RANDOMMULTICVCL_H
#define RANDOMMULTICVCL_H
#include "ISplitter.h"



class RandomMultiCVCL : public ISplitter
{
public:
	RandomMultiCVCL();
	RandomMultiCVCL(int maxNrOfConsideredVariables, float(*calcMetricfunc)(int outputIndex, DataSet* leftTest, DataSet *rightTest));
	~RandomMultiCVCL();

	SplitInfo ConsiderSplit(DataSet *currentDataSet) override;
	float(*calcMetric)(int outputIndex, DataSet* leftTest, DataSet *rightTest);

private:
	int maxNrOfConsideredVariables; //must not be larger than the number of variables available
	int maxNrOfVars;
	int mTry;

private:
	std::vector<int> GetRandomFeatures();
	void insertSplitSorted(LinkNode *&head, CalculatedSplit item);

};


#endif