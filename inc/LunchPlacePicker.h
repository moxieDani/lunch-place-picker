#pragma once
typedef struct LunchPlaceInfo {
	char* name;
	char* desc;
	int frequency;
	LunchPlaceInfo* pNext;
}LunchPlaceInfo;

int init(char* path);

static char* getLine();

static void setLunchPlaceInfo(char* line, LunchPlaceInfo* LunchPlace);

char* pick();

int add(char* name, char* desc="");

int modify(int index, char* name, char* desc);

int remove(int index);

int save();

int exit();

LunchPlaceInfo* temp();