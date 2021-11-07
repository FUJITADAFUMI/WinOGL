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
	//座標軸
	void SetAxisFlag();
	bool GetAxisFlag();
	//点選択
	void SetVertexFlag();
	bool GetVertexFlag();
	//面選択
	void SetSurfaceFlag();
	bool GetSurfaceFlag();
	//現在点
	void SelX(float x);
	void SelY(float y);
	float useX();
	float useY();

private:
	//　頂点リストのヘッド
	//Math* math = NULL;
	CShape* shape_head = NULL;
	CShape* shape_final = NULL;
	//　動的確保したVertexを解放する
	void FreeShape();
	//座標軸
	void DrawAxis();
	bool AxisFlag=false;
	//点選択
	void VertexChoice(float x, float y);
	bool VertexFlag = false;
	//現在点
	float X = 0;
	float Y = 0;
	//面選択
	void SurfaceChoice(float x, float y);
	bool SurfaceFlag=false;
	Math math;
};

