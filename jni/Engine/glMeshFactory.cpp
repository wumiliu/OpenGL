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
	//����һ��������
	glGenBuffers(1, &vb);
	//�󶨻�����
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	//�����ݿ�����������
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
	//������������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, usage);
	InvalidateMeshState();
	return ib;
}
