> 在Android开发过程中，需要对一些数据进行加密，特别是在网络传输过程中。
本文使用OpenSSL库实现了APP常用的加解密算法，源码见 github 项目 [AndroidEncrypt](https://github.com/yadiq/AndroidEncrypt)。


## 1.APP常用加密算法

### 1.1 对称加密 
加密和解密都是使用一个秘钥，常用加密算法：DES、3DES、AES。在众多的对称加密算法中，目前来讲AES是最好的，最安全的。
+ 优点：对数据没有长度限制，加解密速度快
+ 缺点：秘钥的传输及保管是个问题，任何一方的秘钥泄漏都将导致数据的不安全

### 1.2 非对称加密 
非对称加密首先要生成一对秘钥，分为公钥和私钥，常用加密算法：RSA、DSA。在非对称加密算法中，RSA用的最多的。
+ 优点：无需关心秘钥的传输问题，只要在服务端把私钥保管好即可
+ 缺点：加密速度慢，对加密的数据长度有限制

### 1.3 哈希算法(散列算法)

用于将数据快速映射为固定长度的值，通常用于数据结构、数据检索、数据完整性验证等各种领域。
参考文章：https://blog.renzicu.com/2023/09/414.html

#### 1.3.1 MD5 (Message Digest Algorithm 5)
+ 优势：速度较快，适用于小数据集。
+ 劣势：较易碰撞（两个不同的输入产生相同的哈希值），不适合安全性要求高的场景。
#### 1.3.2 SHA-1 (Secure Hash Algorithm 1)
+ 优势：速度适中，适用于小到中等大小的数据集，较MD5更安全。
+ 劣势：不适合用于安全性要求极高的场景，因为已经被证明存在漏洞。
#### 1.3.3 SHA-256 (Secure Hash Algorithm 256-bit)
+ 优势：安全性较高，速度适中，适用于各种数据集大小。
+ 劣势：相对于MD5和SHA-1，速度较慢。
#### 1.3.4 SHA-3 (Secure Hash Algorithm 3)
+ 优势：高度安全，适用于各种数据集大小，较SHA-256更安全。
+ 劣势：相对于SHA-256，速度较慢。
#### 1.3.5 MurmurHash
+ 优势：速度非常快，适用于大数据集，良好的随机性。
+ 劣势：不适用于安全哈希需求，因为它不是密码哈希函数。
#### 1.3.6 CityHash
+ 优势：速度非常快，适用于大数据集，良好的随机性。
+ 劣势：不适用于密码学安全哈希需求，主要用于性能优化。

## 2.APP加密算法的实现

### 2.1 OpenSSL库的集成

[OpenSSL](https://www.openssl.org/source/)是一个开源的软件库，包含了各种加密算法和协议的实现，如SSL/TLS、AES、RSA、DES、SHA等。它可以用来实现网络通信的安全，包括加密、认证和数据完整性验证等功能。
这里我们使用别人编译好的库: [openssl-curl-android](https://github.com/robertying/openssl-curl-android)

### 2.2 AES加密算法

1. 高级加密标准(AES,Advanced Encryption Standard)
AES为分组密码，分组密码也就是把明文分成一组一组的，每组长度相等，每次加密一组数据，直到加密完整个明文。（分组长度只能是128位，也就是说，每个分组为16个字节。密钥的长度可以使用128位、192位或256位。
2. 有六种加密模式
ECB模式（The Electronic Codebook Mode）
CBC模式（The Cipher Block Chaining Mode）
CTR模式（The Counter Mode）
GCM模式（The Galois/Counter Mode）,本质上是CTR模式(计数器模式)加上GMAC
CFB模式（The Cipher Feedback Mode）
OFB模式（The Output Feedback Mode）
3. 参数
Key：对称密钥，它的长度可以为128、192、256bits，用来加密明文的密码。
IV(Initialisation Vector)：初始向量，它的选取必须随机。通常以明文的形式和密文一起传送。它的作用和MD5的”加盐”有些类似，目的是防止同样的明文块，始终加密成同样的密文块。如果不设置，则默认16个0。
AAD(Additional Authenticated Data)：附加身份验证数据。AAD数据不需要加密，通常以明文形式与密文一起传递给接收者。可以为空
Mac tag(MAC标签)：将确保数据在传输和存储过程中不会被意外更改或恶意篡改。该标签随后在解密操作期间使用，以确保密文和AAD未被篡改。在加密时，Mac tag由明文、密钥Key、IV、AAD共同产生。
4. 源码
AES-256-GCM加解密, AES_128_ECB加解密
https://gitee.com/administer/AndroidEncrypt/blob/master/app/src/main/jni_secret/my_aes.cpp
5. 验证。在线加解密工具
https://www.lddgo.net/en/encrypt/aes

### 2.3 SHA加密算法

1. 安全散列算法(Secure Hash Algorithm)
五个类型：SHA-1、SHA-224、SHA-256、SHA-384，SHA-512
后四者有时并称为SHA-2
2. SHA1
SHA-1可以生成一个被称为消息摘要的160位（20字节）散列值，散列值通常的呈现形式为40个十六进制数。
Sha1加密是不可逆的，网上虽然有解密的方法，但只能解密很简单的密码。
```c
SHA1(in, strlen((const char *) in), out);
```
3. HMAC_SHA_256
HMAC(散列消息认证码)是一种使用密码散列函数，同时结合一个加密密钥，通过特别计算方式之后产生的消息认证码(MAC)
```c
out = HMAC(EVP_sha256(), key, key_len, in, strlen((const char *) in), out, &outLen);
```
4. 源码
https://gitee.com/administer/AndroidEncrypt/blob/master/app/src/main/jni_secret/my_sha.cpp
5. 验证。在线加解密工具
https://tool.oschina.net/encrypt?type=2

## 3.效果图

![1.gif](img/1.jpg)