#include "Place.h"
#include <stdio.h>
Place::Place()
{
}

Place::Place(char* name, char* desc, int freq) :
	mName(name), mDesc(desc), mFreq(freq)
{
	mNext = NULL;
}

Place::~Place()
{
}

char* Place::getName()
{
	return mName;
}

char* Place::getDesc()
{
	return mDesc;
}

int Place::getFreq()
{
	return mFreq;
}