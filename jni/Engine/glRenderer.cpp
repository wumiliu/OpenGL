#include "glRenderer.h"
#include "glShaderFactory.h"
#include "glMeshFactory.h"
#include "OpenGLEngine.h"
#include "Texture.h"
#include <stddef.h>


VertexPositionNormalTexture  myCubeVertic[] = {
	{ XMFLOAT3(0.5, 0.5, 0.5), XMFLOAT3(0, 0, 1), XMFLOAT2(1, 0) },
	{ XMFLOAT3(0.5, -0.5, 0.5), XMFLOAT3(0, 0, 1), XMFLOAT2(1, 1) },
	{ XMFLOAT3(-0.5, -0.5, 0.5), XMFLOAT3(0, 0, 1), XMFLOAT2(0, 1) },
	{ XMFLOAT3(-0.5, 0.5, 0.5), XMFLOAT3(0, 0, 1), XMFLOAT2(0, 0) },
	{ XMFLOAT3(-0.5, 0.5, -0.5), XMFLOAT3(0, 0, -1), XMFLOAT2(1, 0) },
	{ XMFLOAT3(-0.5, -0.5, -0.5), XMFLOAT3(0, 0, -1), XMFLOAT2(1, 1) },
	{ XMFLOAT3(0.5, -0.5, -0.5), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 1) },
	{ XMFLOAT3(0.5, 0.5, -0.5), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
	{ XMFLOAT3(0.5, 0.5, -0.5), XMFLOAT3(1, 0, 0), XMFLOAT2(1, 0) },
	{ XMFLOAT3(0.5, -0.5, -0.5), XMFLOAT3(1, 0, 0), XMFLOAT2(1, 1) },
	{ XMFLOAT3(0.5, -0.5, 0.5), XMFLOAT3(1, 0, 0), XMFLOAT2(0, 1) },
	{ XMFLOAT3(0.5, 0.5, 0.5), XMFLOAT3(1, 0, 0), XMFLOAT2(0, 0) },
	{ XMFLOAT3(-0.5, 0.5, 0.5), XMFLOAT3(-1, 0, 0), XMFLOAT2(1, 0) },
	{ XMFLOAT3(-0.5, -0.5, 0.5), XMFLOAT3(-1, 0, 0), XMFLOAT2(1, 1) },
	{ XMFLOAT3(-0.5, -0.5, -0.5), XMFLOAT3(-1, 0, 0), XMFLOAT2(0, 1) },
	{ XMFLOAT3(-0.5, 0.5, -0.5), XMFLOAT3(-1, 0, 0), XMFLOAT2(0, 0) },
	{ XMFLOAT3(-0.5, 0.5, 0.5), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0) },
	{ XMFLOAT3(-0.5, 0.5, -0.5), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1) },
	{ XMFLOAT3(0.5, 0.5, -0.5), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1) },
	{ XMFLOAT3(0.5, 0.5, 0.5), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0) },
	{ XMFLOAT3(0.5, -0.5, 0.5), XMFLOAT3(0, -1, 0), XMFLOAT2(1, 0) },
	{ XMFLOAT3(0.5, -0.5, -0.5), XMFLOAT3(0, -1, 0), XMFLOAT2(1, 1) },
	{ XMFLOAT3(-0.5, -0.5, -0.5), XMFLOAT3(0, -1, 0), XMFLOAT2(0, 1) },
	{ XMFLOAT3(-0.5, -0.5, 0.5), XMFLOAT3(0, -1, 0), XMFLOAT2(0, 0) }
};

glRenderer* glRenderer::GetInstancePtr()
{
	static glRenderer _instance;
	return &_instance;
}

glRenderer& glRenderer::GetInstance()
{
	return *GetInstancePtr();
}


glRenderer::glRenderer()
{
	InitReSource();
}


glRenderer::~glRenderer()
{
}

