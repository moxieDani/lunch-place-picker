#pragma once

#include <stdio.h>

class FileManager
{
public:
	FileManager(const char* name, const char* type);
	char* getData(long offset, size_t length);
	size_t getFileSize();
	int write(const char* _format,...);
	~FileManager();
private:
	FILE *mFilePtr;
	char* mData;	
};

