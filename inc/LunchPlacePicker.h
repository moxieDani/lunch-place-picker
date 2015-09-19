#pragma once
typedef struct LunchPlaceInfo {
	char* name;
	char* desc;
	int frequency;
	LunchPlaceInfo* pNext;
}LunchPlaceInfo;

/*

*/
int open(char* path);

int init();

static char* getLine(char* line);

static LunchPlaceInfo getParsedData(char* line);

LunchPlaceInfo* pickLunchPlace();

LunchPlaceInfo* getNode(int index);

int add(char* name, char* desc, int freq = 0);

int modify(int index, char* name, char* desc);

int remove(int index);

int save();

int deinit();

void close();

LunchPlaceInfo* temp();