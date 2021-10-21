#pragma once
#include"CVertex.h"
class CShape
{
public:
	CShape();
	CShape::CShape(CVertex* new_vertexhead);
	~CShape();
	void AppendVertex(float new_x, float new_y);

private:
	CShape* next_shape = NULL;
	//�@���_���X�g�̃w�b�h
	CVertex* vertex_head = NULL;
	//�@���I�m�ۂ���Vertex���������
	CShape* pre_shape = NULL;
	CVertex* pre_vertex = NULL;
	CVertex* vertex_final = NULL;
	void FreeVertex();

public:
	//�@���̌`�󃊃X�g���w���|�C���^����������
	void SetNext(CShape* new_vertexhead);
	//�@���̌`�󃊃X�g���w���|�C���^��ǂݍ���
	CShape* GetNext();

	void SetVertexhead(CVertex* new_next);
	//�@���̒��_���X�g���w���|�C���^��ǂݍ���
	CVertex* GetVertexhead();

	CShape* Getpreshape();
	void Setpreshape(CShape* new_pre);
	CVertex* Getvertexfinal();

    int Count();

	boolean cross_judge(CVertex* vec1, CVertex* vec2, CVertex* vec3, float new_x, float new_y);
	boolean cross(float new_x, float new_y);
	//(CVertex* v1s, CVertex* v1e, CVertex* v2s, CVertex* v2e);
	boolean cross_other(float new_x, float new_y, CShape* shape_head);
	/*(CVertex* v2s, CVertex* v2e, CShape* shs, CShape* she);*/
};




