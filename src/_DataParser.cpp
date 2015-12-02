#include "_DataParser.h"
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
	Place temp;

	char* parsedDesc = (parsedDesc = strstr(line, ",<DESC>=")) ? parsedDesc + strlen(",<DESC>=") : NULL;
	char* parsedName = (parsedName = strstr(line, ",<NAME>=")) ? parsedName += strlen(",<NAME>=") : NULL;
	char* parsedFreq = (parsedFreq = strstr(line, "<FREQ>=")) ? parsedFreq += strlen("<FREQ>=") : NULL;
	

	if (parsedFreq && parsedName && parsedDesc)
	{
		parsedDesc;

		*(parsedName + (strstr(line, ",<DESC>=") - parsedName)) = '\0';
		temp.name = parsedName;

		*(parsedFreq + (strstr(line, ",<NAME>=") - parsedFreq)) = '\0';
		temp.freq = atoi(parsedFreq);
	}
	else
	{
		//printf("[Error] Parsing Error - FREQ(%s) NAME(%s) DESC(%s)\n", parsedFreq, parsedName, parsedDesc);
		free(line);
	}
	return temp;
}