//
// Created by wenlongbai on 8/14/17.
//

#include <malloc.h>
#include <string.h>
#include "jni.h"
#include "Util.h"

#define HEX_VALUES "0123456789abcdef"
//#define HEX_VALUES "0123456789ABCDEF"

char *jstring2cStr(JNIEnv *env, jstring jstr) {
    const char *temp = (char *) env->GetStringUTFChars(jstr, NULL);
    char *ret = (char *) malloc(strlen(temp) + 1);
    strcpy(ret, temp);
    env->ReleaseStringUTFChars(jstr, temp);
    return ret;
}

jstring cStr2jstring(JNIEnv *env, const char *chars) {
    jstring ret = env->NewStringUTF(chars);
    return ret;
}

char *jlong2char(JNIEnv *env, jlong number) {
    char *chars = (char *) malloc(20);
    sprintf(chars, "%lld", number);
    return chars;
}


char *char2Hex(unsigned char c, char *hexValue) {
    if (c < 16) {
        hexValue[0] = HEX_VALUES[0];
        hexValue[1] = HEX_VALUES[c];
    } else {
        int l = c / 16;
        int r = c % 16;
        hexValue[0] = HEX_VALUES[l];
        hexValue[1] = HEX_VALUES[r];
    }
    hexValue[2] = 0;
    return hexValue;
}

void hexStrToUint8(char *str, int strLen, char* dest) {
    unsigned int val;
      for(int i = 0; i < strLen; i += 2){
        sscanf(str + i, "%02x", &val);
        dest[i / 2] = val;
      }
}

void uint8ToHexStr(char *src, int len, char* dest) {
    for(int i = 0; i < len; i++ ){
      sprintf(&dest[i * 2], "%02x", (unsigned char)src[i]);
    }
    dest[len * 2] = '\0';
}

void printBytes(char *src, int len) {
    char dest[len * 2 + 1];
    for(int i = 0; i < len; i++ ){
        sprintf(&dest[i * 2], "%02x", (unsigned char)src[i]);
    }
    dest[len * 2] = '\0';
    LOGD("printBytes= %s", dest);
}