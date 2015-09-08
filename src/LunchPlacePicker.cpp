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
	while (!feof(fp))
	{
		fscanf(fp, "%d %s %s\n", &LunchPlace->frequency, LunchPlace->name, LunchPlace->desc);
		printf("%d %s %s\n", LunchPlace->frequency, LunchPlace->name, LunchPlace->desc);

		LunchPlace->pNext = (LunchPlaceInfo*)malloc(sizeof(LunchPlaceInfo));
		LunchPlace = LunchPlace->pNext;
		LunchPlace->pNext = NULL;
		total++;
	}
	printf("total count : %d\n", total);

	printf("init done\n");
	return 0;
}

char* pick()
{
	srand(time(NULL));
	
	LunchPlaceInfo* temp = gLunchPlace;
	return 0;
}

int add(char* name, char* desc)
{
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
	if (NULL != fp)
		fclose(fp);
	printf("exit start\n");
	
	while (gLunchPlace != NULL)
	{
		LunchPlaceInfo* temp = gLunchPlace->pNext;
		free(gLunchPlace);
		gLunchPlace = temp;
		
	}
	 
	printf("exit done\n"); 
	return 0;
}