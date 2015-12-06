#include "PlaceListManager.h"	
#include <stdlib.h>
#include <string.h>

/*************************************** public ***************************************/
PlaceListManager::PlaceListManager(PlaceList* placeList)
{
	mPlaceList = placeList;
	mPlaceList->mNext = NULL;
	mTotalPlaceNum = 0;
}

PlaceListManager::~PlaceListManager()
{
	for (PlaceList* placeList = getPlaceList(0); NULL != placeList; placeList = placeList->mNext)
	{
		free(mPlaceList->mDesc);
		free(mPlaceList->mName);
		free(mPlaceList);
		mPlaceList->mDesc = NULL;
		mPlaceList->mName = NULL;
		mPlaceList = NULL;
	}
}

PlaceList* PlaceListManager::getPlaceList(int index)
{
	PlaceList* ret = mPlaceList;
	if (0 > index || getTotalPlaceNum() < index)
		ret = NULL;
	else
	{
		for (int i = 0; i < index; i++)
			ret = ret->mNext;
	}
	return ret;
}

int PlaceListManager::addPlace(Place* place)
{
	int totalPlaceNum = getTotalPlaceNum();
	
	for (PlaceList* placeList = getPlaceList(0); NULL != placeList; placeList = placeList->mNext)
	{
		if (NULL == placeList)
		{
			placeList->mDesc = place->mDesc;
			placeList->mName = place->mName;
			placeList->mFreq = 0;
			countUpTotalPlaceNum();
		}
	}
	return 0;
}

int PlaceListManager::modifyPlace(int index, Place* place)
{
	int ret = 0;
	PlaceList* placeList = NULL;

	if (0 <= index && index <= mTotalPlaceNum)
	{
		placeList = getPlaceList(index);
		if (placeList->mDesc)
			free(placeList->mDesc);
		if (placeList->mName)
			free(placeList->mName);

		placeList->mDesc = place->mDesc;
		placeList->mName = place->mName;
	}
	else
		ret = -1;
	return ret;
}

int PlaceListManager::removePlace(int index)
{
	int ret = 0;
	PlaceList* targetToRemove = NULL;
	
	if (0 <= index && index <= mTotalPlaceNum)
	{
		targetToRemove = getPlaceList(index);
		if (index == 0)
			mPlaceList = mPlaceList->mNext;
		else
			getPlaceList(index - 1)->mNext = targetToRemove->mNext;
		free(targetToRemove->mName);
		targetToRemove->mName = NULL;
		free(targetToRemove->mDesc);
		targetToRemove->mDesc = NULL;
		free(targetToRemove);
		targetToRemove = NULL;
		countDownTotalPlaceNum();
		//printf("total count : %d\n", total);
		//printf("[delete] index(%d) FREQ(%d) NAME(%s) DESC(%s)\n",index, targetToRemove->freq, targetToRemove->name, targetToRemove->desc);
	}
	else
		ret = -1;

	return ret;
}
int PlaceListManager::getTotalPlaceNum()
{
	return mTotalPlaceNum;
}

/*************************************** private ***************************************/
void PlaceListManager::countUpTotalPlaceNum()
{
	mTotalPlaceNum++;
}

void PlaceListManager::countDownTotalPlaceNum()
{
	mTotalPlaceNum--;
}

