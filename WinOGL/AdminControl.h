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
	//�ړ��_
	void MvX(float x);
	void MvY(float y);
	float mvX();
	float mvY();
	//�ӑI��
	void SetEdgeFlag();
	bool GetEdgeFlag();
	//���_�ړ�
	void SetVtMoveFlag();
	bool GetVtMoveFlag();
	//�}�E�X���������ǂ���
	void SetVtmouseflag();
	bool GetVtmouseflag();
	void MoveIn(float x, float y);
	//�E�N���b�N������
	void SetRmouseflag();
	bool GetRmouseflag();
	//�E�N���b�N�_
	void RSelX(float x);
	void RSelY(float y);
	float RuseX();
	float RuseY();

	//�}�`�ړ��������ǂ���
	void SetShapeMoovflag();
	bool GetShapeMoovflag();
	//�}�`�ړ�����
	void ShapeMvHouse();
	//�g��k��
	void LargeReduce(float zDelta);
	//��]
	void Rotate(float zDelta);

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
	CShape* RtShape = NULL;
	//���ݓ_
	float X = 0;
	float Y = 0;
	//�E�N���b�N�_
	float RX = 0;
	float RY = 0;
	//�ʑI��
	void SurfaceChoice(float x, float y);
	bool SurfaceFlag=false;
	CShape* SelectSf=NULL;
	Math math;
	//�ӑI��
	void EdgeChoice(float x, float y);
	bool EdgeFlag = false;
	//���_�}��
	//q=sa+tb;
	CVertex Vta;
	CVertex Vtb;
	int debaccount = 0;
	//���_�ړ�
	void VertexMove(float x, float y);
	bool VtMoveFlag = false;
	CVertex* VtMove=NULL;
	CVertex* VtpreMove = NULL;
	CVertex* VtnextMove = NULL;
	//�}�E�X���������ǂ���
	bool mouseflag = false;
	//���_�}��
	void VertexInsert(float x, float y);
	void Insert(float x, float y);
	//���_�폜
	void VertexDel(float x, float y);
	bool Del( CShape* delS);
	//�}�`�ړ�
	void ShapeMoov(float x, float y, float mx, float my);
	////��̏������������H
	bool ShapeMoovflag = false;
	CVertex diffvt;
	//���������}�`�̓_���}�`�̒��ɂ���
	bool Inoutshape(CShape* selsp);
	//�}�`�̓_�����������}�`�̒��ɂ���
	bool OtherInoutshape(CShape* selsp);
	//��������
	bool Crossshape(CShape* selsp);
	//�E�N���b�N������
	bool Rmouseflag = false;
	//�g��k���̂Ƃ��_���}�`�̒��ɂ���
	bool CAdminControl::LRInoutshape(CShape* selsp, float a);
	//�g��k���̂Ƃ��_�����������}�`�̒��ɂ���
	bool CAdminControl::LROtherInoutsp(CShape* selsp, float a);
	bool LRflag = false;
	//��]�̂Ƃ��_���}�`�̒��ɂ���
	bool CAdminControl::RTInoutshape(CShape* selsp, double tha);
	//��]�̂Ƃ��_�����������}�`�̒��ɂ���
	bool CAdminControl::RTOtherInoutsp(CShape* selsp, double tha);
	//��]��������
	bool CAdminControl::RTCrossshape(CShape* selsp, double tha);
	bool RTflag = false;
};

