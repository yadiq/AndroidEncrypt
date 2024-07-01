package org.freedesktop.liantian;

/**
 * ****************************************************************
 * 作    者: Created by gyd
 * 创建时间: 2024/6/6 13:34
 * 文件描述: 加密
 * 注意事项:
 * ****************************************************************
 */
public class Liantian {
    ////////////////////////////////////native///////////////////////////////////
    static {
        System.loadLibrary("liantian");
    }

    public static native String sha1Encrypt(String in);
    public static native String hmacSha256Encrypt(String in);
    public static native String aes128EcbEncrypt(String in);
    public static native String aes128EcbDecrypt(String in);
    public static native String aes256gcmEncrypt(String in);
    public static native String aes256gcmDecrypt(String in);
}
