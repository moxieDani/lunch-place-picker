#include "DataListManager.h"	
#include <stdlib.h>
#include <string.h>

/*************************************** public ***************************************/
DataListManager::DataListManager()
{
	mPlaceListHead = NULL;//(Place*)malloc(sizeof(Place));
	mPlaceListHead->mDesc = NULL;
	mPlaceListHead->mName = NULL;
	mPlaceListHead->mFreq = 0;
	mPlaceListHead->mNext = NULL;
	mTotalPlaceNum = 0;
}

DataListManager::~DataListManager()
{
}

Place* DataListManager::getPlaceList()
{
	return mPlaceListHead;
}

int DataListManager::addPlace(Place* place)
{
	for (Place* placeList = getPlaceList(); NULL != placeList; placeList = placeList->mNext)
	{
		if (NULL == placeList)
		{
			placeList = place;
			if (NULL == mPlaceListHead)
				mPlaceListHead = placeList;
			countUpTotalPlaceNum();
			break;
		}
	}
	return 0;
}

int DataListManager::modifyPlace(int index, Place* place)
{
	Place* placeList = getPlaceList();
	if (placeList)
	{
		for (int i = 0; i < index; i++)
			placeList = placeList->mNext;

		if ( placeList->mDesc )
			free(placeList->mDesc);
		if ( placeList->mName )
			free(placeList->mName);

		placeList->mDesc = place->mDesc;
		placeList->mName = place->mName;
	}
	return 0;
}

int DataListManager::removePlace(int index)
{
	Place* placeList = getPlaceList();
	Place* targetToRemove = NULL;
	
	if (0 > index || mTotalPlaceNum <= index)
		return -1;

	if (index == 0)
	{
		targetToRemove = mPlaceListHead;
		mPlaceListHead = mPlaceListHead->mNext;
	}

	for (int i = 1; i < mTotalPlaceNum + 1; i++)
	{
		if (i == index)
		{
			targetToRemove = placeList->mNext;
			placeList->mNext = targetToRemove->mNext;
			break;
		}
		placeList = placeList->mNext;
	}
	//printf("total count : %d\n", total);
	//printf("[delete] index(%d) FREQ(%d) NAME(%s) DESC(%s)\n",index, targetToRemove->freq, targetToRemove->name, targetToRemove->desc);

	free(targetToRemove->mName);
	targetToRemove->mName = NULL;
	free(targetToRemove->mDesc);
	targetToRemove->mDesc = NULL;
	free(targetToRemove);
	targetToRemove = NULL;
	countDownTotalPlaceNum();
}

/*************************************** private ***************************************/
void DataListManager::countUpTotalPlaceNum()
{
	mTotalPlaceNum++;
}

void DataListManager::countDownTotalPlaceNum()
{
	mTotalPlaceNum--;
}