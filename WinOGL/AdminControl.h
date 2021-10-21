#pragma once
#include<gl/GL.h>
#include"CVertex.h"
#include"CShape.h"
#include"Math.h"
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
	Math* math = NULL;
	CShape* shape_head = NULL;
	CShape* shape_final = NULL;
	//　動的確保したVertexを解放する
	void FreeShape();

};

