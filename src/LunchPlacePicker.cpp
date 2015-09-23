#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "LunchPlacePicker.h"

FILE *fp;
static LunchPlaceInfo* gLunchPlaceHEAD = NULL;
static LunchPlaceInfo* gLunchPlaceTAIL = NULL;
static int total = 0;
static char* filePath;

int openFile(char* path)
{
	int ret = 0;
	filePath = path;
	if (NULL == (fp = fopen(path, "r+")))
	{
		printf("File not found / path : %s!\n", path);
		if (NULL == (fp = fopen(path, "w+")))
		{
			printf("File open error! / path : %s!\n", path);
			ret = -1;
		}
		else
			printf("New file created / path : %s!\n", path);
	}
	return ret;
}

int LoadFile(char* path)
{
	openFile(path);
	printf("Load data start\n");
	gLunchPlaceHEAD = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));
	gLunchPlaceHEAD->pNext = NULL;
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;

	while( !feof(fp) )
	{
		LunchPlaceInfo parsedData;
		char* line = (char*)malloc(sizeof(char) * 1);
		line = getLine(line);
		if (line[0] == '\0') continue;
		parsedData = getParsedData(line);
		
		if ( 0 <= parsedData.freq && parsedData.name && parsedData.desc)
		{
			insertLunchPlaceInfo(parsedData.name, parsedData.desc);
			getLunchPlaceInfo(total - 1)->freq = parsedData.freq;
		}
		free(line);
	}

	if (total == 0)
	{
		free(gLunchPlaceHEAD);
		gLunchPlaceHEAD = NULL;
	}

	printf("Load data end\n");
	return 0;
}

static char* getLine(char* line)
{
	char buf;
	int lineLength = 1;
	
	while (1)
	{
		buf = fgetc(fp);
		if ('\n' == buf || feof(fp)) break;
		lineLength++;

		line = (char*)realloc(line, sizeof(char)*lineLength);
		line[lineLength - 2] = buf;
	}
	line[lineLength - 1] = '\0';
	return line;
}

static LunchPlaceInfo getParsedData(char* line)
{
	LunchPlaceInfo temp = {NULL, NULL, -1};

	char* parsedDesc = parsedDesc = strstr(line, ",<DESC>=") + strlen(",<DESC>=");
	char* parsedName = (parsedName = strstr(line, ",<NAME>=")) ? parsedName += strlen(",<NAME>=") : NULL;
	char* parsedFreq = (parsedFreq = strstr(line, "<FREQ>=")) ? parsedFreq += strlen("<FREQ>=") : NULL;
	

	if (parsedFreq && parsedName && parsedDesc)
	{
		temp.desc = parsedDesc;
		*(parsedName + (strstr(line, ",<DESC>=") - parsedName)) = '\0';
		temp.name = parsedName;
		*(parsedFreq + (strstr(line, ",<NAME>=") - parsedFreq)) = '\0';
		temp.freq = atoi(parsedFreq);
	}
	else
	{
		printf("[Error] Parsing Error - FREQ(%s) NAME(%s) DESC(%s)\n", parsedFreq, parsedName, parsedDesc);
		free(line);
	}
	return temp;
}

LunchPlaceInfo* pickLunchPlace()
{
	int i = 0;
	int j = 0;
	int nodeCount = total;
	LunchPlaceInfo* nominee[5] = { NULL, };
	LunchPlaceInfo* ret = NULL;
	int randomNumber = 0;
	srand(time(NULL));
	if (nodeCount == 0) return NULL;
	for (i = 0; i < 5; i++)
	{
		if (nodeCount < 5)
			nominee[i] = getLunchPlaceInfo(i);
		else
		{
			randomNumber = rand() % nodeCount;
			nominee[i] = getLunchPlaceInfo(randomNumber);
			for (j = 0; j < i; j++)
				if (nominee[i] == nominee[j])
					i--;
		}
	}
	
	for (i = 0; i < (nodeCount < 5 ? nodeCount : 5); i++)
	{
		ret = nominee[i];
		for (j = 0; j < i; j++)
			if (nominee[i]->freq > nominee[j]->freq)
				ret = nominee[j];
	}
	ret->freq += 1;
	
	return ret;
}

LunchPlaceInfo* getLunchPlaceInfo(int index)
{
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;
	int i = 0;

	if (0 > index || total < index)
		return NULL;

	for (i = 0; i < total; i++)
	{
		if (index == i)
			return LunchPlace;

		LunchPlace = LunchPlace->pNext;
	}
	return LunchPlace;
}

