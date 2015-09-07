#pragma once
typedef struct LunchPlaceInfo {
	char* name;
	char* desc;
	int frequency = 0;
	LunchPlaceInfo* pNext = NULL;
};

int init(char* path);

char* pick();

int add(char* name, char* desc="");

int modify(int index, char* name, char* desc);

int remove(int index);

int save();

int exit();