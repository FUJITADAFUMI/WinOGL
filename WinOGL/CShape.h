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
	//　頂点リストのヘッド
	CVertex* vertex_head = NULL;
	//　動的確保したVertexを解放する
	void FreeVertex();

public:
	//　次の形状リストを指すポインタを書き込む
	void SetNext(CShape* new_vertexhead);
	//　次の形状リストを指すポインタを読み込む
	CShape* GetNext();

	void SetVertexhead(CVertex* new_next);
	//　次の頂点リストを指すポインタを読み込む
	CVertex* GetVertexhead();
};


