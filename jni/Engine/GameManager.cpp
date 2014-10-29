#include "GameManager.h"
#include "glRenderer.h"
#include "OpenGLEngine.h"
#include "TextureMgr.h"
GameManager::GameManager()
{
	pScrolRect = new ScrolRect();

	Rectangle pPageRect(0, 0, g_objBase.m_nWidth-100, g_objBase.m_nHeight-100);
	Rectangle pRect(0, 0, 2024,1444);
	pScrolRect->SetPageRect(pPageRect);
	pScrolRect->SetRect(pRect);

}

GameManager::~GameManager()
{
}

GameManager& GameManager::GetInstance()
{
	static GameManager _instance;
	return*(&_instance);
}

void GameManager::Process()
{
	g_objBase.Begin();
	pScrolRect->Process();
	g_objRender.ShowTexture(300, 100, 800, 130, g_objTextureMgr.GetTexture("ExampleBillboard.dds")->m_TextureId);

	g_objRender.ShowTexture(200, 200, g_objTextureMgr.GetTexture("npc1.png"));
	CTexture* pTexture = g_objTextureMgr.GetTexture("12.jpg");
	RECT pSrcTmp;
	if (pTexture)
	{
		pSrcTmp.left = 0;
		pSrcTmp.right = pTexture->m_nWidth;
		pSrcTmp.top = 0;
		pSrcTmp.bottom = pTexture->m_nHeight;
	}
	g_objRender.DrawCube(0);
	g_objRender.ShowTextureEx(10, 400, &pSrcTmp, 300, 300, pTexture, 0.0f);
	g_objRender.ShowRectEx(0, 0, 100, 100, DX_SCREEN_COLOR(1, 1, 0));

	g_objBase.End();
}

void GameManager::MouseEven(MouseType nType, MousePos pos)
{
	pScrolRect->MouseEven(nType, pos);
}
