#pragma once
#include "CVertex.h"
class Math
{
	Math();
	~Math();

public:
	CVertex calc_vertex(CVertex p1, CVertex p2);
	float inner_product(CVertex vec1, CVertex vec2);
	float cross_product(CVertex vec1, CVertex vec2);
	float 
};
