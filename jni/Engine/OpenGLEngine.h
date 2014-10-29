#include "htype.h"
class  GRAPHIC_API OpenGLEngine
{
private:
	OpenGLEngine();
	~OpenGLEngine();
	void InitGL();
public:
	static OpenGLEngine* GetInstancePtr();
	static OpenGLEngine& GetInstance();

#ifdef _ANDROID_
	bool Initialize(int nWidth, int nHeigth);
#else
	bool Initialize(HDC hDC, int nWidth, int nHeigth);
#endif // _ANDROID_

	void init();
	void Begin();
	void End();

private:
#ifdef _ANDROID_

#else
	HGLRC		m_hRC;		// Permanent Rendering Context
	HDC m_hDC;
#endif // _ANDROID_


	GLuint programObj;
	GLuint vertexbuffer;
	GLuint indexbuffer;
	GLuint vao;
public:
	int m_nWidth;
	int m_nHeight;
};
#define  g_objBase OpenGLEngine::GetInstance()
