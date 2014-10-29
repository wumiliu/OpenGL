package com.example.opengl;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class GL2JNIView extends GLSurfaceView {
	public GL2JNIView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		setEGLContextClientVersion(2);
		setRenderer(new NdkGlRender());
	}
}
