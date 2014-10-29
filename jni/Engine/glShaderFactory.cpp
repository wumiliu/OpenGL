#include "glShaderFactory.h"
#include <string>
#include <fstream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

glShaderFactory::glShaderFactory()
{

}


glShaderFactory::~glShaderFactory()
{

}

GLuint glShaderFactory::complieShader(GLenum type, const char* shaderSrc)
{
	std::string path1 = "/mnt/sdcard/Android/111/log.txt";
#ifndef  _WIN32

#else
	path1 = "log.txt";
#endif // ! _WIN32
	GLint compiled;
	GLuint shader = glCreateShader(type);
	if (shader == 0) { return 0; }
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			char *infoLog = (char*)malloc(sizeof(char)* infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			std::string loger = infoLog;
			FILE* fp = fopen(path1.c_str(), "a+");
			fwrite(loger.c_str(), sizeof(char), loger.size(), fp);
			fclose(fp);
			free(infoLog);
		}
		glDeleteShader(shader);
		return 0;
	}
	path1 = "/mnt/sdcard/Android/111/good.txt";

#ifndef  _WIN32

#else
	path1 = "good.txt";
#endif // ! _WIN32

	FILE* fp = fopen(path1.c_str(), "a+");
	std::string good = "good!";
	fwrite(good.c_str(), sizeof(char), good.size(), fp);
	fclose(fp);

	return shader;
}

GLuint glShaderFactory::LoadShaders(const char * vertex_file_path, const char * fragment_file_path, bool bTexture)
{
	std::string path = "/mnt/sdcard/Android/111/";
#ifndef  _WIN32
	path += vertex_file_path;
#else
	path = vertex_file_path;
#endif // ! _WIN32



	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(path.c_str(), std::ios::in);
	if (VertexShaderStream.is_open()){
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	path = "/mnt/sdcard/Android/111/";

#ifndef  _WIN32
	path += fragment_file_path;
#else
	path = fragment_file_path;
#endif // ! _WIN32

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(path.c_str(), std::ios::in);
	if (FragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}


	GLuint VertexShaderID = complieShader(GL_VERTEX_SHADER, VertexShaderCode.c_str());
	GLuint FragmentShaderID = complieShader(GL_FRAGMENT_SHADER, FragmentShaderCode.c_str());

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	bTexture = false;
	if (bTexture)
	{
		glBindAttribLocation(ProgramID, 0, "vPosition");
		glBindAttribLocation(ProgramID, 1, "vTexCorrd");
	}
	else
	{
		glBindAttribLocation(ProgramID, 0, "position");
		glBindAttribLocation(ProgramID, 1, "color0");
	}


	glLinkProgram(ProgramID);

	GLint Result = GL_FALSE;
	GLint InfoLogLength = 0;
	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	if (!Result) {
		GLint infoLen = 0;
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			char *infoLog = (char*)malloc(sizeof(char)* infoLen);
			glGetProgramInfoLog(ProgramID, infoLen, NULL, infoLog);
			free(infoLog);
		}
		glDeleteProgram(ProgramID);
		return 0;
	}
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
}
