#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "LunchPlacePicker.h"

FILE *fp;
static LunchPlaceInfo* gLunchPlace = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));
static int total = 0;

int init(char* path)
{
	LunchPlaceInfo* LunchPlace = gLunchPlace;
	if (NULL == (fp = fopen(path, "r+")))
	{
		printf("File open error!\n");
		return -1;
	}

	printf("init start\n");
	while (1)
	{
		char* line = getLine();
		if ( 0 == strlen(line) ) { break; }
		setLunchPlaceInfo(line, LunchPlace);
		free(line);
		
		printf("FREQ(%d) NAME(%s) DESC(%s)\n", LunchPlace->frequency, LunchPlace->name, LunchPlace->desc);
		LunchPlace->pNext = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));
		LunchPlace = LunchPlace->pNext;
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
		if ( '\n' == buf || feof(fp) ) break;
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
	
	LunchPlaceInfo* temp = gLunchPlace;
	return 0;
}

int add(char* name, char* desc)
{
	LunchPlaceInfo* LunchPlace = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));
	
	LunchPlace->frequency = 0;
	LunchPlace->name = (char*)malloc(strlen(name)+1);
	memcpy(LunchPlace->name, name, strlen(name)+1);
	LunchPlace->desc = (char*)malloc(strlen(desc)+1);
	memcpy(LunchPlace->desc, desc, strlen(desc)+1);

	LunchPlace->pNext = gLunchPlace;
	gLunchPlace = LunchPlace;
	
	return 0;
}

int modify(int index, char* name, char* desc)
{
	return 0;
}

int remove(int index)
{
	return 0;
}

int save()
{
	return 0;
}

int exit()
{
	if ( NULL != fp) fclose(fp);

	printf("exit start\n");
	while ( NULL != gLunchPlace->pNext )
	{
		LunchPlaceInfo* temp = gLunchPlace->pNext;
		free(gLunchPlace->name);
		free(gLunchPlace->desc);
		free(gLunchPlace);
		gLunchPlace = NULL;
		gLunchPlace = temp;
	}
	printf("exit done\n"); 

	return 0;
}