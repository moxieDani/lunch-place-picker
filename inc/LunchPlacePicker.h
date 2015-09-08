#pragma once
typedef struct LunchPlaceInfo {
	char name[50];
	char desc[200];
	int frequency;
	LunchPlaceInfo* pNext = NULL;
}LunchPlaceInfo;

int init(char* path);

char* pick();

int add(char* name, char* desc="");

int modify(int index, char* name, char* desc);

int remove(int index);

int save();

int exit();