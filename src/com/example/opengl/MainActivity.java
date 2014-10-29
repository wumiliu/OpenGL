package com.example.opengl;

import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import android.support.v7.app.ActionBarActivity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import java.io.File;
import java.io.FileOutputStream;

public class MainActivity extends ActionBarActivity {

	static {
		// load library
		System.loadLibrary("Engine");
	}
	GL2JNIView surface;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		// setContentView(R.layout.activity_main);
		getWindow().setFlags(
				WindowManager.LayoutParams.FLAG_FORCE_NOT_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FORCE_NOT_FULLSCREEN);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		writeToSDcardFile("1.txt","/Android/data/com.example.opengl","read");
		surface = new GL2JNIView(this);
		setContentView(surface);
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	@Override
	protected void onResume() 
	{
		 if(getRequestedOrientation()!=ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE){
			  setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
			 }
			 super.onResume();
			 Log.i("HELLO", "onResume");
			 surface.onResume();
	}
	@Override
	protected void onPause()
	{
		super.onPause();
		Log.i("HELLO", "onPause");
		surface.onPause();
	}
	public void writeToSDcardFile(String file, String destDirStr,
			String szOutText) {

		// 获取扩展SD卡设备状态
		String sDStateString = android.os.Environment.getExternalStorageState();

		File myFile = null;
		// 拥有可读可写权限
		if (sDStateString.equals(android.os.Environment.MEDIA_MOUNTED)) {

			try {

				// 获取扩展存储设备的文件目录
				File SDFile = android.os.Environment
						.getExternalStorageDirectory();

				File destDir = new File(SDFile.getAbsolutePath() + destDirStr);// 文件目录

				if (!destDir.exists()) {// 判断目录是否存在，不存在创建
					destDir.mkdir();// 创建目录
				}
				// 打开文件
				myFile = new File(destDir + File.separator + file);

				// 判断文件是否存在,不存在则创建
				if (!myFile.exists()) {
					myFile.createNewFile();// 创建文件
				}

				// 写数据 注意这里，两个参数，第一个是写入的文件，第二个是指是覆盖还是追加，
				// 默认是覆盖的，就是不写第二个参数，这里设置为true就是说不覆盖，是在后面追加。
				FileOutputStream outputStream = new FileOutputStream(myFile,
						true);
				szOutText = destDir.getAbsolutePath();
				outputStream.write(szOutText.getBytes());// 写入内容
				outputStream.close();// 关闭流

			} catch (Exception e) {
				// TODO: handle exception
				e.getStackTrace();
			}

		}
	}

}
