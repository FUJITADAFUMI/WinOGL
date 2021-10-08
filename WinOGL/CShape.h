#pragma once
#include"CVertex.h"
class CShape
{
public:
	CShape();
	~CShape();
	void AppendVertex(float new_x, float new_y);

private:
	CShape* next_shape;
	//�@���_���X�g�̃w�b�h
	CVertex* vertex_head = NULL;
	//�@���I�m�ۂ���Vertex���������
	void FreeVertex();

public:
	//�@���̌`�󃊃X�g���w���|�C���^����������
	void SetNext(CShape* new_vertexhead);
	//�@���̌`�󃊃X�g���w���|�C���^��ǂݍ���
	CShape* GetNext();

	void SetVertexhead(CVertex* new_next);
	//�@���̒��_���X�g���w���|�C���^��ǂݍ���
	CVertex* GetVertexhead();
};


