#pragma once
#include "Place.h"

class PlaceList : public Place
{	
public:
	PlaceList* mNext;
	
public:
	PlaceList();
	~PlaceList();
};