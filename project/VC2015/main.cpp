#include <stdio.h>
#include "LunchPlacePicker.h"

int main(int argc, char* argv[])
{
	init("lunch-place-info.txt");
	
	remove(0);
	remove(0);
	add("Keep Your Fork", "푸드코트. 조금 비쌈.");
	modify(1, "진순대", "뼈해장국과 순대국을 동시에!");
	LunchPlaceInfo* tmp = temp();
	printf("\n");
	while (NULL != tmp)
	{
		printf("[total] FREQ(%d) NAME(%s) DESC(%s)\n", tmp->frequency, tmp->name, tmp->desc);
		//printf("[total] tmp(%x) \n", tmp);
		tmp = tmp->pNext;
	}
	exit();
	return 0;
}