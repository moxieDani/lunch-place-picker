#pragma once

/*
Node의 구성
 - name : 점심장소의 이름
 - desc : 부연설명
 - freq : 선택된 빈도수
*/
typedef struct LunchPlaceInfo {
	char* name;
	char* desc;
	int freq;
	LunchPlaceInfo* pNext;
}LunchPlaceInfo;

class Place
{
public:
	Place();
	~Place();
	char* getName();
	char* getDesc();
	int getFreq();

private:
	char* mName;
	char* mDesc;
	int mFreq;

private:

};