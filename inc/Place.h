#pragma once

class Place
{	
public:
	char* mName;
	char* mDesc;
	int mFreq;

public:
	Place();
	Place(char* name, char* desc, int freq);
	~Place();
};