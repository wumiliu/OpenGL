#ifndef TEXTUREMGR_H
#define TEXTUREMGR_H

#include "htype.h"
#include "Texture.h"
#include <map>
#include <vector>
///<summary>
/// Simple texture manager to avoid loading duplicate textures from file.  That can
/// happen, for example, if multiple meshes reference the same texture filename. 
///</summary>
class GRAPHIC_API TextureMgr
{
public:
	static TextureMgr* GetInstancePtr();
	static TextureMgr& GetInstance();
	CTexture* GetTexture(std::string filename);
	
	

private:
	TextureMgr(const TextureMgr& rhs);
	TextureMgr& operator=(const TextureMgr& rhs);
	TextureMgr();
	~TextureMgr();
	CTexture* CreateTextureFormFile(const char* strFileName);
private:
	static unsigned char* m_ShareMemory;
	static long SHARE_MEMORY_SIZE;
private:
	typedef std::map<std::string, CTexture*> TTextureMap;
	// The map of already loaded textures. There are indexed
	// using their filename.
	TTextureMap m_Textures;


};
#define  g_objTextureMgr TextureMgr::GetInstance()
#endif // TEXTUREMGR_H
