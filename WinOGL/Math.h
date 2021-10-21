#pragma once
#include "CVertex.h"
#include"CShape.h"
class Math
{
	Math();
	~Math();

public:
	CVertex calc_vertex(CVertex*p1, CVertex*p2);
	float inner_product(CVertex vec1, CVertex vec2);
	float cross_product(CVertex vec1, CVertex vec2);
	float two_distance(CVertex vec1, CVertex vec2);
	/*boolean cross_judge(CVertex* vec1, CVertex* vec2, CVertex* vec3, CVertex* vec4);
	boolean cross(CVertex* v1s, CVertex* v1e, CVertex* v2s, CVertex* v2e);
	boolean cross_other(CVertex* v2s, CVertex* v2e, CShape* shs, CShape* she); */
};
