#pragma once

class PlaceList
{	
public:
	char* mName;
	char* mDesc;
	int mFreq;
	PlaceList* mNext;
	int mtotalPlaceNumber;
public:
	PlaceList();
	PlaceList(char* name, char* desc, int freq);
	~PlaceList();
};