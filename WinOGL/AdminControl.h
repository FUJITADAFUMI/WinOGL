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
	//移動点
	void MvX(float x);
	void MvY(float y);
	float mvX();
	float mvY();
	//辺選択
	void SetEdgeFlag();
	bool GetEdgeFlag();
	//頂点移動
	void SetVtMoveFlag();
	bool GetVtMoveFlag();
	//マウス放したかどうか
	void SetVtmouseflag();
	bool GetVtmouseflag();
	void MoveIn(float x, float y);
	//右クリックしたか
	void SetRmouseflag();
	bool GetRmouseflag();
	//右クリック点
	void RSelX(float x);
	void RSelY(float y);
	float RuseX();
	float RuseY();

	//図形移動したかどうか
	void SetShapeMoovflag();
	bool GetShapeMoovflag();
	//図形移動処理
	void ShapeMvHouse();
	//拡大縮小
	void LargeReduce(float zDelta);
	//回転
	void Rotate(float zDelta);

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
	CShape* RtShape = NULL;
	//現在点
	float X = 0;
	float Y = 0;
	//右クリック点
	float RX = 0;
	float RY = 0;
	//面選択
	void SurfaceChoice(float x, float y);
	bool SurfaceFlag=false;
	CShape* SelectSf=NULL;
	Math math;
	//辺選択
	void EdgeChoice(float x, float y);
	bool EdgeFlag = false;
	//頂点挿入
	//q=sa+tb;
	CVertex Vta;
	CVertex Vtb;
	int debaccount = 0;
	//頂点移動
	void VertexMove(float x, float y);
	bool VtMoveFlag = false;
	CVertex* VtMove=NULL;
	CVertex* VtpreMove = NULL;
	CVertex* VtnextMove = NULL;
	//マウス放したかどうか
	bool mouseflag = false;
	//頂点挿入
	void VertexInsert(float x, float y);
	void Insert(float x, float y);
	//頂点削除
	void VertexDel(float x, float y);
	bool Del( CShape* delS);
	//図形移動
	void ShapeMoov(float x, float y, float mx, float my);
	////上の処理をしたか？
	bool ShapeMoovflag = false;
	CVertex diffvt;
	//動かした図形の点が図形の中にある
	bool Inoutshape(CShape* selsp);
	//図形の点が動かした図形の中にある
	bool OtherInoutshape(CShape* selsp);
	//交差判定
	bool Crossshape(CShape* selsp);
	//右クリックしたか
	bool Rmouseflag = false;
	//拡大縮小のとき点が図形の中にある
	bool CAdminControl::LRInoutshape(CShape* selsp, float a);
	//拡大縮小のとき点が動かした図形の中にある
	bool CAdminControl::LROtherInoutsp(CShape* selsp, float a);
	bool LRflag = false;
	//回転のとき点が図形の中にある
	bool CAdminControl::RTInoutshape(CShape* selsp, double tha);
	//回転のとき点が動かした図形の中にある
	bool CAdminControl::RTOtherInoutsp(CShape* selsp, double tha);
	//回転交差判定
	bool CAdminControl::RTCrossshape(CShape* selsp, double tha);
	bool RTflag = false;
};

