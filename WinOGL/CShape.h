#pragma once
#include"CVertex.h"
#include"Math.h"
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
	Math math;
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

	boolean cross_judge(CVertex* vec1, CVertex* vec2, CVertex* vec3, CVertex* vec4/*float new_x, float new_y*/);
	boolean cross_other(CVertex* Be, CShape* shape_head);
	boolean cross(CVertex* Be);
	boolean cross_last(CVertex* Be);
	boolean inout_judge(CVertex* Be, CShape* shape_head);
	boolean inout_zu_judge(CShape* shape_head, CShape* shape_final);
};




