package com.example.opengl;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;

public class NdkGlRender implements Renderer {

	@Override
	public void onDrawFrame(GL10 arg0) {
		// TODO Auto-generated method stub
		RelayNative.onNdkDrawFrame (); 
	}

	@Override
	public void onSurfaceChanged(GL10 arg0, int width, int height) {
		// TODO Auto-generated method stub
		RelayNative.onNdkSurfaceChanged (width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 arg0, EGLConfig arg1) {
		// TODO Auto-generated method stub
		RelayNative.onNdkSurfaceCreated ();
	}

}
