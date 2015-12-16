#include "Engine.h"
#include "FileManager.h"
#include "DataParser.h"
#include "PlaceList.h"
#include "PlaceListManager.h"
#include "PlacePicker.h"

Engine::Engine()
{
	mFileReader = new FileManager("lunch-place-info.txt", "r");
	mDataParser = new DataParser();
	mPlaceListManager = new PlaceListManager(mDataParser->parseData(mFileReader->getData(0, mFileReader->getFileSize())));
	mPlaceListHead = mPlaceListManager->getPlaceList(1);
	mPlacePicker = new PlacePicker(mPlaceListHead);
}

Engine::Engine(char* filePath)
{
	mFilePath = filePath ? filePath : "lunch-place-info.txt";
	mFileReader = new FileManager(mFilePath, "r");
	mDataParser = new DataParser();
	mPlaceListManager = new PlaceListManager(mDataParser->parseData(mFileReader->getData(0, mFileReader->getFileSize())));
	mPlaceListHead = mPlaceListManager->getPlaceList(1);
	mPlacePicker = new PlacePicker(mPlaceListHead);
}

Engine::~Engine()
{
	delete mFileReader;
	delete mDataParser;
	delete mPlaceListManager;
	delete mPlacePicker;
}

PlaceList* Engine::pickPlace()
{
	PlaceList* ret = NULL;
	if(mPlacePicker)
		ret = mPlacePicker->pickLunchPlace();
	return ret;
}

int Engine::addPlace(PlaceList placeList)
{
	int ret = -1;
	if(mPlaceListManager)
		ret = mPlaceListManager->addPlace(placeList);
	return ret;
}

int Engine::modifyPlace(int index, PlaceList placeList)
{
	int ret = -1;
	if(mPlaceListManager)
		ret = mPlaceListManager->modifyPlace(index, placeList);
	return ret;
}

int Engine::removePlace(int index)
{
	int ret = -1;
	if(mPlaceListManager)
		ret = mPlaceListManager->removePlace(index);
	return ret;
}

int Engine::getTotalPlaceNumber()
{
	int ret = -1;
	if(mPlaceListManager)
		ret = mPlaceListManager->getTotalPlaceNum();
	return ret;
}

int Engine::savePlaceListToFile()
{
	int ret = -1;
	delete mFileReader;
	FileManager writer(mFilePath, "w+");
	for(PlaceList* list = mPlaceListHead; list != NULL; list = list->mNext)
	{
		ret = writer.write("<FREQ>=%d,<NAME>=%s,<DESC>=%s\n", list->mFreq, list->mName, list->mDesc);
		printf("write success!\n");
	}
	return ret;
}