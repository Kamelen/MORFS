#include "Explorer.h"
#include <iostream>
#include "SORandomForests.h"
#include "MORandomForests.h"
#include "RandomMultiCVCL.h"
#include "RandomMultiMSE.h"


Explorer::Explorer()
{
	dataLoader = new DataLoader();
	SelectedClassifier = new SORandomForests();
	this->singleOutputMode = true;

	this->avgTreeTime = 0;
	this->avgModelTime = 0;
}


Explorer::~Explorer()
{
	if (dataLoader)
	{
		delete dataLoader;
		dataLoader = NULL;
	}
	if (loadedData)
	{
		delete loadedData;
		loadedData = NULL;
	}
}
void Explorer::testSingleOutput(DataSet *data)
{
	std::vector<DataSet*> singleOutputData;

	for (int i = 0; i < data->nrOfOutputs; i++)
	{
		DataSet *transData = new DataSet(data->nrOfInstances,data->nrOfInputs,1);

		for (int j = 0; j < data->nrOfInstances; j++)
		{
			Instance *inst = new Instance();
			inst->input = data->data[j]->input;
			
			inst->output = new float[1];
			inst->output[0] = data->data[j]->output[i];
			transData->data[j] = inst;
		}
			
		singleOutputData.push_back(transData);
	}


	for (int i = 0; i < singleOutputData.size(); i++)
	{
		DataSet* allData = singleOutputData[i];

		SORandomForests* learner = new SORandomForests();
		std::vector<StatPair> stats = CrossValidation(learner, allData, 5, 50, i);
		for (int j = 0; j < stats.size(); j++)
		{
			combinedSingleOutputStats[i].push_back(stats[j]);
		}

		delete learner;
	}
	//this->avgModelTime /= singleOutputData.size();
	this->avgTreeTime /= singleOutputData.size();

}
void Explorer::testMultiOutput(DataSet *data)
{
	RandomMultiCVCL *splitter = new RandomMultiCVCL(data->nrOfInputs, UTILS_H::CalcRMSE);


	MORandomForests *learner = new MORandomForests(splitter);

	//crossvalidation
	std::vector<StatPair> stats = CrossValidation(learner, data, 5, 50, -1);

	for (int i = 0; i < stats.size(); i++)
	{
		this->stats.push_back(stats[i]);
	}
	delete learner;

}

void Explorer::MultiSplittCriterionTest(DataSet *data, float(*calcMetric)(int outputIndex, DataSet* leftTest, DataSet *rightTest))
{
	RandomMultiCVCL *splitter = new RandomMultiCVCL(data->nrOfInputs, calcMetric);

	MORandomForests *learner = new MORandomForests(splitter);

	//crossvalidation
	std::vector<StatPair> stats = CrossValidation(learner, data, 5, 50, -1);

	for (int i = 0; i < stats.size(); i++)
	{
		this->stats.push_back(stats[i]);
	}
	delete learner;
}

