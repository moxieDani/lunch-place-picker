#include "DataParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DataParser::DataParser()
{
	mParsedListHead = NULL;
	mParsedListTail = NULL;
}

DataParser::~DataParser()
{
}

char* DataParser::getLine(char* data, int startOffset)
{
	char* line = (char*)malloc(sizeof(char));
	int dataLegth = strlen(data);
	int lineLength = 1;

	for(int i = startOffset; i< dataLegth; i++)
	{
		if ('\n' == data[i]) break;

		lineLength++;
		line = (char*)realloc(line, sizeof(char)*lineLength);
		line[lineLength - 2] = data[i];
	}
	line[lineLength - 1] = '\0';
	return line;
}

PlaceList* DataParser::parseLine(char* line)
{
	char* outputDesc = NULL;
	char* outputName = NULL;
	int outputFreq = 0;
	PlaceList* ret = NULL;

	char* strDesc = (strDesc = strstr(line, ",<DESC>=")) ? strDesc + strlen(",<DESC>=") : NULL;
	char* strName = (strName = strstr(line, ",<NAME>=")) ? strName += strlen(",<NAME>=") : NULL;
	char* strFreq = (strFreq = strstr(line, "<FREQ>=")) ? strFreq += strlen("<FREQ>=") : NULL;
	
	if (strName && strDesc && strFreq)
	{
		*(strName + (strstr(line, ",<DESC>=") - strName)) = '\0';
		outputName = (char*)malloc(strlen(strName)+1);
		memcpy(outputName, strName, strlen(strName)+1);
	
		*(strFreq + (strstr(line, ",<NAME>=") - strFreq)) = '\0';
		outputDesc = (char*)malloc(strlen(strDesc)+1);
		memcpy(outputDesc, strDesc, strlen(strDesc)+1);
	
		outputFreq = atoi(strFreq);

		ret = new PlaceList(outputName, outputDesc, outputFreq);
	}

	if (line)
		free(line);

	return ret;
}

PlaceList* DataParser::parseData(char* data)
{
	int offset = 0;
	int dataLength = strlen(data);
	int totalParsedData = 0;

	while(offset < dataLength)
	{
		char* line = getLine(data, offset);
		offset += (strlen(line) + 1); //start position for next line

		if ( strlen(line) > 0)
		{
			totalParsedData++;
			mParsedListHead == NULL ? (mParsedListTail = mParsedListHead = parseLine(line)) : (mParsedListTail->mNext = parseLine(line));
			mParsedListTail = (NULL == mParsedListTail->mNext) ? mParsedListTail : mParsedListTail->mNext;
		}
	}
	mParsedListHead->mtotalPlaceNumber = totalParsedData;
	return mParsedListHead;
}