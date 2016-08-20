#ifndef ISPLITTER_H
#define ISPLITTER_H

#include "Utils.h"
#include "Node.h"

class ISplitter
{
public:
	ISplitter(){};
	~ISplitter(){};

	virtual SplitInfo ConsiderSplit(DataSet *currentDataSet) = 0;

private:
	

};

#endif