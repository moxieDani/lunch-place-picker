#pragma once
#include "PlaceList.h"

class PlacePicker
{
public:
	PlacePicker(PlaceList* place);
	~PlacePicker();
	Place* pickLunchPlace();

private:
	PlaceList* mPlaceList;
	int mTotalPlaceNum;
};
