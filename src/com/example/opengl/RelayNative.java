package com.example.opengl;

public class RelayNative {
	public native static void onNdkSurfaceCreated ();  
	public native static void onNdkSurfaceChanged (int width, int height);  
	public native static void onNdkDrawFrame();
}
