#pragma once
#include "PlaceList.h"

class PlaceListManager
{
public:
	PlaceList* mPlaceList;
	PlaceList* mPlaceListHead;

public:
	PlaceListManager(PlaceList* placeList);
	~PlaceListManager();
	PlaceList* getPlaceList(int index);
	int addPlace(Place* place);
	int modifyPlace(int index, Place* place);
	int removePlace(int index);
	int getTotalPlaceNum();

private:
	int mTotalPlaceNum;

private:
	void countUpTotalPlaceNum();
	void countDownTotalPlaceNum();
};