#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "FileManager.h"
#include "DataParser.h"
#include "PlaceList.h"
#include "PlaceListManager.h"
#include "PlacePicker.h"

void printNode();
/*
bool mainMenu();
void nodeSetting();
void saveNode();
*/
void clearEnter();


void printNode(PlaceList* placeList)
{
	int i = 1;
	for(PlaceList* list = placeList; list != NULL; list = list->mNext)
		printf("%03d. %s - (%03d) %s\n", i++, list->mName, list->mFreq, list->mDesc);
	printf("Total Place Number : %d\n", placeList ? placeList->mTotalPlaceNumber : 0);
	printf("\n");
}

int main(int argc, char* argv[])
{
	const char* path = argv[1] ? argv[1] : "lunch-place-info.txt";
	FileManager fileReader(path, "r");
	DataParser fileParser = DataParser();
	PlaceListManager listManager = PlaceListManager(fileParser.parseData(fileReader.getData(0, fileReader.getFileSize())));
	PlacePicker picker = PlacePicker(listManager.getPlaceList(1));
	PlaceList* ret = NULL;

	int selectNum;
	while(1)
	{
		printf("\n\n** Lunch Place Picker **\n");
		printf(" [] Select Menu\n");
		printf("   1. Pick lunch place\n");
		printf("   2. Show all lunch places\n");
		printf("   3. Exit\n");
		printf(" [] input : ");
		scanf("%d",&selectNum);
		clearEnter();
		system("printf '\033\143'");
		switch (selectNum)
		{
		case 1:
			ret = picker.pickLunchPlace();
			if(ret)
				printf("\n[result] %s - (%03d) %s\n", ret->mName, ret->mFreq, ret->mDesc);
			else
				printf("\n[result] There is no lunch place!\n");
			break;
		case 2:
			printf("\n");
			printNode(listManager.getPlaceList(1));
			break;
		case 3:
			return 0;
			break;
		default:
			printf("\n");
			printf(" [] Invalid number\n");
			break;
		}
		system("read -n1 -s -p \"\nPress any key to continue...\" key");
		system("printf '\033\143'");
	}
	return 0;
}
/*
bool mainMenu()
{
	int selectNum = 0;
	LunchPlaceInfo* lunchPlace = NULL;
	printf("** Lunch Place Picker **\n");
	printf(" [] Select Menu\n");
	printf("   1. Pick lunch place\n");
	printf("   2. Node setting\n");
	printf("   3. Show lunch place list\n");
	printf("   4. Save lunch place info to file\n");
	printf("   5. Exit\n");
	printf(" [] input : ");
	scanf("	 %d",&selectNum);
	clearEnter();
	switch (selectNum)
	{
	case 1:
		lunchPlace = pickLunchPlace();
		if(lunchPlace)
			printf("[result] Lunch Place information : NAME(%s) / DESC(%s)\n", lunchPlace->name, lunchPlace->desc);
		else
			printf("[result] There is no lunch place!\n");
		saveLunchPlaceInfoToFile();
		break;
	case 2:
		nodeSetting();
		break;
	case 3:
		printNode();
		break;
	case 4:
		saveNode();
		printNode();
		break;
	case 5:
		saveNode();
		release();
		closeFile();
		exit(1);
	default:
		printf(" [] Invalid number\n");
		break;
	}
	printf("\n");
}

void nodeSetting()
{
	int selectNum = 0;
	int targetIndex = 0;
	char name[100] = { '\0', };
	char desc[400] = { '\0', };
	printNode();
	printf(" [] Node setting\n");
	printf("   1. Insert node\n");
	printf("   2. Modify node\n");
	printf("   3. Delete node\n");
	printf("   4. Save node to file\n");
	printf("   5. Back to main menu\n");
	printf(" [] input : ");
	scanf("	 %d", &selectNum);
	clearEnter();
	switch (selectNum)
	{
	case 1:
		printf(" [Insert] Name : ");
		scanf("%99[^\n]s", name);
		clearEnter();
		printf(" [Insert] Description : ");
		scanf("%399[^\n]s", desc);
		clearEnter();
		insertLunchPlaceInfo(name, desc);
		printNode();
		break;
	case 2:
		printf(" [Modify] Target index : ");
		scanf("%d", &targetIndex);
		clearEnter();
		printf(" [Modify] Name : ");
		scanf("%99[^\n]s", name);
		clearEnter();
		printf(" [Modify] Description : ");
		scanf("%399[^\n]s", desc);
		clearEnter();
		modifyLunchPlaceInfo(targetIndex, name, desc);
		printNode();
		break;
	case 3:
		printf(" [Delete] Target index : ");
		scanf("%d", &targetIndex);
		clearEnter();
		deleteLunchPlaceInfo(targetIndex);
		printNode();
		break;
	case 4:
	default:
		mainMenu();
		break;
	}
}

void saveNode()
{
	char ch;
	printf(" [Save] Save Lunch place info to file(y/n)?");
	scanf("%c", &ch);
	clearEnter();
	if( 'y' == ch || 'Y' == ch)
	{
		printf(" [Save] Saving... \n");
		saveLunchPlaceInfoToFile();
		printNode();
	}
	else if ( 'n' == ch || 'N' == ch) { ; }
	else
	{
		printf(" [Error] Invalid value\n");
		saveNode();
	}
}
*/
void clearEnter()
{
	while (getchar() != '\n');
}