void Explorer::ExperimentTwo(DataSet *data, std::string datasetName)
{
	int nrOfRuns = 50;
	int now = 1;
	int done = 4;

	////NEW RUN

	//this->avgTreeTime = 0;
	//this->avgModelTime = 0;

	//fileWriter.open("Experiment2-" "CVRMSE" + datasetName + ".txt");
	//std::cout << now << "/" << done << std::endl;
	//for (int i = 0; i < nrOfRuns; i++)
	//{
	//	float progress = ((float)i / (float)nrOfRuns) * 100;
	//	
	//	std::cout << "progress: " << progress << "%" << std::endl;
	//	combinedMetric = 0;
	//	MultiSplittCriterionTest(data, UTILS_H::CalcCVRMSE);
	//	combinedMetric = sqrt(combinedMetric);

	//}
	//this->avgTreeTime /= nrOfRuns;
	//this->avgModelTime /= nrOfRuns;
	//PrintStatistics(this->stats, data->nrOfOutputs, -1);
	//fileWriter << std::endl << "treeTime(ms): " << avgTreeTime << "|| modelTime(ms): " << avgModelTime << std::endl;
	//fileWriter.close();
	//now++;


	//NEW RUN

	this->avgTreeTime = 0;
	this->avgModelTime = 0;

	fileWriter.open("Experiment2-" "NRMSE" + datasetName + ".txt");
	std::cout << now << "/" << done << std::endl;
	for (int i = 0; i < nrOfRuns; i++)
	{

		float progress = ((float)i / (float)nrOfRuns) * 100;
		std::cout << "progress: " << progress << "%" << std::endl;
		combinedMetric = 0;
		MultiSplittCriterionTest(data, UTILS_H::CalcNRMSE);
		combinedMetric = sqrt(combinedMetric);
		
		fileWriter.close();

	}
	this->avgTreeTime /= nrOfRuns;
	this->avgModelTime /= nrOfRuns;
	PrintStatistics(this->stats, data->nrOfOutputs, -1);
	fileWriter << std::endl << "treeTime(ms): " << avgTreeTime << "|| modelTime(ms): " << avgModelTime << std::endl;
	fileWriter.close();
	now++;

	////NEW RUN

	//this->avgTreeTime = 0;
	//this->avgModelTime = 0;

	//fileWriter.open("Experiment2-" "RMSE" + datasetName + ".txt");
	//std::cout << now << "/" << done << std::endl;
	//for (int i = 0; i < nrOfRuns; i++)
	//{
	//	float progress = ((float)i / (float)nrOfRuns) * 100;
	//	std::cout << "progress: " << progress << "%" << std::endl;
	//	combinedMetric = 0;
	//	MultiSplittCriterionTest(data, UTILS_H::CalcRMSE);
	//	combinedMetric = sqrt(combinedMetric);

	//}
	//this->avgTreeTime /= nrOfRuns;
	//this->avgModelTime /= nrOfRuns;
	//PrintStatistics(this->stats, data->nrOfOutputs, -1);
	//fileWriter << std::endl << "treeTime(ms): " << avgTreeTime << "|| modelTime(ms): " << avgModelTime << std::endl;
	//fileWriter.close();
	//now++;

	//NEW RUN
	/*this->avgTreeTime = 0;
	this->avgModelTime = 0;

	fileWriter.open("Experiment2-" "LAD" + datasetName + ".txt");
	std::cout << now << "/" << done << std::endl;
	for (int i = 0; i < nrOfRuns; i++)
	{
		float progress = ((float)i / (float)nrOfRuns) * 100;
		std::cout << "progress: " << progress << "%" << std::endl;
		combinedMetric = 0;
		MultiSplittCriterionTest(data, UTILS_H::CalcLAD);
		combinedMetric = sqrt(combinedMetric);

	}
	this->avgTreeTime /= nrOfRuns;
	this->avgModelTime /= nrOfRuns;
	PrintStatistics(this->stats, data->nrOfOutputs, -1);
	fileWriter << std::endl << "treeTime(ms): " << avgTreeTime << "|| modelTime(ms): " << avgModelTime << std::endl;
	fileWriter.close();
	now++;
	std::cout << now << "/" << done << std::endl;
*/
}

void Explorer::ExperimentOne(DataSet *data, std::string datasetName)
{
	int nrOfRuns = 25;
	//std::cout << "single-output" << std::endl;
	//this->avgTreeTime = 0;
	//this->avgModelTime = 0;
	//fileWriter.open("Experiment1-" "Single-output(RMSE)-" + datasetName + ".txt");
	//combinedSingleOutputStats.resize(data->nrOfOutputs);
	//for (int i = 0; i < nrOfRuns; i++)
	//{
	//	std::cout << "new crossval" << std::endl;
	//	float progress = ((float)i / (float)nrOfRuns) * 100;
	//	std::cout << "progress: " << progress << "%" << std::endl;
	//	combinedMetric = 0;
	//	testSingleOutput(data);
	//	combinedMetric = sqrt(combinedMetric);

	//}
	//this->avgTreeTime /= nrOfRuns;
	//this->avgModelTime /= nrOfRuns;
	//for (int i = 0; i < combinedSingleOutputStats.size(); i++)
	//{
	//	PrintStatistics(combinedSingleOutputStats[i], 1, i);
	//}
	//fileWriter << std::endl << "treeTime(ms): " << avgTreeTime << "|| modelTime(ms): " << avgModelTime << std::endl;

	//
	//fileWriter.close();

	//std::cout << "multi-output" << std::endl;
	//fileWriter.open("Experiment1-" "Multi-output(RCL)-" + datasetName + ".txt");

	this->avgTreeTime = 0;
	this->avgModelTime = 0;
	for (int i = 0; i < nrOfRuns; i++)
	{
		std::cout << "new crossval" << std::endl;
		float progress = ((float)i / (float)nrOfRuns) * 100;
		std::cout << "progress: " << progress << "%" << std::endl;
		combinedMetric = 0;
		testMultiOutput(data);
		combinedMetric = sqrt(combinedMetric);
		//fileWriter << "combined MSE:" << " " << combinedMetric << std::endl;

	}
	this->avgTreeTime /= nrOfRuns;
	this->avgModelTime /= nrOfRuns;
	//PrintStatistics(this->stats, data->nrOfOutputs, -1);
	//fileWriter << std::endl << "treeTime(ms): " << avgTreeTime << "|| modelTime(ms): " << avgModelTime << std::endl;
	//fileWriter.close();
}

