#pragma once
class FileManager;
class DataParser;
class PlaceListManager;
class PlacePicker;
class PlaceList;

class Engine
{
public:
	FileManager* mFileReader;
	DataParser* mDataParser;
	PlaceListManager* mPlaceListManager;
	PlacePicker* mPlacePicker;
	PlaceList* mPlaceListHead;
	char* mFilePath;
public:
	Engine();
	Engine(char* srcPath);
	~Engine();
	PlaceList* pickPlace();
	int addPlace(PlaceList placeList);
	int modifyPlace(int index, PlaceList placeList);
	int removePlace(int index);
	int getTotalPlaceNumber();
	int savePlaceListToFile();
};

