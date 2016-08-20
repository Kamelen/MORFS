#ifndef SORANDOMFORESTS_H
#define SORANDOMFORESTS_H

#include "ITreeClassifier.h"
#include "Tree.h"

class SORandomForests : public ITreeClassifier
{
public:
	SORandomForests();
	~SORandomForests();

	virtual Instance* Predict(Instance* instToBePredicted);
	virtual void Train(DataSet* input, int nrOfTrees);
	virtual float getModelTime();
	virtual float getTreeTime();

private:
	std::vector<Tree*> *trees;
	float modelTime;
	float treeTime;

private:
	DataSet* ConstructBaggedSet(DataSet* trainingSet);

};

#endif