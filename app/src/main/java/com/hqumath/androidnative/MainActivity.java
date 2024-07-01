package com.hqumath.androidnative;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.hqumath.androidnative.databinding.ActivityMainBinding;
import com.hqumath.androidnative.utils.CommonUtil;
import com.hqumath.androidnative.utils.LogUtil;

import org.freedesktop.liantian.Liantian;

/**
 * ****************************************************************
 * 作    者: Created by gyd
 * 创建时间: 2023/9/5 16:24
 * 文件描述:
 * 注意事项:
 * ****************************************************************
 */
public class MainActivity extends AppCompatActivity {
    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        CommonUtil.init(this);


        String msg = "123ab";

        String sha1Encrypt = Liantian.sha1Encrypt(msg);
        LogUtil.d("sha1Encrypt=" + sha1Encrypt);
        String hmacSha256Encrypt = Liantian.hmacSha256Encrypt(msg);
        LogUtil.d("hmacSha256Encrypt=" + hmacSha256Encrypt);

        String aes128EcbEncrypt = Liantian.aes128EcbEncrypt(msg);
        LogUtil.d("aes128EcbEncrypt=" + aes128EcbEncrypt);
        String aes128EcbDecrypt = Liantian.aes128EcbDecrypt(aes128EcbEncrypt);
        LogUtil.d("aes128EcbDecrypt=" + aes128EcbDecrypt);

        String aes256gcmEncrypt = Liantian.aes256gcmEncrypt(msg);
        LogUtil.d("aes256gcmEncrypt=" + aes256gcmEncrypt);
        String aes256gcmDecrypt = Liantian.aes256gcmDecrypt(aes256gcmEncrypt);
        LogUtil.d("aes256gcmDecrypt=" + aes256gcmDecrypt);

        binding.tvResult.setText("明文：" + msg + "\n加密结果：" +
                "\nsha1Encrypt=" + sha1Encrypt +
                "\nhmacSha256Encrypt=" + hmacSha256Encrypt +
                "\naes128EcbEncrypt=" + aes128EcbEncrypt +
                "\naes256gcmEncrypt=" + aes256gcmEncrypt
        );
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        CommonUtil.killProgress();
    }
}