void glRenderer::ShowRect(int x1, int y1, int x2, int y2)
{
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	static float rotateY = 0.0f;




	//Model = glm::rotate(Model, rotateY, glm::vec3(0.0f, 1.0f, 0.0f));
	//Model = glm::scale(Model, glm::vec3(1.5f, 1.5f, 1.0f));
	//Model = glm::translate(Model, glm::vec3(-1, 0, 0.8));



	rotateY++;
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around


	glUseProgram(programObj);
	GLuint MatrixID = glGetUniformLocation(programObj, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Model[0][0]);
	//IASetVertexBuffers
	//	glBindVertexArray(vao);


	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	static const GLfloat g_vertex_buffer_data1[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vertex_buffer_data1), g_vertex_buffer_data1);
	//IASetIndexBuffer

	//类似DX IASetInputLayout
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	//绑定顶点颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_TEXTURE_2D, 0);

	//启用顶点数据布局信息
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	// Draw the triangle !
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthFunc(GL_LESS);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
}

void glRenderer::ShowRectEx(int x1, int y1, int x2, int y2, DX_SCREEN_COLOR _color, float fRotate, float fScaleX, float fScaleY)
{
	glm::mat4 Projection = glm::ortho(0.0f, (float)g_objBase.m_nWidth, (float)g_objBase.m_nHeight, 0.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !


	int x = x1;
	int y = y1;
	int h = y2 - y1;
	int w = x2 - x1;

	VertexPositionColor g_vertex_buffer[4] = {
		VertexPositionColor(DX_SCREEN_VERTEX(x, (y + h), 0.0f), _color),
		VertexPositionColor(DX_SCREEN_VERTEX(x, y, 0.0f), _color),
		VertexPositionColor(DX_SCREEN_VERTEX(x + w, y, 0.0f), _color),
		VertexPositionColor(DX_SCREEN_VERTEX(x + w, (y + h), 0.0f), _color)
	};


	VertexPositionColor pVertexs[] =
	{
		VertexPositionColor(DX_SCREEN_VERTEX(-1.0f, -1.0f, 0.0f), _color),
		VertexPositionColor(DX_SCREEN_VERTEX(1.0f, -1.0f, 0.0f), _color),
		VertexPositionColor(DX_SCREEN_VERTEX(0.5f, 1.0f, 0.0f), _color),
		VertexPositionColor(DX_SCREEN_VERTEX(0.0f, 1.0f, 0.0f), _color)
	};

	fRotate = glm::degrees(fRotate);
	Model = glm::translate(Model, glm::vec3(x, y, 0));//在移回原来位置
	Model = glm::rotate(Model, fRotate, glm::vec3(0.0f, 0.0f, 1.0f));//在旋转
	Model = glm::scale(Model, glm::vec3(fScaleX, fScaleY, 1.0f));//在缩放
	Model = glm::translate(Model, glm::vec3(-x, -y, 0)); //先移到原点

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection *Model; // Remember, matrix multiplication is the other way around

	glUseProgram(programTextureObj);
	GLuint MatrixID = glGetUniformLocation(programTextureObj, "gTex");
	LOGD("programObj = %d,programTextureObj = %d, TMVP = %d",programObj,programTextureObj,MatrixID);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


	glUseProgram(programObj);
	 MatrixID = glGetUniformLocation(programObj, "MVP");
	LOGD("programObj MatrixID = %d",MatrixID);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	//IASetVertexBuffers
	//	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vertex_buffer), g_vertex_buffer);
	//IASetIndexBuffer

	//类似DX IASetInputLayout
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionColor),                  // stride
		(const GLvoid*)offsetof(VertexPositionColor, _pos)           // array buffer offset
		);
	int nSize = offsetof(VertexPositionColor, _pos);
	nSize = offsetof(VertexPositionColor, _color);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionColor),                  // stride
		(const GLvoid*)offsetof(VertexPositionColor, _color)           // array buffer offset
		);


	//启用顶点数据布局信息
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
	
}


