#include "_FileManager.h"
#include <stdlib.h>
#include <stdarg.h>

FileManager::FileManager(const char* name, const char* type)
{
	fp = fopen(name, type);

	if (NULL == fp)
		printf("fp is NULL\n");
	data = (char*)malloc(sizeof(char)*4);
}

char* FileManager::getData(long offset, size_t length)
{
	data = (char*)realloc(data, length);
	fseek(fp, offset, SEEK_SET);
	fread(data, sizeof(char), length, fp);
	return data;
}

size_t FileManager::getFileSize()
{
	size_t ret = 0;
	fseek(fp, 0, SEEK_END);
	ret = (size_t)ftell(fp);
	fseek(fp, 0, SEEK_SET);
	printf("filesize : %d\n", ret);
	return ret;
}

void FileManager::write(const char* _format,...)
{
	if(fp == NULL)
		printf("File write error : fp is NULL\n");
	else
	{
		va_list   arg;
		va_start(arg, _format);
		vfprintf(fp, _format, arg);
		va_end(arg);
	}
}

FileManager::~FileManager()
{
	free(data);
	if (NULL != fp)
		fclose(fp);
}