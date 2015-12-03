#pragma once
#include "Place.h"

class DataListManager
{
public:
	DataListManager();
	~DataListManager();
	Place* getPlaceList();
	int addPlace(Place* place);
	int modifyPlace(int index, Place* place);
	int removePlace(int index);

private:
	int mTotalPlaceNum;
	Place* mPlaceListHead;

private:
	void countUpTotalPlaceNum();
	void countDownTotalPlaceNum();
};