#include "PlaceList.h"
#include <stdio.h>

PlaceList::PlaceList()
{
}

PlaceList::PlaceList(char* name, char* desc, int freq) :
	mName(name), mDesc(desc), mFreq(freq)
{
	mNext = NULL;
	mtotalPlaceNumber = -1;
}

PlaceList::~PlaceList()
{
}
