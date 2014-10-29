#pragma once

#include "htype.h"
#include <stddef.h>
#include <malloc.h>


class glShaderFactory
{
public:
	glShaderFactory();
	~glShaderFactory();

	GLuint complieShader(GLenum type, const char* shaderSrc);
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path,bool bTexture =false);
};

