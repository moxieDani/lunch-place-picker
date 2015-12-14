#pragma once

class PlaceList
{	
public:
	char* mName;
	char* mDesc;
	int mFreq;
	PlaceList* mNext;
	int mTotalPlaceNumber;
public:
	PlaceList();
	PlaceList(char* name, char* desc, int freq);
	~PlaceList();
};