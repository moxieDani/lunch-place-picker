#include "PlaceList.h"
#include <stdio.h>

PlaceList::PlaceList() :
	mName(NULL), mDesc(NULL), mFreq(0)
{
	mNext = NULL;
	mTotalPlaceNumber = -1;
}

PlaceList::PlaceList(char* name, char* desc, int freq) :
	mName(name), mDesc(desc), mFreq(freq)
{
	mNext = NULL;
	mTotalPlaceNumber = -1;
}

PlaceList::~PlaceList()
{
}
