#pragma once
#include<gl/GL.h>
#include"CVertex.h"
#include"CShape.h"
#include"Math.h"
#define _USE_MATH_DEFINES
#include <math.h>
class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();
	void Draw();

	void AppendShape();
	//CVertex* AppendVertex(float x, float y);

	void CreateShape(float x, float y);
	//���W��
	void SetAxisFlag();
	bool GetAxisFlag();
	//�_�I��
	void SetVertexFlag();
	bool GetVertexFlag();
	//�ʑI��
	void SetSurfaceFlag();
	bool GetSurfaceFlag();
	//���ݓ_
	void SelX(float x);
	void SelY(float y);
	float useX();
	float useY();

private:
	//�@���_���X�g�̃w�b�h
	//Math* math = NULL;
	CShape* shape_head = NULL;
	CShape* shape_final = NULL;
	//�@���I�m�ۂ���Vertex���������
	void FreeShape();
	//���W��
	void DrawAxis();
	bool AxisFlag=false;
	//�_�I��
	void VertexChoice(float x, float y);
	bool VertexFlag = false;
	//���ݓ_
	float X = 0;
	float Y = 0;
	//�ʑI��
	void SurfaceChoice(float x, float y);
	bool SurfaceFlag=false;
	Math math;
};