int insertLunchPlaceInfo(char* name, char* desc)
{
	LunchPlaceInfo* LunchPlace = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));

	LunchPlace->freq = 0;
	LunchPlace->name = (char*)malloc(strlen(name) + 1);
	memset(LunchPlace->name, '\0', strlen(name) + 1);
	memcpy(LunchPlace->name, name, strlen(name));

	LunchPlace->desc = (char*)malloc(strlen(desc) + 1);
	memset(LunchPlace->desc, '\0', strlen(desc) + 1);
	memcpy(LunchPlace->desc, desc, strlen(desc));
	LunchPlace->pNext = NULL;

	if(total == 0)
	{
		free(gLunchPlaceHEAD);
		gLunchPlaceHEAD = LunchPlace;
		gLunchPlaceTAIL = gLunchPlaceHEAD;
	}
	else
	{
		gLunchPlaceTAIL->pNext = LunchPlace;
		gLunchPlaceTAIL = gLunchPlaceTAIL->pNext;
	}
	printf("[Insert] index(%d) FREQ(%d) NAME(%s) DESC(%s)\n", total, LunchPlace->freq, LunchPlace->name, LunchPlace->desc);
	total++;
	return 0;
}

int modifyLunchPlaceInfo(int index, char* name, char* desc)
{
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;
	int i = 0;

	if (0 > index || total < index)
		return -1;

	for (i = 0; i < total; i++)
	{
		if (index == i)
		{
			if (name)
			{
				free(LunchPlace->name);
				LunchPlace->name = NULL;
				LunchPlace->name = (char*)realloc(LunchPlace->name, strlen(name) + 1);
				memcpy(LunchPlace->name, name, strlen(name) + 1);
			}
			if (desc)
			{
				free(LunchPlace->desc);
				LunchPlace->desc = NULL;
				LunchPlace->desc = (char*)realloc(LunchPlace->desc, strlen(desc) + 1);
				memcpy(LunchPlace->desc, desc, strlen(desc) + 1);
			}
			printf("[modify] index(%d) FREQ(%d) NAME(%s) DESC(%s)\n", index, LunchPlace->freq, LunchPlace->name, LunchPlace->desc);
			break;
		}
		LunchPlace = LunchPlace->pNext;
	}
	return 0;
}

int deleteLunchPlaceInfo(int index)
{
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;
	LunchPlaceInfo* targetToRemove = NULL;
	int i = 0;

	if (0 > index || total <= index)
		return -1;
	
	if (index == 0)
	{
		targetToRemove = gLunchPlaceHEAD;
		gLunchPlaceHEAD = gLunchPlaceHEAD->pNext;
	}

	for (i = 1; i < total + 1; i++)
	{
		if (i == index)
		{
			targetToRemove = LunchPlace->pNext;
			LunchPlace->pNext = targetToRemove->pNext;
			break;
		}
		LunchPlace = LunchPlace->pNext;
	}
	printf("total count : %d\n", total);
	printf("[delete] index(%d) FREQ(%d) NAME(%s) DESC(%s)\n",index, targetToRemove->freq, targetToRemove->name, targetToRemove->desc);

	free(targetToRemove->name);
	targetToRemove->name = NULL;
	free(targetToRemove->desc);
	targetToRemove->desc = NULL;
	free(targetToRemove);
	targetToRemove = NULL;
	total--;
	return 0;
}

int saveLunchPlaceInfoToFile()
{
	if (NULL != fp) fclose(fp);

	fp = fopen(filePath,"w+");
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;

	while (NULL != LunchPlace)
	{
		fprintf(fp,"<FREQ>=%d,<NAME>=%s,<DESC>=%s\n", LunchPlace->freq, LunchPlace->name, LunchPlace->desc);
		LunchPlace = LunchPlace->pNext;
	}
	fclose(fp);
	printf("[save] Saved successfully\n");
	return 0;
}

int release()
{
	printf("release start\n");
	gLunchPlaceTAIL = NULL;
	if (total == 0)
	{
		free(gLunchPlaceHEAD);
		gLunchPlaceHEAD = NULL;
	}
	
	while (NULL != gLunchPlaceHEAD)
	{
		LunchPlaceInfo* temp = gLunchPlaceHEAD->pNext;
		free(gLunchPlaceHEAD->name);
		gLunchPlaceHEAD->name = NULL;
		free(gLunchPlaceHEAD->desc);
		gLunchPlaceHEAD->desc = NULL;
		free(gLunchPlaceHEAD);
		gLunchPlaceHEAD = temp;
	}
	printf("release done\n");
	return 0;
}

void closeFile()
{
	if (NULL != fp) fclose(fp);
}
