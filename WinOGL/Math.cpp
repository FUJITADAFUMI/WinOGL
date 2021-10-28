#include "pch.h"
#include "Math.h"



//ベクトル計算
CVertex Math::calc_vertex(CVertex*p1, CVertex*p2)
{
	CVertex cv;
	cv.SetX(p2->GetX() - p1->GetX());
	cv.SetY(p2->GetY() - p1->GetY());
	return cv;
}
//内積計算
float Math::inner_product(CVertex vec1, CVertex vec2)
{
	float ip;
	ip = (vec1.GetX() * vec2.GetX()) + (vec1.GetY() * vec2.GetY());
	return ip;
}
//外積計算
float Math::cross_product(CVertex vec1, CVertex vec2)
{
	float cp;
	cp = (vec1.GetX() * vec2.GetY()) - (vec1.GetY() * vec2.GetX());
	return cp;
}

//2点間の距離
float Math::two_distance(CVertex vec1, CVertex vec2)
{
	float td;
	//頂点2ー頂点1
	float tdx= vec2.GetX()-vec1.GetX();
	float tdy= vec2.GetY() - vec1.GetY();
	//上記の2乗
	float tdxx = tdx * tdx;
	float tdyy = tdy * tdy;

	td = sqrt(tdxx+tdyy);
	return td;
}

//なす角
float Math::substend_angle(CVertex* p1, CVertex* p2, CVertex* nowp)
{
	CVertex vec1= calc_vertex(nowp, p1);
	CVertex vec2= calc_vertex(nowp, p2);
	float sa;
	float in= inner_product(vec1,vec2);
	float cr= cross_product(vec1,vec2);

	/*if (cr<0) {
		cr = cr * -1;
	}*/
	sa = atan2(cr,in);
	return sa;
}



