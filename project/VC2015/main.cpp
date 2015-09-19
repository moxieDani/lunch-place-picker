#include <stdio.h>
#include "LunchPlacePicker.h"

void printNode();

void printNode()
{
	printf("[Output]\n");
	int i = 0;
	for( LunchPlaceInfo* tmp = temp(); tmp; tmp = tmp->pNext)
		printf("[print] %d. FREQ(%d) NAME(%s) DESC(%s)\n", i++, tmp->frequency, tmp->name, tmp->desc);
	printf("\n");
}

int main(int argc, char* argv[])
{
	LunchPlaceInfo* lunchPlace = NULL;
	open("lunch-place-info.txt");
	init();

	lunchPlace = pickLunchPlace();
	printf("\n[total] Lunch Place information : NAME(%s) / DESC(%s)\n", lunchPlace->name, lunchPlace->desc);
	save();
	deinit();
	close();
	return 0;
}