int Explorer::Run()
{
	DataSet *data =  dataLoader->ParseAndGetData("hub2.arff", 10, 4);
	//DataSet *data = dataLoader->ParseAndGetData("autoprice.arff", 15, 1);
	//DataSet *data = dataLoader->ParseAndGetData("Crime.arff", 5, 2);
	//DataSet *data = dataLoader->ParseAndGetData("cpu.arff", 6, 1);
	ExperimentOne(data,"Hubtest");
	//ExperimentTwo(data,"Hub");
	//testSingleOutput(data);
	//testMultiOutput(data);
	

	std::string input = "";
	int choice = 0;
	int nrOfOutputs = 0;
	int nrOfInputs = 0;
	int nrOfFolds = 0;
	Instance *inst;

	std::cout << "1: Load a file" << std::endl;
	std::cout << "2: Train selectedClassifier on loaded data if it exists" << std::endl;
	std::cout << "3: Create a classifier" << std::endl;
	std::cout << "4: Print the data of the loaded file" << std::endl;
	std::cout << "5: CrossValidate" << std::endl;
	std::cout << "6: Exit" << std::endl;


	std::cin >> choice;

	switch (choice)
	{
	case 1:
		std::cout << "Type a fileName to load" << std::endl;
		std::cin >> input;
		std::cout << "Set number of inputs in each instance" << std::endl;
		std::cin >> nrOfInputs;
		std::cout << "set number of outputs in each instance" << std::endl;
		std::cin >> nrOfOutputs;

		loadedData = dataLoader->ParseAndGetData(input + ".arff",nrOfInputs,nrOfOutputs);


		
		if (loadedData)
		{
			std::cout << "Data is loaded" << std::endl;
		}
		else
		{
			std::cout << "No data found" << std::endl;
		}
		if (nrOfOutputs > 1 && singleOutputMode)
		{
			//split into n single output instances(data.size * output.size = newdata.size)
			

			for (int i = 0; i < nrOfOutputs; i++)
			{
				DataSet *transData = new DataSet(loadedData->nrOfInstances,loadedData->nrOfInputs,1);

				for (int j = 0; j < loadedData->nrOfInstances; j++)
				{
					Instance *inst = new Instance();
					inst->input = loadedData->data[j]->input;
					inst->output = new float[1];
					inst->output[0] = loadedData->data[j]->output[i];
					transData->data[j] = inst;
				}
			
				transformedData.push_back(transData);
			}
		}

		break;

	case 2:
		if (transformedData.size() > 0)
		{
			//data has been transformed
			//train transformedData.size() nr of classifiers
			for (int i = 0; i < (int)transformedData.size(); i++)
			{
				ITreeClassifier *RF = new SORandomForests();
				RF->Train(transformedData[i],20);
				transformedClassifiers.push_back(RF);
				std::cout << "classifier: " << i << " trained" << std::endl;
			}
		}
		else
		{
			if (loadedData)
			{
				SelectedClassifier->Train(loadedData, 20);
			}
			else
			{
				std::cout << "Cant run classifier: No data found" << std::endl;
			}
		}
		
		break;

	case 3:


		break;

	case 4:
		if (!loadedData)
		{
			std::cout << "Cant print: No data found" << std::endl;

			break;
		}

		for (int i = 0; i < loadedData->nrOfInstances; i++)
		{
			inst = loadedData->data[i];
			std::cout << "instance: " << i+1 << " = " << std::endl << std::endl;
			
			std::cout << "inputs: " << std::endl;
			for (int j = 0; j < loadedData->nrOfInputs; j++)
			{
				std::cout << "#" << i << ": "<< inst->input[j] << std::endl;
			}

			std::cout << std::endl << "outputs: " << std::endl;
			for (int j = 0; j <loadedData->nrOfOutputs; j++)
			{
				std::cout << "#" << i << ": " << inst->output[j] << std::endl;
			}

			std::cout << std::endl;
		}

		break;

	case 5:
		//crossvalidate transformed problem
		std::cout << "enter number of folds" << std::endl;
		std::cin >> nrOfFolds;
		if (transformedData.size() > 0)
		{
			for (int i = 0; i < 5; i++)
			{
				ITreeClassifier *RF = new SORandomForests();
				transformedClassifiers.push_back(RF);
				//CrossValidation(RF, transformedData[0], nrOfFolds, 10);
			}
			//PrintStatistics(CrossValPredictions, transformedData[0]->nrOfOutputs);

		}
		else
		{
			//crossvalidate the normal "loadedData" set
			SelectedClassifier = new SORandomForests();
			
			//PrintStatistics(CrossValidation(SelectedClassifier, loadedData, nrOfFolds, 10), loadedData->nrOfOutputs);
		}
		break;

	case 6:
		return 0;
		break;
	}



	return 1;
}