void glRenderer::InitReSource()
{
	glShaderFactory factory;
	//programObj = factory.LoadShaders("shader\\base.vs", "shader\\base.ps");
	//programTextureObj = factory.LoadShaders("shader\\baseTexture.vs", "shader\\baseTexture.ps");

	programObj = factory.LoadShaders("base.vs", "base.ps");
	programTextureObj = factory.LoadShaders("baseTexture.vs", "baseTexture.ps");
	float triColor[150 * 3];
	triColor[0] = 0;    triColor[1] = 1;    triColor[2] = 0;
	triColor[3] = 0;    triColor[4] = 1;    triColor[5] = 0;
	triColor[6] = 0;    triColor[7] = 1;    triColor[8] = 0;
	triColor[9] = 0;    triColor[10] = 1;    triColor[11] = 0;

	//产生VBO
	glGenBuffers(1, &uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), triColor, GL_STATIC_DRAW);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[150 * 6] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};
	GLushort  g_index_buffer_data[] = {
		0, 1, 2, 0, 2, 3, 4, 5, 6,
		4, 6, 7, 8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15, 16, 17, 18,
		16, 18, 19, 20, 21, 22, 20, 22, 23
	};
	vertexbuffer = g_MeshFactory.CreateVertexBuffer(g_vertex_buffer_data, sizeof(g_vertex_buffer_data), glUsage::Static);
	indexbuffer = g_MeshFactory.CreateIndexBuffer(g_index_buffer_data, sizeof(g_index_buffer_data), glUsage::Static);




	VertexPositionTexture g_vertexT_buffer_data[4] = {
		{ XMFLOAT3(0.5, 0.5, 0.5), XMFLOAT2(1, 0) },
		{ XMFLOAT3(0.5, 0.5, 0.5), XMFLOAT2(1, 0) },
		{ XMFLOAT3(0.5, 0.5, 0.5), XMFLOAT2(1, 0) },
		{ XMFLOAT3(0.5, 0.5, 0.5), XMFLOAT2(1, 0) }

	};
	vertexTBuffer = g_MeshFactory.CreateVertexBuffer(g_vertexT_buffer_data, sizeof(g_vertexT_buffer_data), glUsage::Static);





}
void CalcCircleDot(VertexPositionColor vCenter, VertexPositionColor& vDot, int nRadius, float fAlpha, const DX_SCREEN_COLOR& _color)
{
	// 角度=弧度除以π再乘以180
	float x = nRadius * cosf(fAlpha);
	float y = nRadius * sinf(fAlpha);
	vDot._pos.x = vCenter._pos.x + x;
	vDot._pos.y = vCenter._pos.y + y;
	vDot._pos.z = vCenter._pos.z;
	vDot._color = _color;
}

void glRenderer::DrawCircle(int nX, int nY, int nRadius, DX_SCREEN_COLOR _color, float fRotate)
{
	glm::mat4 Projection = glm::ortho(0.0f, (float)g_objBase.m_nWidth, (float)g_objBase.m_nHeight, 0.0f);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !


	VertexPositionColor verts[150] = {
	};

	float fDetaAngle = 2 * 3.1415927f / 50;
	verts[0]._pos.x = (float)nX;
	verts[0]._pos.z = 0.0f;
	verts[0]._pos.y = (float)nY;
	verts[0]._color = _color;
	verts[1]._pos.x = (float)nRadius + nX;
	verts[1]._pos.z = 0.0f;
	verts[1]._pos.y = (float)nY;
	verts[1]._color = _color;

	float fAngle = fDetaAngle;
	CalcCircleDot(verts[0], verts[2], nRadius, fAngle, _color);
	for (int i = 1; i < 50; i++)
	{
		verts[i * 3] = verts[0];
		verts[i * 3 + 1] = verts[(i - 1) * 3 + 2];
		fAngle += fDetaAngle;
		CalcCircleDot(verts[0], verts[i * 3 + 2], nRadius, fAngle, _color);
	}

	int x = nX - nRadius;
	int y = nY - nRadius;
	fRotate = glm::degrees(fRotate);//角度
	Model = glm::translate(Model, glm::vec3(x, y, 0));//在移回原来位置
	Model = glm::rotate(Model, fRotate, glm::vec3(0.0f, 0.0f, 1.0f));//在旋转
	Model = glm::translate(Model, glm::vec3(-x, -y, 0)); //先移到原点

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection *Model; // Remember, matrix multiplication is the other way around

	glUseProgram(programObj);
	GLuint MatrixID = glGetUniformLocation(programObj, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	//IASetVertexBuffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	int nSize = sizeof(verts);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
	//IASetIndexBuffer

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionColor),                  // stride
		(const GLvoid*)offsetof(VertexPositionColor, _pos)           // array buffer offset
		);
	nSize = offsetof(VertexPositionColor, _pos);
	nSize = offsetof(VertexPositionColor, _color);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionColor),                  // stride
		(const GLvoid*)offsetof(VertexPositionColor, _color)           // array buffer offset
		);


	//启用顶点数据布局信息
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_LINE_LOOP, 0, 150);

}

