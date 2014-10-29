#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <string>
#include "htype.h"

class TextureMgr;
// Class that wraps information about a texture. This class 
// won't be used directly by the users. Instead, they will
// manipulate the CImage class.
class  GRAPHIC_API CTexture
{
	friend class TextureMgr;
public:
	CTexture(GLuint);
	GLuint  m_TextureId;
	int m_nWidth;
	int m_nHeight;
	void Bind();
	
};

#endif  // _TEXTURE_H_