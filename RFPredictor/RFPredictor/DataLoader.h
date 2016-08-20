#ifndef DATALOADER_H
#define DATALOADER_H
#include "arff_parser.h"
#include "Utils.h"

//Reads data from ARFF format and creates a dataset(my own format)
//TODO: Define what a dataset is and how it is to be represented
//TODO: Implement a ARFF loader function that returns one of these datasets(my own format)
class DataLoader
{
public:
	DataLoader();
	~DataLoader();

	//Only need this functionallity right now
	//sends null if no file is found
	DataSet* ParseAndGetData(std::string fileName, int nrOfInputs, int nrOfOutputs);


private:
	ArffParser *fileParser;
};

#endif
