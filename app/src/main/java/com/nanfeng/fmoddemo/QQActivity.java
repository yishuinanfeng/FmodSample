package com.nanfeng.fmoddemo;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;

/**
 * Created by Administrator on 2019/3/30.
 */

public class QQActivity extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        org.fmod.FMOD.init(this);
        setContentView(R.layout.activity_qq);
    }

    public void mFix(View btn){
        String path ="file:///android_asset/jaguar.wav";
        EffectUtil.fix(path,EffectUtil.MODE_NORMAL);
    }

    @Override
    protected void onDestroy() {
        org.fmod.FMOD.close();
        super.onDestroy();
    }
}
