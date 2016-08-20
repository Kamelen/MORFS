#include "Utils.h"


float AvgSum(int featureToSum, DataSet *dataSet, bool isOutput)
{
	float avgSum = 0;

	if (isOutput)
	{
		for (int i = 0; i < dataSet->nrOfInstances; i++)
		{
			avgSum += dataSet->data[i]->output[featureToSum];
		}
	}
	else
	{
		for (int i = 0; i < dataSet->nrOfInstances; i++)
		{
			avgSum += dataSet->data[i]->input[featureToSum];
		}
	}


	avgSum /= dataSet->nrOfInstances;

	return avgSum;
}

float CalcPercentMetric(int outputIndex, DataSet* leftTest, DataSet *rightTest)
{
	float leftPred = 0;
	float rightPred = 0;
	float leftMSE = 0;
	float rightMSE = 0;
	float leftSum = 0;
	float rightSum = 0;
	float AvgMSE = 0;

	leftPred = AvgSum(outputIndex, leftTest, true);

	rightPred = AvgSum(outputIndex, rightTest, true);


	for (int m = 0; m < leftTest->nrOfInstances; m++)
	{
		float outValue = leftTest->data[m]->output[outputIndex];
		float val = ((outValue - leftPred));
		if (val < 0)
		{
			val *= -1;
		}

		leftMSE += val;
		leftSum += outValue;

	}
	leftMSE /= leftSum;
	//leftMSE *= (100.0 / leftTest->nrOfInstances);

	for (int m = 0; m < rightTest->nrOfInstances; m++)
	{
		float outValue = rightTest->data[m]->output[outputIndex];
		float val = ((rightPred - outValue) / (outValue));
		if (val < 0)
		{
			val *= -1;
		}
		rightMSE += val;
		rightSum += outValue;
	}
	rightMSE /= rightSum;
	//rightMSE *= (100.0 / rightTest->nrOfInstances);

	AvgMSE = ((rightMSE + leftMSE) / 2);
	
	return AvgMSE;
}
float CalcRMSE(int outputIndex, DataSet* leftTest, DataSet *rightTest)
{
	//check here if left/right tests are size 0

	//now use left and right test to measure MSE
	//prediction val is the average of the outputvar
	float leftMSE = 0;
	float leftPred = 0;
	float rightMSE = 0;
	float rightPred = 0;
	float AvgMSE = 0;


	leftPred = AvgSum(outputIndex, leftTest, true);

	rightPred = AvgSum(outputIndex, rightTest, true);


	for (int k = 0; k < leftTest->nrOfInstances; k++)
	{
		float outValue = leftTest->data[k]->output[outputIndex];

		leftMSE += ((leftPred - outValue) * (leftPred - outValue));

	}
	leftMSE /= leftTest->nrOfInstances;
	leftMSE = sqrt(leftMSE);

	for (int k = 0; k < rightTest->nrOfInstances; k++)
	{
		float outValue = rightTest->data[k]->output[outputIndex];
		rightMSE += ((rightPred - outValue) * (rightPred - outValue));
	}
	rightMSE /= rightTest->nrOfInstances;
	rightMSE = sqrt(rightMSE);


	AvgMSE = ((rightMSE + leftMSE) / 2);

	return AvgMSE;
}

float CalcLAD(int outputIndex, DataSet* leftTest, DataSet *rightTest)
{
	float leftPred = 0;
	float leftLAD = 0;
	float rightLAD = 0;
	float rightPred = 0;


	leftPred = AvgSum(outputIndex, leftTest, true);

	rightPred = AvgSum(outputIndex, rightTest, true);

	for (int k = 0; k < leftTest->nrOfInstances; k++)
	{
		float outValue = leftTest->data[k]->output[outputIndex];
		float calc = (outValue - leftPred);

		if (calc < 0)
			calc *= -1;

		leftLAD += calc;
	}
	leftLAD /= leftTest->nrOfInstances;

	for (int k = 0; k < rightTest->nrOfInstances; k++)
	{
		float outValue = rightTest->data[k]->output[outputIndex];
		float calc = (outValue - rightPred);

		if (calc < 0)
			calc *= -1;

		rightLAD += calc;
	}
	rightLAD /= rightTest->nrOfInstances;

	return (leftLAD + rightLAD) / 2;

}


