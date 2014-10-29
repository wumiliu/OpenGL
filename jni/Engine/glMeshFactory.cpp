#include "glMeshFactory.h"
#include "htype.h"
glMeshFactory::glMeshFactory()
{
}

glMeshFactory::~glMeshFactory()
{
}

glMeshFactory* glMeshFactory::GetInstancePtr()
{
	static glMeshFactory _instance;
	return &_instance;
}

glMeshFactory& glMeshFactory::GetInstance()
{
	return *GetInstancePtr();
}

GLuint glMeshFactory::CreateVertexBuffer(const void* vertexData, unsigned int vertexDataSize, glUsage::Code usage)
{
	InvalidateMeshState();
	GLuint vb = 0;
	//创建一个缓冲区
	glGenBuffers(1, &vb);
	//绑定缓冲区
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	//把数据拷贝到缓冲区
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, usage);
	InvalidateMeshState();
	return vb;
}

void glMeshFactory::InvalidateMeshState()
{
	//glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

GLuint glMeshFactory::CreateIndexBuffer(const void* indexData, unsigned int indexDataSize, glUsage::Code usage)
{
	GLuint ib = 0;
	glGenBuffers(1, &ib);
	InvalidateMeshState();
	//绑定索引缓冲区
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, usage);
	InvalidateMeshState();
	return ib;
}
