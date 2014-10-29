#pragma once
#include "htype.h"
class CTexture;
struct  DX_SCREEN_VERTEX
{
	GLfloat x, y, z;
	DX_SCREEN_VERTEX()
	{

	}
	DX_SCREEN_VERTEX(GLfloat _x, GLfloat _y, GLfloat _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

struct  DX_SCREEN_COLOR
{
	GLfloat r, g, b;
	DX_SCREEN_COLOR()
	{

	}
	DX_SCREEN_COLOR(GLfloat _x, GLfloat _y, GLfloat _z)
	{
		r = _x;
		g = _y;
		b = _z;
	}
};

struct VertexPositionColor
{
	DX_SCREEN_VERTEX _pos;
	DX_SCREEN_COLOR _color;
	VertexPositionColor()
	{

	}
	VertexPositionColor(DX_SCREEN_VERTEX pos, DX_SCREEN_COLOR color)
	{
		_pos = pos;
		_color = color;
	}
};
struct XMFLOAT3
{
	float x, y, z;
	XMFLOAT3()
	{

	}
	XMFLOAT3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

struct XMFLOAT2
{
	float x, y;
	XMFLOAT2()
	{

	}
	XMFLOAT2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

struct VertexPositionNormalTexture
{
	XMFLOAT3 _pos;
	XMFLOAT3 _color;
	XMFLOAT2 _uv;
	VertexPositionNormalTexture(XMFLOAT3 pos, XMFLOAT3 color, XMFLOAT2 uv)
	{
		_pos = pos;
		_color = color;
		_uv = uv;
	}
};
struct  VertexPositionTexture
{
	XMFLOAT3 _pos;
	XMFLOAT2 _uv;
	VertexPositionTexture(XMFLOAT3 pos, XMFLOAT2 uv)
	{
		_pos = pos;
		_uv = uv;
	}
};
#ifndef  _WIN32
struct RECT
{
	float left;
	float top;
	float right;
	float bottom;
};
#endif // ! _WIN32

class GRAPHIC_API glRenderer
{
public:
	static glRenderer* GetInstancePtr();
	static glRenderer& GetInstance();
	void ShowRect(int x1, int y1, int x2, int y2);
	void ShowRectEx(int x1, int y1, int x2, int y2, DX_SCREEN_COLOR _color = DX_SCREEN_COLOR(1, 1, 1), float fRotate = 0.0f, float fScaleX = 1.0f, float fScaleY = 1.0f);
	void DrawCircle(int nX, int nY, int nRadius, DX_SCREEN_COLOR _color = DX_SCREEN_COLOR(1, 1, 1), float fRotate = 0.0f);
	void DrawCircleEx(int nX, int nY, int nRadius, DX_SCREEN_COLOR _color = DX_SCREEN_COLOR(1, 1, 1), float fRotate = 0.0f);
	void DrawCube(int n = 0);

	void ShowTexture(int x1, int y1, int x2, int y2, GLuint  TextureId);
	void ShowTexture(int x1, int y1, CTexture* pTexture);

	void ShowTextureEx(int x, int y, RECT *pSrc, int nWidth, int nHeight, CTexture*pTexture, float fRotate = 0.0f);
	void ShowTextureEx(int x, int y, RECT *pSrc, int nWidth, int nHeight, CTexture*pTexture, glm::mat4 Model = glm::mat4(1.0f));

	void ShowTexture(int x, int y, RECT *pSrc, int nWidth, int nHeight, CTexture*pTexture, glm::mat4 Model = glm::mat4(1.0f));
private:
	glRenderer();
	~glRenderer();
	void InitReSource();
	GLuint programObj;
	GLuint vertexbuffer;
	GLuint indexbuffer;
	GLuint vao;
	GLuint uiVBO;

	GLuint programTextureObj;
	GLuint vertexTBuffer;


};
#define g_objRender glRenderer::GetInstance()
