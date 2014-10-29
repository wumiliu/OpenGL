#include <jni.h>


#include <GLES2/gl2.h>
#include <GLES/glext.h>





#include "Engine/htype.h"
#include "Engine/OpenGLEngine.h"
#include "Engine/glMeshFactory.h"
#include "Engine/glShaderFactory.h"
#include "Engine/glRenderer.h"
#include "Engine/TextureMgr.h"
#include  "Engine/GameManager.h"
#include <stdio.h>
#include <string>



#ifdef __cplusplus
extern "C" {
#endif

void Java_com_example_opengl_RelayNative_onNdkSurfaceCreated(JNIEnv* env) {
		g_objBase.init();
	}

void Java_com_example_opengl_RelayNative_onNdkSurfaceChanged(JNIEnv * env,
		jobject jobj, jint width, jint height)

	{
		g_objBase.Initialize(width, height);
	}

/* Call to render the next GL frame */
void Java_com_example_opengl_RelayNative_onNdkDrawFrame(JNIEnv * env,
		jobject jobj) {

//		g_objBase.Begin();
//		g_objRender.ShowTexture(300, 100, 800, 130, g_objTextureMgr.GetTexture("ExampleBillboard.dds")->m_TextureId);
//
//		g_objRender.ShowTexture(200, 200, g_objTextureMgr.GetTexture("npc1.png"));
//		CTexture* pTexture = g_objTextureMgr.GetTexture("npc1.png");
//		RECT pSrcTmp;
//		if (pTexture)
//		{
//			pSrcTmp.left = 0;
//			pSrcTmp.right = pTexture->m_nWidth;
//			pSrcTmp.top = 0;
//			pSrcTmp.bottom = pTexture->m_nHeight;
//		}
//		g_objRender.DrawCube(0);
//		g_objRender.ShowTextureEx(10, 400, &pSrcTmp, 300, 300, pTexture,0.0f);
//		g_objRender.ShowRectEx(0, 0, 100, 100, DX_SCREEN_COLOR(1, 1, 0));
//		g_objBase.End();
	g_objGameManager.Process();
	}

#ifdef __cplusplus
}
#endif