std::vector<StatPair> Explorer::CrossValidation(ITreeClassifier *learner, DataSet *data, int nrOfFolds, int nrOfTrees, int outputIndex)
{
		//1. randomly permuate the set

		Instance *temp;
		int x = 0;
		std::vector<StatPair> CrossValPredictions;
		std::vector<DataSet*> foldedData;
		float treeTime = 0;
		float modelTime = 0;

		for (int i = 0; i < data->nrOfInstances; i++)
		{
			int x = rand() % data->nrOfInstances;
			temp = data->data[x];
			data->data[x] = data->data[i];
			data->data[i] = temp;
		}

		//2. split up into nrOfFolds folds
		for (int i = 0; i < nrOfFolds; i++)
		{
			DataSet *fold = new DataSet(data->nrOfInstances / nrOfFolds, data->nrOfInputs, data->nrOfOutputs);

			for (int j = 0; j < data->nrOfInstances / nrOfFolds; j++)
			{
				fold->data[j] = (data->data[(i * data->nrOfInstances / nrOfFolds) + j]);
			}

			foldedData.push_back(fold);
		}


		//3. train nrOfFolds learners each with 1 fold left out

		for (int i = 0; i < nrOfFolds; i++)
		{
			//std::cout << "fold" << std::endl;
			std::vector<Instance*> tempSet;
			DataSet *testSet = new DataSet();

			testSet = foldedData[i];

			for (int j = 0; j < nrOfFolds; j++)
			{
				if (j == i)
				{
					//testfold
				}
				else
				{
					DataSet *fold = foldedData[i];

					for (int k = 0; k < fold->nrOfInstances; k++)
					{
						tempSet.push_back(fold->data[k]);
					}
				}
			}

			DataSet *trainingSet = new DataSet(tempSet.size(), data->nrOfInputs, data->nrOfOutputs);
			for (int j = 0; j < (int)tempSet.size(); j++)
			{
				trainingSet->data[j] = tempSet[j];
			}
			//now train
			learner->Train(trainingSet, nrOfTrees);
			modelTime += learner->getModelTime();
			treeTime += learner->getTreeTime();
			for (int j = 0; j < testSet->nrOfInstances; j++)
			{
				float *pred = 0;
				float *awnser = 0;
				awnser = testSet->data[j]->output;

				pred = learner->Predict(testSet->data[j])->output;

				StatPair statPair;
				statPair.prediction = pred;
				statPair.observation = awnser;
				statPair.outputIndex = outputIndex;

				CrossValPredictions.push_back(statPair);

			}
			

		}
		modelTime /= nrOfFolds;
		treeTime /= nrOfFolds;

		this->avgModelTime += modelTime;
		this->avgTreeTime += treeTime;
		return CrossValPredictions;
}

void Explorer::PrintStatistics(std::vector<StatPair> stats, int nrOfOutputs, int currentOutput)
{
	float MSE = 0;
	float combinedMSE = 0;
	float averageAwns = 0;
	float averagePred = 0;
	for (int j = 0; j < nrOfOutputs; j++)
	{
		for (int i = 0; i < (int)stats.size(); i++)
		{
			float awns = stats[i].observation[j];
			float pred = stats[i].prediction[j];

			MSE += (awns - pred) * (awns - pred);
		}

		MSE /= stats.size();
		MSE = sqrt(MSE);

		combinedMetric += MSE;

		//std::cout << "MSE for output:" << j << " " << MSE << std::endl;
		if (currentOutput == -1)
		{
			fileWriter << "#" << j << ": " << MSE << " || ";
		}
		else
		{
			fileWriter << "#" << currentOutput << ": " << MSE << " || ";
		}
		
	}
}