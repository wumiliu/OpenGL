#include "glEnums.h"
/************************************************************************/
/*     http://msdn.microsoft.com/zh-cn/library/windows/apps/dn166871.aspx
		���� glGenBuffers ����һ����������������������ظ����ǡ�
		���� glBindBuffer ���建�����Ĳ��֣��� GL_ELEMENT_ARRAY_BUFFER��
		���� glBufferData ���ض������е��ض����ݣ��綥��ṹ���������ݻ���ɫ���ݣ���仺������

		ʹ�� glBindBuffer ���ض������ݡ�
		���� glVertexAttribPointer ����һ����������Ԫ����������ȷ�����Դ�С��ƫ�ơ����ÿ������ִ�иò�����
		ʹ�� glEnableVertexAttribArray ���ö������ݲ�����Ϣ��

*/
/************************************************************************/
class  glMeshFactory
{

public:
	static glMeshFactory* GetInstancePtr();
	static glMeshFactory& GetInstance();
	GLuint CreateVertexBuffer(const void* vertexData, unsigned int vertexDataSize, glUsage::Code usage);

	GLuint CreateIndexBuffer(const void* indexData, unsigned int indexDataSize, glUsage::Code usage);
private:
	glMeshFactory();
	~glMeshFactory();
	void InvalidateMeshState();

};

#define  g_MeshFactory glMeshFactory::GetInstance()