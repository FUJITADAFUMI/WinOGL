#pragma once
#include<gl/GL.h>
#include"CShape.h"
class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();
	void Draw();

	void AppendShape();
	//CVertex* AppendVertex(float x, float y);

	void Append_vertex(float x, float y);
private:
	//�@���_���X�g�̃w�b�h
	CShape* shape_head = NULL;
	//�@���I�m�ۂ���Vertex���������
	void FreeShape();
};

