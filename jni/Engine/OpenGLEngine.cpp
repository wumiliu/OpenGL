#include "OpenGLEngine.h"
#include "glShaderFactory.h"
#include "glMeshFactory.h"

#include <malloc.h>
#include <assert.h>
#include <string.h>


OpenGLEngine::OpenGLEngine()
{
}


OpenGLEngine::~OpenGLEngine()
{
}

OpenGLEngine* OpenGLEngine::GetInstancePtr()
{
	static OpenGLEngine _instance;
	return&_instance;
}

OpenGLEngine& OpenGLEngine::GetInstance()
{
	return *(GetInstancePtr());
}
#ifdef _ANDROID_
bool OpenGLEngine::Initialize(int nWidth, int nHeigth)
{
	m_nWidth = nWidth;
	m_nHeight = nHeigth;
}

#else
bool OpenGLEngine::Initialize(HDC hDC, int nWidth, int nHeigth)
{
	m_nWidth = nWidth;
	m_nHeight = nHeigth;
	m_hDC = hDC;
	int bits = 32;
	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		33317,
		32,										// Select Our Color Depth
		8, 16, 8, 8, 8, 0,							// Color Bits Ignored
		8,											// No Alpha Buffer
		24,											// Shift Bit Ignored
		64,											// No Accumulation Buffer
		16, 16, 16, 16,									// Accumulation Bits Ignored
		24,											// 16Bit Z-Buffer (Depth Buffer)  
		8,											// No Stencil Buffer
		4,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		return FALSE;								// Return FALSE
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		return FALSE;
	}

	if (!(m_hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		// Reset The Display
		MessageBoxA(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, m_hRC))					// Try To Activate The Rendering Context
	{
		// Reset The Display
		MessageBoxA(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}
	glewInit();

	init();
	glViewport(0, 0, nWidth, nHeigth);
	return true;
}

#endif




void OpenGLEngine::init()
{
	
}

void OpenGLEngine::Begin()
{
	float color[4];
	color[0] = 0.1921568627450980392156862745098f;
	color[1] = 0.30196078431372549019607843137255f;
	color[2] = 0.47450980392156862745098039215686f;
	color[3] = 1.0f;
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

}

void OpenGLEngine::End()
{
#ifdef _ANDROID_
#else
	SwapBuffers(m_hDC);					// Swap Buffers (Double Buffering)
#endif // _ADNROID_
}
