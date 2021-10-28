#include "pch.h"
#include "Math.h"



//�x�N�g���v�Z
CVertex Math::calc_vertex(CVertex*p1, CVertex*p2)
{
	CVertex cv;
	cv.SetX(p2->GetX() - p1->GetX());
	cv.SetY(p2->GetY() - p1->GetY());
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

//2�_�Ԃ̋���
float Math::two_distance(CVertex vec1, CVertex vec2)
{
	float td;
	//���_2�[���_1
	float tdx= vec2.GetX()-vec1.GetX();
	float tdy= vec2.GetY() - vec1.GetY();
	//��L��2��
	float tdxx = tdx * tdx;
	float tdyy = tdy * tdy;

	td = sqrt(tdxx+tdyy);
	return td;
}

//�Ȃ��p
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



