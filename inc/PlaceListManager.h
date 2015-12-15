#pragma once
#include "PlaceList.h"

class PlaceListManager
{
public:
	PlaceList* mPlaceList;
	PlaceList* mPlaceListHead;
	int mPlaceListNumber;

public:
	PlaceListManager();
	PlaceListManager(PlaceList* placeList);
	~PlaceListManager();
	PlaceList* getPlaceList(int index);
	int addPlace(PlaceList place);
	int modifyPlace(int index, PlaceList place);
	int removePlace(int index);
	int getTotalPlaceNum();

private:
	int copyPlace(PlaceList* dest, PlaceList src);
	int freeMemory(void *);
	void countUpTotalPlaceNum();
	void countDownTotalPlaceNum();
};