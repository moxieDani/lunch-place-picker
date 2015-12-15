#include "PlacePicker.h"	
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

PlacePicker::PlacePicker(PlaceList* place)
{
	mPlaceList = place;
	mTotalPlaceNum = 0;
	if(mPlaceList)
	{
		mTotalPlaceNum = mPlaceList->mTotalPlaceNumber;
		mPlaceList->mTotalPlaceNumber = mTotalPlaceNum;
	}
}

PlacePicker::~PlacePicker()
{
}

PlaceList* PlacePicker::pickLunchPlace()
{
	PlaceList* ret = NULL;
	PlaceList* nominee[5] = { NULL, };
	int nomineeNum = mTotalPlaceNum < 5 ? mTotalPlaceNum : 5;
	int randomNumber = 0;
	
	srand(time(NULL));
	for (int i = 0; i < nomineeNum; i++)
	{
		PlaceList* list = mPlaceList;
		if(NULL == nominee[i])
			randomNumber = rand() % mTotalPlaceNum;

		for (int j = 0; j < randomNumber; j++)
			list = list->mNext;
		nominee[i] = list;
		for (int k = 0; k < i; k++)
		{
			if (nominee[i] == nominee[k])
			{
				randomNumber = rand() % nomineeNum;
				i--;
			}
		}
	}

	randomNumber = rand() % nomineeNum;
	ret = nominee[randomNumber];
	for (int i = 0; i < nomineeNum; i++)
		if (ret->mFreq > nominee[i]->mFreq)
			ret = nominee[i];
	return ret;
}