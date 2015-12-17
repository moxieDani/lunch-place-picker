#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Engine.h"
#include "PlaceList.h"

void printNode(PlaceList* placeList);
bool mainMenu(Engine* engine);
bool settingsMenu(Engine* engine);
bool selectPlaceMenu();
bool pickPlaceMenu(PlaceList* ret);

void clearEnter();


void printNode(PlaceList* placeList)
{
	int i = 1;
	for(PlaceList* list = placeList; list != NULL; list = list->mNext)
		printf("%03d. %s - %s(%d times selected.)\r\n", i++, list->mName, list->mDesc, list->mFreq);
	printf("\r\nTotal Place Number : %d\r\n", placeList ? i : 0);
}

int main(int argc, char* argv[])
{
	const char* path = argv[1] ? argv[1] : "lunch-place-info.txt";
	Engine* engine = new Engine(path);
	
	while(mainMenu(engine)) {}
	return 0;
}

bool mainMenu(Engine* engine)
{
	bool ret = true;
	PlaceList* pickedPlace;
	int selectNum;
	bool isPlaceChanged = false;
		
	system("printf '\033\143'");
	printf("\r\n\r\n** Lunch Place Picker **\r\n");
	printf(" [] Select Menu\r\n");
	printf("   1. Pick lunch place\r\n");
	printf("   2. Show all lunch places\r\n");
	printf("   3. Settings\r\n");
	printf("   4. Exit\r\n");
	printf(" [] input : ");
	scanf("	 %d",&selectNum);
	clearEnter();
	system("printf '\033\143'");
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
		printf("\r\n");
		printNode(engine->mPlaceListHead);
		break;
	case 3:
		while(settingsMenu(engine)) {}
		isPlaceChanged = true;
		break;
	case 4:
		if(isPlaceChanged)
			engine->savePlaceListToFile();
		ret = false;
		break;
	default:
		printf("\r\n");
		printf(" [] Invalid number\r\n");
		break;
	}
	printf("\r\n");
	if(ret)
		system("read -n1 -s -p \"\r\nPress any key to continue...\" key");

	
	return ret;
}

bool settingsMenu(Engine* engine)
{
	bool ret = true;
	int selectNum = 0;
	int targetIndex = 0;
	char* name = (char*)malloc(sizeof(char) * 100);
	char* desc = (char*)malloc(sizeof(char) * 400);
	PlaceList targetList;
	printf(" [] Settings\r\n");
	printf("   1. Add place\r\n");
	printf("   2. Modify place\r\n");
	printf("   3. Remove place\r\n");
	printf("   4. Back to main menu\r\n");
	printf(" [] input : ");
	scanf("	 %d", &selectNum);
	clearEnter();
	system("printf '\033\143'");
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
		ret = false;
		break;
	default:
		if(name){ free(name); name = NULL;}
		if(desc){ free(desc); desc = NULL;}
		printf("\r\n");
		printf(" [] Invalid number\r\n");
		break;
	}
	printf("\r\n");
	if(ret)
		system("read -n1 -s -p \"\r\nPress any key to continue...\" key");
	return ret;
}


bool selectPlaceMenu()
{
	bool ret = false;
	char ch;
	printf("\r\n [Select] Select this Lunch place for today`s lunch. Ok? (y/n)");
	scanf("%c", &ch);
	clearEnter();
	if( 'y' == ch || 'Y' == ch)
	{
		printf("\r\n [Select] Save success\r\n");
		ret = true;
	}
	else if ( 'n' == ch || 'N' == ch)
		printf("\r\n [Select] Didn`t select place.\r\n");
	else
	{
		printf("\r\n [] Invalid value input\r\n");
		selectPlaceMenu();
	}
	return ret;
}

bool pickPlaceMenu(PlaceList* placeList)
{
	bool ret = false;
	if(placeList)
	{
		printf("\r\n[result] %s - %s(%d times selected.)\r\n", placeList->mName, placeList->mDesc, placeList->mFreq);
		ret = true;
	}
	else
		printf("\r\n[result] There is no lunch place!\r\n");
	return ret;
}

void clearEnter()
{
	while (getchar() != '\n');
}
