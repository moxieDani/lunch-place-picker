#include "DataParser.h"
#include <stdlib.h>
#include <string.h>

DataParser::DataParser()
{
}

DataParser::~DataParser()
{
}

char* DataParser::getLine(char* data, int startOffset)
{
	char* line = (char*)malloc(sizeof(char));
	char buf;
	int lineLength = 1;
	int i;

	for(i = startOffset; i< sizeof(data); i++)
	{
		buf = data[startOffset];
		if ('\n' == buf) break;

		lineLength++;line = (char*)realloc(line, sizeof(char)*lineLength);
		line[lineLength - 2] = buf;
	}
	line[lineLength - 1] = '\0';
	return line;
}

Place DataParser::parseLine(char* line)
{
	char* strDesc = (strDesc = strstr(line, ",<DESC>=")) ? strDesc + strlen(",<DESC>=") : NULL;
	char* strName = (strName = strstr(line, ",<NAME>=")) ? strName += strlen(",<NAME>=") : NULL;
	char* strFreq = (strFreq = strstr(line, "<FREQ>=")) ? strFreq += strlen("<FREQ>=") : NULL;
	
	if (strName)
		*(strName + (strstr(line, ",<DESC>=") - strName)) = '\0';
	if (strDesc)
		*(strFreq + (strstr(line, ",<NAME>=") - strFreq)) = '\0';
	
	char* outputDesc = (char*)malloc(strlen(strDesc)+1);
	char* outputName = (char*)malloc(strlen(strName)+1);
	int outputFreq = 0;
	memcpy(outputDesc, strDesc, strlen(strDesc)+1);
	memcpy(outputName, strName, strlen(strName)+1);
	outputFreq = atoi(strFreq);

	if (line)
		free(line);

	Place place(outputDesc, outputName, outputFreq);
	return place;
}