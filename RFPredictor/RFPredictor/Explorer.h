#ifndef EXPLORER_H
#define EXPLORER_H

#include <vector>
#include "ITreeClassifier.h"
#include "DataLoader.h"
#include <fstream>


//This is the core of the program, it will handle communication between the dataloader and the classifiers
//Will have a list of classifiers, each with a name?
//Make sure that the classifier code itself is contained in its own class to facillitate a modular design.

//TODO: List of classifiers, able to use classifiers(what functions needs to be done in explorer for this?).
//TODO: Run function that waits for input and makes calls functions based on that input (cin)(switchcase)
typedef float(*calcMetric)(int outputIndex, DataSet* leftTest, DataSet *rightTest);
class Explorer
{
public:
	Explorer();
	~Explorer();

	int Run();

private:
	std::vector<ITreeClassifier> Classifiers;
	ITreeClassifier *SelectedClassifier;

	DataLoader *dataLoader;

	DataSet *loadedData;
	std::vector<DataSet*> transformedData;
	std::vector<ITreeClassifier*> transformedClassifiers;
	bool singleOutputMode;
	float combinedMetric;

	std::ofstream fileWriter;

	std::vector<StatPair> stats;
	std::vector<std::vector<StatPair>> combinedSingleOutputStats;

	float avgModelTime;
	float avgTreeTime;

private:
	std::vector<StatPair> CrossValidation(ITreeClassifier *learner, DataSet *data, int nrOfFolds, int nrOfTrees, int outputIndex); //outputIndex == -1 if multi-output case
	void PrintStatistics(std::vector<StatPair> stats, int nrOfOutputs, int currentOutput);
	void testSingleOutput(DataSet *data);
	void testMultiOutput(DataSet *data);
	
	void MultiSplittCriterionTest(DataSet *data, float(*calcMetric)(int outputIndex, DataSet* leftTest, DataSet *rightTest));

	void ExperimentOne(DataSet *data, std::string datasetName);
	void ExperimentTwo(DataSet *data, std::string datasetName);

};

#endif