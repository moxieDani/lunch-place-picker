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

int open(char* path)
{
	filePath = path;
	if (NULL == (fp = fopen(path, "r+")))
	{
		printf("File open error!\n");
		return -1;
	}
	return 0;
}

int init()
{
	printf("init start\n");
	gLunchPlaceHEAD = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));
	gLunchPlaceHEAD->pNext = NULL;
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;

	while( !feof(fp) )
	{
		char* line = (char*)malloc(sizeof(char) * 1);
		line = getLine(line);
		if (line[0] == '\0') continue;
		LunchPlaceInfo parsedData = getParsedData(line);
		add(parsedData.name, parsedData.desc, parsedData.frequency);
		free(line);
	}

	if (total == 0)
	{
		free(gLunchPlaceHEAD);
		gLunchPlaceHEAD = NULL;
	}

	printf("init done\n");
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
	LunchPlaceInfo temp;
	char* targetFreq = strdup(line);

	char* parsedFreq = strstr(line, "<FREQ>=") + 7;
	char* parsedName = strstr(line, ",<NAME>=") + 8;
	char* parsedDesc = strstr(line, ",<DESC>=") + 8;
	*( parsedFreq + (strstr(targetFreq, ",<NAME>=") - parsedFreq) ) = '\0';
	*( parsedName + (strstr(line, ",<DESC>=") - parsedName) ) = '\0';

	temp.frequency = atoi(parsedFreq);
	temp.name = parsedName;
	temp.desc = parsedDesc;
	
	free(targetFreq);
	return temp;
}

LunchPlaceInfo* pickLunchPlace()
{
	int i, j = 0;
	LunchPlaceInfo* nominee[5] = { NULL, };
	LunchPlaceInfo* ret = NULL;
	int randomNumber = 0;
	srand(time(NULL));
	if (total == 0) return NULL;
	for (i = 0; i < 5; i++)
	{
		if (total < 5)
			nominee[i] = getNode(i);
		else
		{
			randomNumber = rand() % total;
			nominee[i] = getNode(randomNumber);
			for (j = 0; j < i; j++)
				if (nominee[i] == nominee[j])
					i--;
		}
	}

	for (i = 0; i < (total < 5 ? total : 5); i++)
	{
		ret = nominee[i];
		for (j = 0; j < i; j++)
			if (nominee[i]->frequency > nominee[j]->frequency)
				ret = nominee[j];
	}
	ret->frequency += 1;
	printf("[pick] \"%s\" has been picked!\n", ret->name);
	return ret;
}

LunchPlaceInfo* getNode(int index)
{
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;
	if (0 > index || total < index)
		return NULL;

	for (int i = 0; i < total; i++)
	{
		if (index == i)
		{
			printf("[getNode] index(%d) FREQ(%d) NAME(%s) DESC(%s)\n", index, LunchPlace->frequency, LunchPlace->name, LunchPlace->desc);
			return LunchPlace;
		}
		LunchPlace = LunchPlace->pNext;
	}
	return LunchPlace;
}

int add(char* name, char* desc, int freq)
{
	LunchPlaceInfo* LunchPlace = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));

	LunchPlace->frequency = freq;
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
	printf("[add] FREQ(%d) NAME(%s) DESC(%s)\n", LunchPlace->frequency, LunchPlace->name, LunchPlace->desc);
	total++;
	printf("total count : %d\n", total);
	return 0;
}

int modify(int index, char* name, char* desc)
{
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;

	if (0 > index || total < index)
		return -1;

	for (int i = 0; i < total; i++)
	{
		if (index == i)
		{
			free(LunchPlace->name);
			LunchPlace->name = NULL;
			LunchPlace->name = (char*)realloc(LunchPlace->name, strlen(name) + 1);
			memcpy(LunchPlace->name, name, strlen(name) + 1);

			free(LunchPlace->desc);
			LunchPlace->desc = NULL;
			LunchPlace->desc = (char*)realloc(LunchPlace->desc, strlen(desc) + 1);
			memcpy(LunchPlace->desc, desc, strlen(desc) + 1);

			printf("[modify] index(%d) FREQ(%d) NAME(%s) DESC(%s)\n", index, LunchPlace->frequency, LunchPlace->name, LunchPlace->desc);
			break;
		}
		LunchPlace = LunchPlace->pNext;
	}
	return 0;
}

int remove(int index)
{
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;
	LunchPlaceInfo* targetToRemove = NULL;
	if (0 > index || total <= index)
		return -1;
	
	if (index == 0)
	{
		targetToRemove = gLunchPlaceHEAD;
		gLunchPlaceHEAD = gLunchPlaceHEAD->pNext;
	}

	for (int i = 1; i < total + 1; i++)
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
	printf("[remove] index(%d) FREQ(%d) NAME(%s) DESC(%s)\n",index, targetToRemove->frequency, targetToRemove->name, targetToRemove->desc);

	free(targetToRemove->name);
	targetToRemove->name = NULL;
	free(targetToRemove->desc);
	targetToRemove->desc = NULL;
	free(targetToRemove);
	targetToRemove = NULL;
	total--;
	return 0;
}

int save()
{
	if (NULL != fp) fclose(fp);

	fp = fopen(filePath,"w+");
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;
	while (NULL != LunchPlace)
	{
		fprintf(fp,"<FREQ>=%d,<NAME>=%s,<DESC>=%s\n", LunchPlace->frequency, LunchPlace->name, LunchPlace->desc);
		LunchPlace = LunchPlace->pNext;
	}
	fclose(fp);
	return 0;
}

int deinit()
{
	printf("deinit start\n");
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
	printf("deinit done\n");
	return 0;
}

void close()
{
	if (NULL != fp) fclose(fp);
}

LunchPlaceInfo* temp()
{
	LunchPlaceInfo* temp = gLunchPlaceHEAD;
	return temp;
}