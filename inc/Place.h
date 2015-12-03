#pragma once

class Place
{	
public:
	char* mName;
	char* mDesc;
	int mFreq;
	Place* mNext;

public:
	Place();
	Place(char* name, char* desc, int freq);
	~Place();
	char* getName();
	char* getDesc();
	int getFreq();
};