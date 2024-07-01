#ifndef BWL_SIGN_UTIL_H
#define BWL_SIGN_UTIL_H

#include <jni.h>

char *getSign(JNIEnv *env);//获取应用签名
char *getPackageName(JNIEnv *env);//获取应用包名

#endif //BWL_SIGN_UTIL_H