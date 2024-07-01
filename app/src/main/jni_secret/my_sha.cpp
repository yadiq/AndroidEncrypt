#include <string.h>
#include <malloc.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>

#include "Util.h"
#include "my_sha.h"

//SHA-1可以生成一个被称为消息摘要的160位（20字节）散列值。加密后20B
//Sha1加密是不可逆的，网上虽然有解密的方法，但只能解密很简单的密码
/**
 * sha1加密函数
 * @param in
 * @return 16进制字符串，需要手动释放空间
 */
char *sha1_encrypt(const unsigned char *in) {
    unsigned char out[20];//存储在栈区，局部变量会在函数结束后自动释放申请的空间
    size_t outLen = 20;
    SHA1(in, strlen((const char *) in), out);
    //转hex
    char *hexStr = (char *) malloc(outLen * 2 + 1);//存储在堆区，由程序员分配释放
    uint8ToHexStr((char *) out, outLen, hexStr);
    return hexStr;
}


//HMAC-SHA256 算法，使用SHA-256生成哈希值的HMAC算法
//SHA256 摘要长度为256位（32字节）
/**
 * hmac_sha256加密函数
 * @param in
 * @return 16进制字符串，需要手动释放空间
 */
char *hmac_sha256_encrypt(const void *key, int key_len, const unsigned char *in) {
    unsigned char *out = NULL;//char[32] 存储在栈区，局部变量会在函数结束后自动释放申请的空间 TODO 是否需要申请空间
    unsigned int outLen = -1;
    out = HMAC(EVP_sha256(), key, key_len, in, strlen((const char *) in), out, &outLen);
    //LOGD("hmac_sha256_encrypt out=%s len=%d", out, outLen);
    //转hex
    char *hexStr = (char *) malloc(outLen * 2 + 1);//存储在堆区，由程序员分配释放
    uint8ToHexStr((char *) out, outLen, hexStr);
    //LOGD("hex=%s", hexStr);
    return hexStr;
}