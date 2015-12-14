#include "PlaceListManager.h"	
#include <stdlib.h>
#include <string.h>

/*************************************** public ***************************************/
PlaceListManager::PlaceListManager()
{
	mPlaceList = new PlaceList();
	mPlaceList->mTotalPlaceNumber = 0;
}

PlaceListManager::PlaceListManager(PlaceList* placeList)
{
	mPlaceList = placeList;
	mPlaceList->mTotalPlaceNumber = placeList->mTotalPlaceNumber;
}

PlaceListManager::~PlaceListManager()
{
	PlaceList* placeList = getPlaceList(1);
	while(placeList)
	{
		PlaceList* targetToRemove = placeList;
		
		placeList = placeList->mNext;
		freeMemory(targetToRemove->mDesc);
		freeMemory(targetToRemove->mName);
		freeMemory(targetToRemove);
	}
}

PlaceList* PlaceListManager::getPlaceList(int index)
{
	PlaceList* ret = NULL;
	if (0 <= index && index <= getTotalPlaceNum())
	{
		ret = mPlaceList;
		for (int i = 1; i < index; i++)
			ret = ret->mNext;
	}
	
	return ret;
}

int PlaceListManager::addPlace(PlaceList place)
{
	int totalPlaceNum = getTotalPlaceNum();
	PlaceList* placeList = new PlaceList();
	int ret = copyPlace(placeList, place);
	
	if( 0 == ret )
	{
		PlaceList* targetPlaceList = NULL;
		if (0 == totalPlaceNum)
		{
			mPlaceList = placeList;
			mPlaceList->mTotalPlaceNumber = 0;
		}
		else
		{
			targetPlaceList = getPlaceList(totalPlaceNum);
			targetPlaceList->mNext = placeList;
		}
		countUpTotalPlaceNum();
	}
	else
		ret = -1;

	return ret;
}

int PlaceListManager::modifyPlace(int index, PlaceList place)
{
	int ret = -1;
	
	if (0 <= index && index <= getTotalPlaceNum())
	{
		PlaceList* placeList = getPlaceList(index);
		ret = copyPlace(placeList, place);
	}

	return ret;
}

int PlaceListManager::removePlace(int index)
{
	int ret = 0;
	PlaceList* targetToRemove = NULL;
	
	if (0 <= index && index <= getTotalPlaceNum())
	{
		targetToRemove = getPlaceList(index);
		if (index == 0)
			mPlaceList = mPlaceList->mNext;
		else
			getPlaceList(index - 1)->mNext = targetToRemove->mNext;
		freeMemory(targetToRemove->mName);
		freeMemory(targetToRemove->mDesc);
		freeMemory(targetToRemove);
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
	int ret = 0;

	if (mPlaceList)
		ret = mPlaceList->mTotalPlaceNumber;

	return ret;
}

/*************************************** private ***************************************/
int PlaceListManager::copyPlace(PlaceList* dest, PlaceList src)
{
	if (NULL == dest)
		dest = new PlaceList(src.mName, src.mDesc, src.mFreq);
	else
	{
		if (src.mName)
		{
			freeMemory(dest->mName);
			char* name = (char*)malloc(strlen(src.mName)+1);
			strncpy(name, src.mName, strlen(src.mName)+1);
			dest->mName = name;
		}
		if (src.mDesc)
		{
			freeMemory(dest->mDesc);
			char* desc = (char*)malloc(strlen(src.mDesc)+1);
			strncpy(desc, src.mDesc, strlen(src.mDesc)+1);
			dest->mDesc = desc;
		}
		dest->mFreq = src.mFreq;
	}
	return 0;
}

int PlaceListManager::freeMemory(void *target)
{
	if(target)
		free(target);
	target = NULL;

	return 0;
}

void PlaceListManager::countUpTotalPlaceNum()
{
	mPlaceList->mTotalPlaceNumber++;
}

void PlaceListManager::countDownTotalPlaceNum()
{
	mPlaceList->mTotalPlaceNumber--;
}