void glRenderer::DrawCircleEx(int nX, int nY, int nRadius, DX_SCREEN_COLOR _color /*= DX_SCREEN_COLOR(1, 1, 1)*/, float fRotate /*= 0.0f*/)
{
	glm::mat4 Projection = glm::ortho(0.0f, (float)g_objBase.m_nWidth, (float)g_objBase.m_nHeight, 0.0f);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !


	VertexPositionColor verts[50];

	float fDetaAngle = 2 * 3.1415927f / 50;
	float fAngle = fDetaAngle;
	VertexPositionColor _tmp;
	_tmp._pos.x = (float)nX;
	_tmp._pos.z = 0.5f;
	_tmp._pos.y = (float)nY;
	_tmp._color = _color;
	verts[0] = _tmp;
	for (int i = 0; i < 50; i++)
	{
		fAngle += fDetaAngle;
		CalcCircleDot(_tmp, verts[i], nRadius, fAngle, _color);
	}
	int x = nX - nRadius;
	int y = nY - nRadius;
	fRotate = glm::degrees(fRotate);//角度
	Model = glm::translate(Model, glm::vec3(x, y, 0));//在移回原来位置
	Model = glm::rotate(Model, fRotate, glm::vec3(0.0f, 0.0f, 1.0f));//在旋转
	Model = glm::translate(Model, glm::vec3(-x, -y, 0)); //先移到原点

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection *Model; // Remember, matrix multiplication is the other way around

	glUseProgram(programObj);
	GLuint MatrixID = glGetUniformLocation(programObj, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	//IASetVertexBuffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	int nSize = sizeof(verts);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
	//IASetIndexBuffer

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionColor),                  // stride
		(const GLvoid*)offsetof(VertexPositionColor, _pos)           // array buffer offset
		);
	nSize = offsetof(VertexPositionColor, _pos);
	nSize = offsetof(VertexPositionColor, _color);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionColor),                  // stride
		(const GLvoid*)offsetof(VertexPositionColor, _color)           // array buffer offset
		);


	//启用顶点数据布局信息
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glDisable(GL_DEPTH_FUNC);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_LINE_LOOP, 0, 50);
}

void glRenderer::DrawCube(int n)
{

	glm::mat4 Projection = glm::perspectiveFov(45.0f, (float)g_objBase.m_nWidth, (float)g_objBase.m_nHeight, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	static float rotateY = 0.0f;

	if (n == 0)
	{
		Model = glm::translate(Model, glm::vec3(0.0, 0.0, 0.0));
	}
	else
	{
		Model = glm::translate(Model, glm::vec3(1.0, -1.0, 0.5));
	}


	//	Model = glm::rotate(Model, rotateY, glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::scale(Model, glm::vec3(3.5f, 3.5f, 3.5f));
	rotateY += 2;




	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

	glUseProgram(programObj);
	GLuint MatrixID = glGetUniformLocation(programObj, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	//IASetVertexBuffers

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	int nSize = sizeof(myCubeVertic);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(myCubeVertic), myCubeVertic);
	//IASetIndexBuffer

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionNormalTexture),                  // stride
		(const GLvoid*)offsetof(VertexPositionNormalTexture, _pos)           // array buffer offset
		);
	nSize = offsetof(VertexPositionNormalTexture, _pos);
	nSize = offsetof(VertexPositionNormalTexture, _color);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionNormalTexture),                  // stride
		(const GLvoid*)offsetof(VertexPositionNormalTexture, _color)           // array buffer offset
		);


	//启用顶点数据布局信息
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDrawArrays(GL_LINE_LOOP, 0, 24);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthFunc(GL_LESS);//如果目标像素z值＝当前像素z值，则绘制目标像素
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)0);


}

