#include "PlacePicker.h"	
#include <time.h>
#include <stdlib.h>

PlacePicker::PlacePicker(PlaceList* place)
{
	mPlaceList = place;
	mTotalPlaceNum = 0;
	for (PlaceList* list = place; list != NULL; list = list->mNext)
		mTotalPlaceNum++;
}

PlacePicker::~PlacePicker()
{
}

PlaceList* PlacePicker::pickLunchPlace()
{
	PlaceList* ret = NULL;
	PlaceList* nominee[5] = { NULL, };
	PlaceList* list = mPlaceList;
	int nomineeNum = mTotalPlaceNum < 5 ? mTotalPlaceNum : 5;
	int randomNumber = 0;

	srand(time(NULL));
	randomNumber = rand() % mTotalPlaceNum;
	for (int i = 0; i < nomineeNum; i++)
	{
		PlaceList* list = mPlaceList;
		randomNumber = rand() % mTotalPlaceNum;
		for (int j = 0; j < mTotalPlaceNum; j++)
			list = list->mNext;
		nominee[i]->mDesc = list->mDesc;
		nominee[i]->mName = list->mName;
		nominee[i]->mFreq = list->mFreq;

		for (int k = 0; k < i; k++)
			if (nominee[i] == nominee[k])
				i--;
	}
	
	randomNumber = rand() % nomineeNum;
	ret = nominee[randomNumber];
	for (int i = 0; i < nomineeNum; i++)
		if (ret->mFreq > nominee[i]->mFreq)
			ret = nominee[i];

	return ret;
}