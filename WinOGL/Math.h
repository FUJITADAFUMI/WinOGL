#pragma once
#include "CVertex.h"
class Math
{

public:
	CVertex calc_vertex(CVertex*p1, CVertex*p2);
	float inner_product(CVertex vec1, CVertex vec2);
	float cross_product(CVertex vec1, CVertex vec2);
	float two_distance(CVertex vec1, CVertex vec2);
	float substend_angle(CVertex* p1, CVertex* p2, CVertex* nowp);
	float edgechoicejud(CVertex vec1, CVertex vec2, CVertex vec3);
	void Sets(float s);
	float Gets();
	void Sett(float t);
	float Gett();
private:
	float S;
	float T;
	//float DistanceCal();
};
