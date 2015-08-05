package com.nju.ecg.wave;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.Display;
import android.view.KeyEvent;
import android.view.Window;
import android.view.WindowManager;
import com.nju.ecg.R;
import com.nju.ecg.basic.BasicActivity;
import com.nju.ecg.utils.EcgConst;
import com.nju.ecg.utils.LogUtil;

/***
 * 欢迎界面
 * 
 * @author zhuhf
 * @version [ME MTVClient_Handset V100R001C04SPC002, 2012-9-3]
 */
public class EcgWelcomeScreen extends BasicActivity
{
    private static final String TAG = "EcgWelcomeScreen";

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.welcome_screen);

        WindowManager windowManager = getWindowManager();
        Display display = windowManager.getDefaultDisplay();
        int rotation = display.getOrientation();
        EcgConst.DISPLAY_WIDTH = display.getWidth();
        EcgConst.DISPLAY_HEIGH = display.getHeight();
        LogUtil.d(TAG,
            "Width = " + EcgConst.DISPLAY_WIDTH + " Heigh = "
                + EcgConst.DISPLAY_HEIGH + " Rotate = " + rotation);
        EcgConst.WAVE_WIDTH = ((EcgConst.DISPLAY_WIDTH - EcgConst.DISPLAY_LEFT_LEAD_NUMBER_WIDTH) / 16) * 16; // 8
                                                                                                              // =
                                                                                                              // RAW_DATA_BUF_LENGTH
                                                                                                              // /2/
                                                                                                              // AVARAGE_POINTS;
        if (EcgConst.DISPLAY_HEIGH < 700) // 屏幕高度低于700, 肢体和模拟肢体导联之间隔缩小才能完整显示
        {
            EcgDrawView.marginBetweenWave = EcgDrawView.CENTER_Y_CH;
        }
        /**
         *  启动画面延迟2秒进入主界面
         */
        new Handler().postDelayed(new Runnable()
        {
            @Override
            public void run()
            {
                Intent intent = new Intent(EcgWelcomeScreen.this,
                    WaveScreen.class);
                intent.putExtra("mode",
                    0);
                startActivity(intent);
                finish();
            }
        }, 2000);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if (keyCode == KeyEvent.KEYCODE_BACK)
        {
            finishAll();
            android.os.Process.killProcess(android.os.Process.myPid());
            System.exit(0);
        }
        return super.onKeyDown(keyCode,
            event);
    }

}
