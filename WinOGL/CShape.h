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
	//　頂点リストのヘッド
	CVertex* vertex_head = NULL;
	//　動的確保したVertexを解放する
	CShape* pre_shape = NULL;
	CVertex* pre_vertex = NULL;
	CVertex* vertex_final = NULL;
	void FreeVertex();

public:
	//　次の形状リストを指すポインタを書き込む
	void SetNext(CShape* new_vertexhead);
	//　次の形状リストを指すポインタを読み込む
	CShape* GetNext();

	void SetVertexhead(CVertex* new_next);
	//　次の頂点リストを指すポインタを読み込む
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




