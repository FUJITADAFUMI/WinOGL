#include "pch.h"
#include "Math.h"

Math::Math()
{

}
Math::~Math()
{

}

//�x�N�g���v�Z
CVertex Math::calc_vertex(CVertex p1, CVertex p2)
{
	CVertex cv;
	cv.SetX(p2.GetX() - p1.GetX());
	cv.SetY(p2.GetY() - p1.GetY());
	return cv;
}
//���όv�Z
float Math::inner_product(CVertex vec1, CVertex vec2)
{
	float ip;
	ip = (vec1.GetX() * vec2.GetX()) + (vec1.GetY() * vec2.GetY());
	return ip;
}
//�O�όv�Z
float Math::cross_product(CVertex vec1, CVertex vec2)
{
	float cp;
	cp = (vec1.GetX() * vec2.GetY()) - (vec1.GetY() * vec2.GetX());
	return cp;
}


