#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "LunchPlacePicker.h"

FILE *fp;
static LunchPlaceInfo* gLunchPlaceHEAD = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));
static LunchPlaceInfo* gLunchPlaceTAIL;
static int total = 0;

int init(char* path)
{
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;
	if (NULL == (fp = fopen(path, "r+")))
	{
		printf("File open error!\n");
		return -1;
	}

	printf("init start\n");
	while (1)
	{
		char* line = getLine();
		if (0 == strlen(line)) { break; }
		setLunchPlaceInfo(line, LunchPlace);
		free(line);

		printf("[init] FREQ(%d) NAME(%s) DESC(%s)\n", LunchPlace->frequency, LunchPlace->name, LunchPlace->desc);
		if ( !feof(fp) )
		{
			
			LunchPlace->pNext = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));
			LunchPlace = LunchPlace->pNext;
		}
		gLunchPlaceTAIL = LunchPlace;
		LunchPlace->pNext = NULL;
		total++;
	}
	printf("total count : %d\n", total);

	printf("init done\n");
	return 0;
}

static char* getLine()
{
	char buf;
	int lineLength = 1;
	char* line = (char*)malloc(sizeof(char) * lineLength);
	while (1)
	{
		fread(&buf, 1, 1, fp);
		if ('\n' == buf || feof(fp)) break;
		lineLength++;

		line = (char*)realloc(line, sizeof(char)*lineLength);
		line[lineLength - 2] = buf;
	}
	line[lineLength - 1] = '\0';

	return line;
}

static void setLunchPlaceInfo(char* line, LunchPlaceInfo* LunchPlace)
{
	LunchPlace->frequency = atoi(strtok(line, "<FREQ>="));

	line = strtok(NULL, ",<NAME>=");
	LunchPlace->name = (char*)malloc(sizeof(char) * strlen(line) + 1);
	memset(LunchPlace->name, '\0', strlen(line) + 1);
	memcpy(LunchPlace->name, line, strlen(line));

	line = strtok(NULL, ",<DESC>=");
	LunchPlace->desc = (char*)malloc(sizeof(char) * strlen(line) + 1);
	memset(LunchPlace->desc, '\0', strlen(line) + 1);
	memcpy(LunchPlace->desc, line, strlen(line));

}

char* pick()
{
	srand(time(NULL));

	LunchPlaceInfo* temp = gLunchPlaceHEAD;
	return 0;
}

int add(char* name, char* desc)
{
	LunchPlaceInfo* LunchPlace = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));

	LunchPlace->frequency = 0;
	LunchPlace->name = (char*)malloc(strlen(name) + 1);
	memcpy(LunchPlace->name, name, strlen(name) + 1);
	LunchPlace->desc = (char*)malloc(strlen(desc) + 1);
	memcpy(LunchPlace->desc, desc, strlen(desc) + 1);
	LunchPlace->pNext = NULL;

	printf("[add] FREQ(%d) NAME(%s) DESC(%s)\n", LunchPlace->frequency, LunchPlace->name, LunchPlace->desc);

	gLunchPlaceTAIL->pNext = LunchPlace;
	gLunchPlaceTAIL = gLunchPlaceTAIL->pNext;
	total++;
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

			printf("[modify] FREQ(%d) NAME(%s) DESC(%s)\n", LunchPlace->frequency, LunchPlace->name, LunchPlace->desc);
			break;
		}
		LunchPlace = LunchPlace->pNext;
	}
	return 0;
}

int remove(int index)
{
	LunchPlaceInfo* LunchPlace = gLunchPlaceHEAD;
	LunchPlaceInfo* targetToRemove;
	if (0 > index || total < index)
		return -1;

	for (int i = 1; i < total; i++)
	{
		
		if (index == 0)
		{
			targetToRemove = gLunchPlaceHEAD;
			gLunchPlaceHEAD = gLunchPlaceHEAD->pNext;
			break;
		}
		else if (index == i)
		{
			targetToRemove = LunchPlace->pNext;
			LunchPlace->pNext = targetToRemove->pNext;
			break;
		}
		//gLunchPlaceTAIL = LunchPlace->pNext == NULL ? LunchPlace : gLunchPlaceTAIL;
		LunchPlace = LunchPlace->pNext;
	}
	printf("[remove] FREQ(%d) NAME(%s) DESC(%s)\n", targetToRemove->frequency, targetToRemove->name, targetToRemove->desc);

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
	return 0;
}

int exit()
{
	if (NULL != fp) fclose(fp);

	printf("exit start\n");
	while (NULL != gLunchPlaceHEAD->pNext)
	{
		LunchPlaceInfo* temp = gLunchPlaceHEAD->pNext;
		free(gLunchPlaceHEAD->name);
		gLunchPlaceHEAD->name = NULL;
		free(gLunchPlaceHEAD->desc);
		gLunchPlaceHEAD->desc = NULL;
		free(gLunchPlaceHEAD);
		gLunchPlaceHEAD = NULL;
		gLunchPlaceHEAD = temp;
	}
	printf("exit done\n");

	return 0;
}

LunchPlaceInfo* temp()
{
	LunchPlaceInfo* temp = gLunchPlaceHEAD;
	return temp;
}