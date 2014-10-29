
#include "TextureMgr.h"
#include "FreeImage.h"
#pragma comment(lib,"FreeImage.lib")



#define MAX_SHARE_MEMORY  (4*1024*512)
long TextureMgr::SHARE_MEMORY_SIZE = 0;
unsigned char* TextureMgr::m_ShareMemory = NULL;

TextureMgr::TextureMgr() 
{
	SHARE_MEMORY_SIZE = MAX_SHARE_MEMORY;
	m_ShareMemory = (unsigned char*)malloc(SHARE_MEMORY_SIZE);
	
}

TextureMgr::~TextureMgr()
{
	for (auto it = m_Textures.begin(); it != m_Textures.end(); ++it)
	{
		CTexture* pTexture = (CTexture*)it->second;
		if (pTexture)
		{
			delete pTexture;
			pTexture = NULL;
		}
	}
	m_Textures.clear();

	if (m_ShareMemory)
	{
		free(m_ShareMemory);
		m_ShareMemory = NULL;
	}
}

TextureMgr* TextureMgr::GetInstancePtr()
{
	static TextureMgr _instance;
	return &_instance;
}

TextureMgr& TextureMgr::GetInstance()
{
	return *GetInstancePtr();
}


CTexture* TextureMgr::GetTexture(std::string filename)
{

	CTexture* pTexture = NULL;
	// Does it already exist?
	if (m_Textures.find(filename) != m_Textures.end())
	{
		pTexture = m_Textures[filename];
	}
	else
	{
		int nWidth = 0;
		int  nHeight = 0;
		pTexture = CreateTextureFormFile(filename.c_str());
		if (pTexture)
		{
		
			m_Textures[filename] = pTexture;
		}
	}
	return pTexture;
}

CTexture* TextureMgr::CreateTextureFormFile(const char* strFileName)
{
	// Generate a new image Id and bind it with the
	// current image.
	std::string filePath = "/mnt/sdcard/Android/111/";
#ifndef  _WIN32
	filePath += strFileName;
#else
	filePath = strFileName;
#endif // ! _WIN32

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType(filePath.c_str());
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filePath.c_str());
	// Load the file data in the current image.
	FIBITMAP *dib0;
	dib0 = FreeImage_Load(fif, filePath.c_str(), 0);
	FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(dib0);
	if (dib0 == NULL)
	{
		return NULL;
	}
	int bpp = FreeImage_GetBPP(dib0);
	FIBITMAP* dib = FreeImage_ConvertTo32Bits(dib0);
	FreeImage_Unload(dib0);
	bpp = FreeImage_GetBPP(dib);
	unsigned int pitch = FreeImage_GetPitch(dib);
	// Store the data in our STextureData structure.
	int newSize = FreeImage_GetDIBSize(dib);
	int nWidth = FreeImage_GetWidth(dib);
	int nHeight = FreeImage_GetHeight(dib);
	GLuint	texture;
	glGenTextures(1, &texture);					// Create Three Textures
	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, texture);
	//BGR(A) order
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);

	if (pitch * nHeight > MAX_SHARE_MEMORY)
	{
		int i = (pitch * nHeight) / (MAX_SHARE_MEMORY);
		SHARE_MEMORY_SIZE = 2 * (i)*MAX_SHARE_MEMORY;

		m_ShareMemory = (unsigned char*)realloc(m_ShareMemory, SHARE_MEMORY_SIZE);
	}
	memset(m_ShareMemory, 0, SHARE_MEMORY_SIZE);

	unsigned char* pDst = m_ShareMemory;
	for (int y = 0; y < nHeight; y++)
	{
		BYTE *bits = pDst + y*pitch;// FreeImage_GetScanLine(bitmap, FreeImage_GetHeight(bitmap) - 1 - y);
		BYTE* src = FreeImage_GetScanLine(dib, y);//, FreeImage_GetScanLine(dib, rows), 
		int kk = FI_RGBA_RED;
		//bgra
		//// Little Endian (x86 / MS Windows, Linux) : BGR(A) order
		for (int x = 0; x < nWidth; x++)
		{
			//Texture ->  BGRA  to -> RGBA
		

			bits[0] = src[2]; 
			bits[1] = src[1];
			bits[2] = src[0];
			bits[3] = src[3];
			bits += 4;
			src += 4;
		}
	}
	//bgra rgba
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pDst);
	CTexture* pTexture = new CTexture(texture);
	pTexture->m_nWidth = nWidth;
	pTexture->m_nHeight = nHeight;

	//glDeleteTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, 0);
	return pTexture;
}













