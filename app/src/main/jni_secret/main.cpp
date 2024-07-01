#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Util.h"
#include "SignUtil.h"
#include "my_sha.h"
#include "my_aes.h"

//const char key1[] = "1234567890123456";//16B
const char key1[] = {'1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6'};//16B
//const char key2[] = "12345678901234567890123456789012";//32B
const char key2[] = "{'1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2'}";//32B

JNIEXPORT jstring JNICALL
sha1Encrypt(JNIEnv *env,jclass thiz,jstring str) {
    const char *strFromJava = env->GetStringUTFChars(str, NULL);
    char *hexStr = sha1_encrypt((const unsigned char *)strFromJava);
    jstring result = env->NewStringUTF(hexStr);
    //释放空间
    env->ReleaseStringUTFChars(str, strFromJava);
    free(hexStr);
    return result;
}

JNIEXPORT jstring JNICALL
hmacSha256Encrypt(JNIEnv *env,jclass thiz,jstring str) {
    const char *strFromJava = env->GetStringUTFChars(str, NULL);
    char *hexStr = hmac_sha256_encrypt(key1, sizeof(key1), (const unsigned char *)strFromJava);
    jstring result = env->NewStringUTF(hexStr);
    //释放空间
    env->ReleaseStringUTFChars(str, strFromJava);
    free(hexStr);
    return result;
}

JNIEXPORT jstring JNICALL
aes128EcbEncrypt(JNIEnv *env, jclass thiz, jstring str) {
    const char *strFromJava = env->GetStringUTFChars(str, NULL);
    char *base64Str = aes128ecb_encrypt(key1, (const unsigned char *) strFromJava);
    jstring result = env->NewStringUTF(base64Str);
    //释放空间
    env->ReleaseStringUTFChars(str, strFromJava);
    free(base64Str);
    return result;
}

JNIEXPORT jstring JNICALL
aes128EcbDecrypt(JNIEnv *env, jclass thiz, jstring str) {
    const char *strFromJava = env->GetStringUTFChars(str, NULL);
    char *hexStr = aes128ecb_decrypt(key1, (const unsigned char *) strFromJava);
    jstring result = env->NewStringUTF(hexStr);
    //释放空间
    env->ReleaseStringUTFChars(str, strFromJava);
    free(hexStr);
    return result;
}

JNIEXPORT jstring JNICALL
aes256gcmEncrypt(JNIEnv *env,jclass thiz,jstring str) {
    const char *strFromJava = env->GetStringUTFChars(str, NULL);
    char *base64Str = aes256gcm_encrypt(key2, (const unsigned char *)strFromJava);
    jstring result = env->NewStringUTF(base64Str);
    //释放空间
    env->ReleaseStringUTFChars(str, strFromJava);
    free(base64Str);
    return result;
}

JNIEXPORT jstring JNICALL
aes256gcmDecrypt(JNIEnv *env,jclass thiz,jstring str) {
    const char *strFromJava = env->GetStringUTFChars(str, NULL);
    char *hexStr = aes256gcm_decrypt(key2, (const unsigned char *)strFromJava);
    jstring result = env->NewStringUTF(hexStr);
    //释放空间
    env->ReleaseStringUTFChars(str, strFromJava);
    free(hexStr);
    return result;
}


//构建 JNINativeMethod 数组
static JNINativeMethod methods[] = {
        {"sha1Encrypt", "(Ljava/lang/String;)Ljava/lang/String;", (void *) sha1Encrypt},
        {"hmacSha256Encrypt", "(Ljava/lang/String;)Ljava/lang/String;", (void *) hmacSha256Encrypt},
        {"aes128EcbEncrypt", "(Ljava/lang/String;)Ljava/lang/String;", (void *) aes128EcbEncrypt},
        {"aes128EcbDecrypt", "(Ljava/lang/String;)Ljava/lang/String;", (void *) aes128EcbDecrypt},
        {"aes256gcmEncrypt", "(Ljava/lang/String;)Ljava/lang/String;", (void *) aes256gcmEncrypt},
        {"aes256gcmDecrypt", "(Ljava/lang/String;)Ljava/lang/String;", (void *) aes256gcmDecrypt}
};

//动态注册的入口函数
jint
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    //获取JNI env变量
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    //获取native方法所在类
    jclass clazz = env->FindClass("org/freedesktop/liantian/Liantian");
    if (clazz == NULL) {
        return -1;
    }
    // 动态注册native方法
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        return -1;
    }

    //比对包名和签名
    char *expectPackageName = getPackageName(env);//"com.test"; 替换为app的包名
    char *expectSign = getSign(env);//"123456091939831e5172c94786e74830";  替换为app的签名
    char *packageName = getPackageName(env);
    char *sign = getSign(env);

    //比对签名
    if (packageName != NULL && sign != NULL && strcmp(expectPackageName, packageName) == 0 && strcmp(expectSign, sign) == 0) {
        LOGI("verification success");
    } else {
        LOGI("verification failed");
        strcmp(NULL, NULL);
    }
    free(sign);
    return JNI_VERSION_1_4;
}