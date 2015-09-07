#include <stdio.h>
#include "LunchPlacePicker.h"

FILE *fp;
LunchPlaceInfo* gLunchPlace;

int init(char* path)
{
	if (NULL == (fp = fopen(path, "r+")) )
		return -1;
	return 0;
}

char* pick()
{
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
	return 0;
}