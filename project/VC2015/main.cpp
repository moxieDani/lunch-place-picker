#include <stdio.h>
#include "LunchPlacePicker.h"

int main(int argc, char* argv[])
{
	init("lunch-place-info.txt");
	modify(1, "진순대", "뼈해장국과 순대국을 동시에!");
	remove(2);
	exit();
	return 0;
}