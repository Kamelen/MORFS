#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <chrono>


struct Instance
{
	float *input;
	float *output;

	Instance()
	{
		input = NULL;
		output = NULL;
	}

	Instance(int nrOfInputs, int nrOfOutputs)
	{
		this->input = new float[nrOfInputs];
		this->output = new float[nrOfOutputs];
	}

	~Instance()
	{
		delete input;
		delete output;
	}

};




struct DataSet
{
	Instance** data;
	int nrOfInputs;
	int nrOfOutputs;
	int nrOfInstances;

	DataSet()
	{
			
	}

	DataSet(int nrOfInstances, int nrOfInputs, int nrOfOutputs)
	{
		this->nrOfInstances = nrOfInstances;
		this->nrOfInputs = nrOfInputs;
		this->nrOfOutputs = nrOfOutputs;
		this->data = new Instance*[nrOfInstances];
	}

	void clean()
	{
		for(int i = 0; i < this->nrOfInstances; i++)
		{
			delete data[i];
		}
		delete data;
		data = NULL;
	}

	~DataSet()
	{
		if(data)
		{
			delete data;
			data = NULL;
		}
		
	}

};

struct SplitInfo
{
	float splitVal;
	int splitIndex;
};

struct CalculatedSplit
{
	float splitVal;
	int splitIndex;

	float correlation;
	float errorMetric;
	

};


struct StatPair
{
	float *prediction;
	float *observation;
	int outputIndex;//-1 if prediction and observation contain multiple floats
};

struct LinkNode
{
	CalculatedSplit split;
	LinkNode *nextNode;//null if last
	LinkNode *PreviousNode;//null if first

	LinkNode()
	{
		nextNode = 0;//remains null if last
		PreviousNode = 0;//remains null if first
	}

	~LinkNode()
	{
		if (nextNode)
		{
			delete nextNode;
		}
		
	}

};



//STATISTICAL CALCULATIONS DEF
float CalcCovariance(int inputIndex, int outputIndex, DataSet *dataset);
float CalcCorrelation(int inputIndex, int outputIndex, DataSet *dataset, float covariance);
float AvgSum(int featureToSum, DataSet *dataSet, bool isOutput);
float CalcPercentMetric(int outputIndex, DataSet* leftTest, DataSet *rightTest);
float Calc(int outputIndex, DataSet* leftTest, DataSet *rightTest);
float CalcLAD(int outputIndex, DataSet* leftTest, DataSet *rightTest);
float CalcRMSE(int outputIndex, DataSet* leftTest, DataSet *rightTest);
float CalcNRMSE(int outputIndex, DataSet* leftTest, DataSet *rightTest);
float CalcCVRMSE(int outputIndex, DataSet* leftTest, DataSet *rightTest);

void Partition(float splitVal, int splitIndex, DataSet *currentData, DataSet *&leftData, DataSet *&rightData);
//STATISTICAL CALCULATIONS DEF


#endif

