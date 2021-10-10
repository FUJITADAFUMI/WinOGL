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

	void CreateShape(float x, float y);
private:
	//　頂点リストのヘッド
	CShape* shape_head = NULL;
	//　動的確保したVertexを解放する
	void FreeShape();

	CShape CS;
};

