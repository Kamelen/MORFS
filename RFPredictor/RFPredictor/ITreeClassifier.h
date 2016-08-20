#ifndef ITREECLASSIFIER_H
#define ITREECLASSIFIER_H

#include "IPredictor.h"
#include "ISplitter.h"
#include "Utils.h"

//not sure on this implementation
class ITreeClassifier
{
public:
	ITreeClassifier(){};
	~ITreeClassifier(){};

	virtual Instance* Predict(Instance* instToBePredicted) = 0;
	virtual void Train(DataSet* input, int nrOfTrees) = 0;
	virtual float getModelTime() = 0;
	virtual float getTreeTime() = 0;

private:
	IPredictor* predictor;
	ISplitter* splitter;
};

#endif