void glRenderer::ShowTexture(int x1, int y1, int x2, int y2, GLuint TextureId)
{

	glm::mat4 Projection = glm::ortho(0.0f, (float)g_objBase.m_nWidth, (float)g_objBase.m_nHeight, 0.0f);
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !


	int x = x1;
	int y = y1;
	int h = y2 - y1;
	int w = x2 - x1;

	VertexPositionTexture g_vertex_buffer[4] = {
		VertexPositionTexture(XMFLOAT3(x, (y + h), 0.0f), XMFLOAT2(0, 0)),
		VertexPositionTexture(XMFLOAT3(x, y, 0.0f), XMFLOAT2(0, 1)),
		VertexPositionTexture(XMFLOAT3(x + w, y, 0.0f), XMFLOAT2(1, 1)),
		VertexPositionTexture(XMFLOAT3(x + w, (y + h), 0.0f), XMFLOAT2(1, 0))
	};

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection *Model; // Remember, matrix multiplication is the other way around


	// Use our shader
	glUseProgram(programTextureObj);
	GLuint MatrixID = glGetUniformLocation(programTextureObj, "MVP");
	LOGD("MatrixID = %d",MatrixID);

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


	GLuint gTexID = glGetUniformLocation(programTextureObj, "gTex");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureId);
	glUniform1i(gTexID, 0);
	//LOGD("%d,%d,%d",MatrixID,gTexID,TextureId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexTBuffer);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vertex_buffer), g_vertex_buffer);
	//IASetIndexBuffer

	//类似DX IASetInputLayout
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionTexture),                  // stride
		(const GLvoid*)offsetof(VertexPositionTexture, _pos)           // array buffer offset
		);
	int nSize = offsetof(VertexPositionTexture, _pos);
	nSize = offsetof(VertexPositionTexture, _uv);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionTexture),                  // stride
		(const GLvoid*)offsetof(VertexPositionTexture, _uv)           // array buffer offset
		);


	//启用顶点数据布局信息
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//glBindTexture(GL_TEXTURE_2D, TextureId);
	// Use our shader

	glEnable(GL_BLEND);
	//glBlendFunc(GL_COMBINE_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle

}

void glRenderer::ShowTexture(int x1, int y1, CTexture* pTexture)
{

	ShowTexture(x1, y1, x1 + pTexture->m_nWidth, y1 + pTexture->m_nHeight, pTexture->m_TextureId);
}

void glRenderer::ShowTextureEx(int x, int y, RECT *pSrc, int nWidth, int nHeight, CTexture*pTexture, float fRotate /*= 0.0f*/)
{
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	fRotate = glm::degrees(fRotate);

	Model = glm::translate(Model, glm::vec3(x, y, 0));//在移回原来位置
	Model = glm::rotate(Model, fRotate, glm::vec3(0.0f, 0.0f, 1.0f));//在旋转
	Model = glm::translate(Model, glm::vec3(-x, -y, 0)); //先移到原点

	ShowTextureEx(x, y, pSrc, nWidth, nHeight, pTexture, Model);
}

void glRenderer::ShowTextureEx(int x, int y, RECT *pSrc, int nWidth, int nHeight, CTexture*pTexture, glm::mat4 Model/*= glm::mat4(1.0f)*/)
{
	glm::mat4 Projection = glm::ortho(0.0f, (float)g_objBase.m_nWidth, (float)g_objBase.m_nHeight, 0.0f);

	LOGI("Width = %d,Height = %d",pTexture->m_nWidth,pTexture->m_nHeight);
	int h = nHeight;
	int w = nWidth;

	VertexPositionTexture g_vertex_buffer[4] = {
		VertexPositionTexture(XMFLOAT3(x, (y + h), 0.0f), XMFLOAT2(0, 0)),
		VertexPositionTexture(XMFLOAT3(x, y, 0.0f), XMFLOAT2(0, 1)),
		VertexPositionTexture(XMFLOAT3(x + w, y, 0.0f), XMFLOAT2(1, 1)),
		VertexPositionTexture(XMFLOAT3(x + w, (y + h), 0.0f), XMFLOAT2(1, 0))
	};

	//opengl uv  00 01 11 10
	//设置uv纹理坐标，截取贴图，这里是在确定(u,v)贴图左上坐标(x,y)
	g_vertex_buffer[0]._uv.x = g_vertex_buffer[1]._uv.x = float(pSrc->left) / (float)pTexture->m_nWidth;
	g_vertex_buffer[0]._uv.y = g_vertex_buffer[3]._uv.y = float(pSrc->top) / (float)pTexture->m_nHeight;;

	//这里是在确定(u,v)贴图右下坐标(x,y)

	g_vertex_buffer[2]._uv.x = g_vertex_buffer[3]._uv.x = float(pSrc->right) / (float)pTexture->m_nWidth;
	g_vertex_buffer[2]._uv.y = g_vertex_buffer[1]._uv.y = float(pSrc->bottom) / (float)pTexture->m_nHeight;
	// Our ModelViewProjection : multiplication of our 3 matrices


	glm::mat4 MVP = Projection *Model; // Remember, matrix multiplication is the other way around

	// Use our shader
	glUseProgram(programTextureObj);
	GLuint MatrixID = glGetUniformLocation(programTextureObj, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	GLuint gTexID = glGetUniformLocation(programTextureObj, "gTex");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pTexture->m_TextureId);
	glUniform1i(gTexID, 0);

	//IASetVertexBuffers
	//	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexTBuffer);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vertex_buffer), g_vertex_buffer);
	//IASetIndexBuffer

	//类似DX IASetInputLayout
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionTexture),                  // stride
		(const GLvoid*)offsetof(VertexPositionTexture, _pos)           // array buffer offset
		);
	int nSize = offsetof(VertexPositionTexture, _pos);
	nSize = offsetof(VertexPositionTexture, _uv);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionTexture),                  // stride
		(const GLvoid*)offsetof(VertexPositionTexture, _uv)           // array buffer offset
		);


	//启用顶点数据布局信息
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	//glDisEnable(GL_BLEND);
	//glBlendFunc(GL_COMBINE_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_COMBINE_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
}


