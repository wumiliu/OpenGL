#include "Texture.h"
#include "TextureMgr.h"
#include <string>


CTexture::CTexture(GLuint _id)
{
	m_TextureId = _id;
}

void CTexture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}
