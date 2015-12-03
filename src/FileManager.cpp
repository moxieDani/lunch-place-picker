#include "FileManager.h"
#include <stdlib.h>
#include <stdarg.h>

FileManager::FileManager(const char* name, const char* type)
{
	mFilePtr = fopen(name, type);

	if (NULL == mFilePtr)
		printf("mFilePtr is NULL\n");
	mData = (char*)malloc(sizeof(char)*4);
}

char* FileManager::getData(long offset, size_t length)
{
	mData = (char*)realloc(mData, length);
	fseek(mFilePtr, offset, SEEK_SET);
	fread(mData, sizeof(char), length, mFilePtr);
	return mData;
}

size_t FileManager::getFileSize()
{
	size_t ret = 0;
	fseek(mFilePtr, 0, SEEK_END);
	ret = (size_t)ftell(mFilePtr);
	fseek(mFilePtr, 0, SEEK_SET);
	printf("filesize : %d\n", ret);
	return ret;
}

void FileManager::write(const char* _format,...)
{
	if(mFilePtr == NULL)
		printf("File write error : mFilePtr is NULL\n");
	else
	{
		va_list   arg;
		va_start(arg, _format);
		vfprintf(mFilePtr, _format, arg);
		va_end(arg);
	}
}

FileManager::~FileManager()
{
	free(mData);
	if (NULL != mFilePtr)
		fclose(mFilePtr);
}