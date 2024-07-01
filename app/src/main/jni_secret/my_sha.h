//
// Created by Adi on 2024/6/16.
//

#ifndef ANDROIDNATIVE_MY_SHA_H
#define ANDROIDNATIVE_MY_SHA_H

char* sha1_encrypt(const unsigned char *in);

char *hmac_sha256_encrypt(const void *key, int key_len, const unsigned char *in);

#endif //ANDROIDNATIVE_MY_SHA_H
