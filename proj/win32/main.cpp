#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#include "Engine.h"
#include "PlaceList.h"

void printNode(PlaceList* placeList);
int mainMenu(Engine* engine);
int settingsMenu(Engine* engine);
bool selectPlaceMenu();
bool pickPlaceMenu(PlaceList* ret);

void clearEnter();


void printNode(PlaceList* placeList)
{
	int i = 1;
	for(PlaceList* list = placeList; list != NULL; list = list->mNext)
		printf("%03d. %s - %s(%d times selected.)\n", i++, list->mName, list->mDesc, list->mFreq);
	printf("\nTotal Place Number : %d\n", placeList ? i : 0);
}

int main(int argc, char* argv[])
{
	const char* path = argv[1] ? argv[1] : "lunch-place-info.txt";
	Engine* engine = new Engine(path);
	
	while(1 != mainMenu(engine)) {}
	return 0;
}

int mainMenu(Engine* engine)
{
	int ret = 0;
	PlaceList* pickedPlace;
	int selectNum;
	bool isPlaceChanged = false;
		
	system("cls");
	printf("\n\n** Lunch Place Picker **\n");
	printf(" [] Select Menu\n");
	printf("   1. Pick lunch place\n");
	printf("   2. Show all lunch places\n");
	printf("   3. Settings\n");
	printf("   4. Exit\n");
	printf(" [] input : ");
	scanf("	 %d",&selectNum);
	clearEnter();
	system("cls");
	switch (selectNum)
	{
	case 1:
		pickedPlace = engine->pickPlace();
		if(pickPlaceMenu(pickedPlace))
		{
			if(selectPlaceMenu())
			{
				pickedPlace->mFreq++;
				isPlaceChanged = true;
			}
		}
		break;
	case 2:
		printf("\n");
		printNode(engine->mPlaceListHead);
		break;
	case 3:
		while(1 >= (ret = settingsMenu(engine))) {}
		isPlaceChanged = true;
		break;
	case 4:
		if(isPlaceChanged)
			engine->savePlaceListToFile();
		ret = 1;
		break;
	default:
		printf("\n");
		printf(" [] Invalid number\n");
		break;
	}
	printf("\n");
	if(0 == ret)
		system("pause");
	
	return ret;
}

int settingsMenu(Engine* engine)
{
	int ret = 0;
	int selectNum = 0;
	int targetIndex = 0;
	char* name = (char*)malloc(sizeof(char) * 100);
	char* desc = (char*)malloc(sizeof(char) * 400);
	PlaceList targetList;
	printf(" [] Settings\n");
	printf("   1. Add place\n");
	printf("   2. Modify place\n");
	printf("   3. Remove place\n");
	printf("   4. Back to main menu\n");
	printf(" [] input : ");
	scanf("	 %d", &selectNum);
	clearEnter();
	system("cls");
	switch (selectNum)
	{
	case 1:
		printf(" [Add] Name : ");
		fgets(name, 100, stdin);
		name[strlen(name)-1] = '\0';
		printf(" [Add] Description : ");
		fgets(desc, 400, stdin);
		desc[strlen(desc)-1] = '\0';
		targetList.mName = name;
		targetList.mDesc = desc;
		engine->addPlace(targetList);
		printNode(engine->mPlaceListHead);
		break;
	case 2:
		printf(" [Modify] Target index : ");
		scanf("%d", &targetIndex);
		clearEnter();
		printf(" [Modify] Name : ");
		fgets(name, 100, stdin);
		name[strlen(name)-1] = '\0';
		printf(" [Modify] Description : ");
		fgets(desc, 400, stdin);
		desc[strlen(desc)-1] = '\0';
		targetList.mName = name;
		targetList.mDesc = desc;
		engine->modifyPlace(targetIndex, targetList);
		printNode(engine->mPlaceListHead);
		break;
	case 3:
		printf(" [Delete] Target index : ");
		scanf("%d", &targetIndex);
		clearEnter();
		engine->removePlace(targetIndex);
		printNode(engine->mPlaceListHead);
		break;
	case 4:
		if(name){ free(name); name = NULL;}
		if(desc){ free(desc); desc = NULL;}
		ret = 2;
		break;
	default:
		if(name){ free(name); name = NULL;}
		if(desc){ free(desc); desc = NULL;}
		printf("\n");
		printf(" [] Invalid number\n");
		break;
	}
	printf("\n");
	return ret;
}


bool selectPlaceMenu()
{
	bool ret = false;
	char ch;
	printf("\n [Select] Select this Lunch place for today`s lunch. Ok? (y/n)");
	scanf("%c", &ch);
	clearEnter();
	if( 'y' == ch || 'Y' == ch)
	{
		printf("\n [Select] Save success\n");
		ret = true;
	}
	else if ( 'n' == ch || 'N' == ch)
		printf("\n [Select] Didn`t select place.\n");
	else
	{
		printf("\n [] Invalid value input\n");
		selectPlaceMenu();
	}
	return ret;
}

bool pickPlaceMenu(PlaceList* placeList)
{
	bool ret = false;
	if(placeList)
	{
		printf("\n[result] %s - %s(%d times selected.)\n", placeList->mName, placeList->mDesc, placeList->mFreq);
		ret = true;
	}
	else
		printf("\n[result] There is no lunch place!\n");
	return ret;
}

void clearEnter()
{
	while (getchar() != '\n');
}