float CalcNRMSE(int outputIndex, DataSet* leftTest, DataSet *rightTest)
{
	float leftMSE = 0;
	float leftPred = 0;
	float rightMSE = 0;
	float rightPred = 0;
	float max = 0;
	float min = 0;
	float AvgMSE = 0;


	leftPred = AvgSum(outputIndex, leftTest, true);

	rightPred = AvgSum(outputIndex, rightTest, true);

	min = leftTest->data[0]->output[outputIndex];
	max = leftTest->data[0]->output[outputIndex];
	for (int k = 0; k < leftTest->nrOfInstances; k++)
	{
		float outValue = leftTest->data[k]->output[outputIndex];

		leftMSE += ((leftPred - outValue) * (leftPred - outValue));

		if (outValue > max)
		{
			max = outValue;
		}
		if (outValue < min)
		{
			min = outValue;
		}


	}
	leftMSE /= leftTest->nrOfInstances;
	leftMSE = sqrt(leftMSE);
	leftMSE /= (max - min);
	
	min = rightTest->data[0]->output[outputIndex];
	max = rightTest->data[0]->output[outputIndex];
	for (int k = 0; k < rightTest->nrOfInstances; k++)
	{
		float outValue = rightTest->data[k]->output[outputIndex];
		rightMSE += ((rightPred - outValue) * (rightPred - outValue));

		if (outValue > max)
		{
			max = outValue;
		}
		if (outValue < min)
		{
			min = outValue;
		}
	}
	rightMSE /= rightTest->nrOfInstances;
	rightMSE = sqrt(rightMSE);
	rightMSE /= (max - min);

	AvgMSE = ((rightMSE + leftMSE) / 2);

	return AvgMSE;

}

float CalcCVRMSE(int outputIndex, DataSet* leftTest, DataSet *rightTest)
{
	float leftMSE = 0;
	float leftPred = 0;
	float rightMSE = 0;
	float rightPred = 0;
	float AvgMSE = 0;


	leftPred = AvgSum(outputIndex, leftTest, true);

	rightPred = AvgSum(outputIndex, rightTest, true);


	for (int k = 0; k < leftTest->nrOfInstances; k++)
	{
		float outValue = leftTest->data[k]->output[outputIndex];

		leftMSE += ((leftPred - outValue) * (leftPred - outValue));

	}
	leftMSE /= leftTest->nrOfInstances;
	leftMSE = sqrt(leftMSE);
	leftMSE /= leftPred;

	for (int k = 0; k < rightTest->nrOfInstances; k++)
	{
		float outValue = rightTest->data[k]->output[outputIndex];
		rightMSE += ((rightPred - outValue) * (rightPred - outValue));
	}
	rightMSE /= rightTest->nrOfInstances;
	rightMSE = sqrt(rightMSE);
	rightMSE /= rightPred;


	AvgMSE = ((rightMSE + leftMSE) / 2);

	return AvgMSE;

}

float CalcCovariance(int inputIndex, int outputIndex, DataSet *dataset)
{
	float covariance = 0;
	float meanX = 0;
	float meanY = 0;

	meanX = AvgSum(inputIndex, dataset, false);
	meanY = AvgSum(outputIndex, dataset, true);

	for (int i = 0; i < dataset->nrOfInstances; i++)
	{
		float cov = ((dataset->data[i]->input[inputIndex] - meanX) * (dataset->data[i]->output[outputIndex] - meanY));
		covariance += cov;
	}

	covariance /= (dataset->nrOfInstances - 1);

	return covariance;
}

float CalcCorrelation(int inputIndex, int outputIndex, DataSet *dataset, float covariance)
{
	float correlation = 0;

	float meanX = 0;
	float meanY = 0;
	float standardDevX = 0;
	float standardDevY = 0;

	meanX = AvgSum(inputIndex, dataset, false);
	meanY = AvgSum(outputIndex, dataset, true);

	for (int i = 0; i < dataset->nrOfInstances; i++)
	{
		standardDevX += (dataset->data[i]->input[inputIndex] - meanX) * (dataset->data[i]->input[inputIndex] - meanX);
		standardDevY += (dataset->data[i]->input[outputIndex] - meanY) * (dataset->data[i]->input[outputIndex] - meanY);
	}

	standardDevX /= (dataset->nrOfInstances - 1);
	standardDevY /= (dataset->nrOfInstances - 1);

	correlation = (covariance / (standardDevX * standardDevY));

	return correlation;
}

void Partition(float splitVal, int splitIndex, DataSet *currentData, DataSet *&leftData, DataSet *&rightData)
{
	std::vector<Instance*> tempLeft;
	std::vector<Instance*> tempRight;

	for (int i = 0; i < currentData->nrOfInstances; i++)
	{
		Instance *inst = currentData->data[i];

		if (inst->input[splitIndex] >= splitVal) //go right
		{
			tempRight.push_back(inst);
		}
		else //go left
		{
			tempLeft.push_back(inst);
		}
	}

	rightData = new DataSet(tempRight.size(), currentData->nrOfInputs, currentData->nrOfOutputs);
	for (int i = 0; i < (int)tempRight.size(); i++)
	{
		rightData->data[i] = tempRight[i];
	}

	leftData = new DataSet(tempLeft.size(), currentData->nrOfInputs, currentData->nrOfOutputs);
	for (int i = 0; i < (int)tempLeft.size(); i++)
	{
		leftData->data[i] = tempLeft[i];
	}
}
