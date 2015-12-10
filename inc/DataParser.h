#pragma once
#include "PlaceList.h"

class DataParser
{	
public:
	DataParser();
	~DataParser();
	PlaceList* parseData(char* data);

private:
	char* mLine;
	PlaceList* mParsedListTail;
	PlaceList* mParsedListHead;

private:
	char* getLine(char* data, int startOffset);
	PlaceList* parseLine(char* line);
	
};

