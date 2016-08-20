#include "DataLoader.h"


DataLoader::DataLoader()
{
	this->fileParser = NULL;
}


DataLoader::~DataLoader()
{
	if (fileParser)
	{
		delete fileParser;
		fileParser = NULL;
	}
}

DataSet* DataLoader::ParseAndGetData(std::string fileName, int nrOfInputs, int nrOfOutputs)
{
	//first check if file exists


	//first check if file exists


	//pars file then return it to caller
	if (fileParser)
	{
		delete fileParser;
		fileParser = NULL;
	}
	fileParser = new ArffParser(fileName);
	
	ArffData* loadedData = fileParser->parse();

	//convert LoadedData into my own format
	DataSet *dataSet = new DataSet(loadedData->num_instances(),nrOfInputs,nrOfOutputs);
	//Instance *newInst;

	for (int i = 0; i < loadedData->num_instances(); i++)
	{
		ArffInstance *inst = loadedData->get_instance(i);
		
		dataSet->data[i] = new Instance(nrOfInputs, nrOfOutputs);

		for (int j = 0; j < nrOfInputs; j++)
		{
			dataSet->data[i]->input[j] = (float)(*inst->get(j));
		}
		
		for (int j = nrOfInputs; j < nrOfOutputs + nrOfInputs; j++)
		{
			dataSet->data[i]->output[j-nrOfInputs] = (float)(*inst->get(j));
		}
	}
	

	return dataSet;
	//convert LoadedData into my own format
}
