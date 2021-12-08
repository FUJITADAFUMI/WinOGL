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

//辺選択判定
float Math::edgechoicejud(CVertex vec1, CVertex vec2, CVertex vec3)
{
	float min;
	//2点の距離
	//(p-b)
	float dis1 = 0;
	//(a-q)
	float dis2 = 0;
	//(a-b)
	float dis3 = 0;
	//s+t=1
	float s = 0;
	float t = 0;
	dis1 = two_distance(vec2, vec3);
	dis2 = two_distance(vec3, vec1);
	dis3 = two_distance(vec2, vec1);
	s = (dis1 * dis3) / (dis3 * dis3);
	t = (dis2 * dis3) / (dis3 * dis3);
	Sets(s);
	Sett(t);
	//s+t=1,0<=s<=1の判定
	if (s + t < 1.01 && s + t>0.99 && -0.01 < s && s < 1.01) {
		return min= s + t;
	}
	return 2;
}

void Math::Sets(float s)
{
	S = s;
}

float Math::Gets()
{
	return S;
}

void Math::Sett(float t)
{
	T = t;
}

float Math::Gett()
{
	return T;
}



