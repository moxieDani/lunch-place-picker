#include <stdio.h>
#include "LunchPlacePicker.h"

void printNode();

void printNode()
{
	LunchPlaceInfo* tmp = NULL;
	int i = 0;

	printf("[Output]\n");
	for( tmp = temp(); tmp; tmp = tmp->pNext)
		printf("[print] %d. FREQ(%d) NAME(%s) DESC(%s)\n", i++, tmp->freq, tmp->name, tmp->desc);
	printf("\n");
}

int main(int argc, char* argv[])
{
	LunchPlaceInfo* lunchPlace = NULL;
	open("lunch-place-info.txt");
	if (init() == 0)
	{
		lunchPlace = pickLunchPlace();
		printf("\n[total] Lunch Place information : NAME(%s) / DESC(%s)\n", lunchPlace->name, lunchPlace->desc);

		save();
	}
	deinit();
	close();
	return 0;
}