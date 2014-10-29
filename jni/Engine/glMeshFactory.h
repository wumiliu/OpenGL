#include "glEnums.h"
/************************************************************************/
/*     http://msdn.microsoft.com/zh-cn/library/windows/apps/dn166871.aspx
		调用 glGenBuffers 生成一个或多个缓冲区并将句柄返回给它们。
		调用 glBindBuffer 定义缓冲区的布局，如 GL_ELEMENT_ARRAY_BUFFER。
		调用 glBufferData 用特定布局中的特定数据（如顶点结构、索引数据或颜色数据）填充缓冲区。

		使用 glBindBuffer 上载顶点数据。
		调用 glVertexAttribPointer 可在一个顶点数据元素内设置正确的属性大小和偏移。针对每个属性执行该操作。
		使用 glEnableVertexAttribArray 启用顶点数据布局信息。

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