void glRenderer::ShowTexture(int x, int y, RECT *pSrc, int nWidth, int nHeight, CTexture*pTexture, glm::mat4 Model /*= glm::mat4(1.0f)*/)
{
	//	glm::mat4 Projection = glm::ortho(0.0f, (float)g_objBase.m_nWidth, (float)g_objBase.m_nHeight, 0.0f);
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 6), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	int h = nHeight;
	int w = nWidth;
	//	Model = glm::mat4(1.0f);  // Changes for each model !

	VertexPositionTexture g_vertex_buffer[4] = {
		VertexPositionTexture(XMFLOAT3(0, 1, 0.0f), XMFLOAT2(0, 0)),
		VertexPositionTexture(XMFLOAT3(0, 0, 0.0f), XMFLOAT2(0, 1)),
		VertexPositionTexture(XMFLOAT3(1, 0, 0.0f), XMFLOAT2(1, 1)),
		VertexPositionTexture(XMFLOAT3(1, 1, 0.0f), XMFLOAT2(1, 0))
	};

	//设置uv纹理坐标，截取贴图，这里是在确定(u,v)贴图左上坐标(x,y)
	g_vertex_buffer[0]._uv.x = g_vertex_buffer[1]._uv.x = float(pSrc->left) / (float)pTexture->m_nWidth;
	g_vertex_buffer[0]._uv.y = g_vertex_buffer[3]._uv.y = float(pSrc->bottom) / (float)pTexture->m_nHeight;;

	//这里是在确定(u,v)贴图右下坐标(x,y)

	g_vertex_buffer[2]._uv.x = g_vertex_buffer[3]._uv.x = float(pSrc->right) / (float)pTexture->m_nWidth;
	g_vertex_buffer[2]._uv.y = g_vertex_buffer[1]._uv.y = float(pSrc->top) / (float)pTexture->m_nHeight;
	// Our ModelViewProjection : multiplication of our 3 matrices


	glm::mat4 MVP = Projection* View *Model; // Remember, matrix multiplication is the other way around

	// Use our shader
	glUseProgram(programTextureObj);
	GLuint MatrixID = glGetUniformLocation(programObj, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	//IASetVertexBuffers
	//	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexTBuffer);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vertex_buffer), g_vertex_buffer);
	//IASetIndexBuffer

	//类似DX IASetInputLayout
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionTexture),                  // stride
		(const GLvoid*)offsetof(VertexPositionTexture, _pos)           // array buffer offset
		);
	int nSize = offsetof(VertexPositionTexture, _pos);
	nSize = offsetof(VertexPositionTexture, _uv);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(VertexPositionTexture),                  // stride
		(const GLvoid*)offsetof(VertexPositionTexture, _uv)           // array buffer offset
		);


	//启用顶点数据布局信息
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindTexture(GL_TEXTURE_2D, pTexture->m_TextureId);
	// Use our shader

	//glDisEnable(GL_BLEND);
	//glBlendFunc(GL_COMBINE_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_COMBINE_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
}

