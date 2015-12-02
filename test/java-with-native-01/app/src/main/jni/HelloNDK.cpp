#include <stdio.h>
#include <string.h>
#include <jni.h>

#include <pthread.h>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 */
extern "C"
JNIEXPORT jstring
Java_com_example_hellojni_HelloJni_stringFromJNI( JNIEnv* env, jobject thiz )
{
	int x = 10;
	int y = 20;

	int tmp = x + 100 + y;
	char* pTemp = (char*)malloc(100);
	memset(pTemp, 0, 100);

	free(pTemp);

    return env->NewStringUTF("Hello World");
}
