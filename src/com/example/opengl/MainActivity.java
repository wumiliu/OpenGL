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

		// ��ȡ��չSD���豸״̬
		String sDStateString = android.os.Environment.getExternalStorageState();

		File myFile = null;
		// ӵ�пɶ���дȨ��
		if (sDStateString.equals(android.os.Environment.MEDIA_MOUNTED)) {

			try {

				// ��ȡ��չ�洢�豸���ļ�Ŀ¼
				File SDFile = android.os.Environment
						.getExternalStorageDirectory();

				File destDir = new File(SDFile.getAbsolutePath() + destDirStr);// �ļ�Ŀ¼

				if (!destDir.exists()) {// �ж�Ŀ¼�Ƿ���ڣ������ڴ���
					destDir.mkdir();// ����Ŀ¼
				}
				// ���ļ�
				myFile = new File(destDir + File.separator + file);

				// �ж��ļ��Ƿ����,�������򴴽�
				if (!myFile.exists()) {
					myFile.createNewFile();// �����ļ�
				}

				// д���� ע�����������������һ����д����ļ����ڶ�����ָ�Ǹ��ǻ���׷�ӣ�
				// Ĭ���Ǹ��ǵģ����ǲ�д�ڶ�����������������Ϊtrue����˵�����ǣ����ں���׷�ӡ�
				FileOutputStream outputStream = new FileOutputStream(myFile,
						true);
				szOutText = destDir.getAbsolutePath();
				outputStream.write(szOutText.getBytes());// д������
				outputStream.close();// �ر���

			} catch (Exception e) {
				// TODO: handle exception
				e.getStackTrace();
			}

		}
	}

}
