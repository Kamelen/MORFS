#ifndef MORANDOMFORESTS_H
#define MORANDOMFORESTS_H
#include "ITreeClassifier.h"
#include "Tree.h"
#include "ISplitter.h"
class MORandomForests : public ITreeClassifier
{

public:
	MORandomForests();
	MORandomForests(ISplitter* splitter);
	~MORandomForests();

	virtual Instance* Predict(Instance* instToBePredicted);
	virtual void Train(DataSet* input, int nrOfTrees);
	virtual float getModelTime();
	virtual float getTreeTime();

private:
	std::vector<Tree*> *trees;
	int nrOfOutputs;
	ISplitter *splitter;
	float modelTime;
	float treeTime;

private:
	DataSet* ConstructBaggedSet(DataSet* trainingSet);

};

#endif