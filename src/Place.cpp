#include "Place.h"
#include <stdio.h>
Place::Place()
{
}

Place::Place(char* name, char* desc, int freq) :
	mName(name), mDesc(desc), mFreq(freq)
{
}

Place::~Place()
{
}
