#ifndef BWL_UTIL_H
#define BWL_UTIL_H

#include "jni.h"
#include <android/log.h>

#define LOG_TAG "JNI_log"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

// jstring转为char*
char *jstring2cStr(JNIEnv *env, jstring jstr);

// char*转为jstring
jstring cStr2jstring(JNIEnv *env, const char *pat);

// long转为char
char *jlong2char(JNIEnv *env, jlong number);

// char转为16进制
char *char2Hex(unsigned char c, char* hexValue) ;

// 16进制转为byte[]
void hexStrToUint8(char *str, int strLen, char* dest);

// byte[]转为16进制
void uint8ToHexStr(char *src, int len, char* dest);

//打印bytes
void printBytes(char *src, int len);

#endif //BWL_UTIL_H
