#pragma once
#include "Place.h"

class DataParser
{
public:
	DataParser();
	~DataParser();
	
private:
	char* mLine;

private:
	char* getLine(char* data, int startOffset);
	Place parseLine(char* line);
};

