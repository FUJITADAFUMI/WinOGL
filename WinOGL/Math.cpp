#include "pch.h"
#include "Math.h"

Math::Math()
{

}
Math::~Math()
{

}

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


//��������
/*boolean Math::cross_judge(CVertex* vec1, CVertex* vec2, CVertex* vec3, CVertex* vec4)
{
	CVertex a, b, a1, b1, a2, b2;
	float ca1, ca2, cb1, cb2;
	a = calc_vertex(vec1, vec2);
	b = calc_vertex(vec3, vec4);
	a1 = calc_vertex(vec1, vec3);
	b1 = calc_vertex(vec3, vec1);
	a2 = calc_vertex(vec1, vec4);
	b2 = calc_vertex(vec3, vec2);

	ca1 = a.GetX() * a1.GetY() - a1.GetX() * a.GetY();
	ca2 = a.GetX() * a2.GetY() - a2.GetX() * a.GetY();
	cb1 = b.GetX() * b1.GetY() - b1.GetX() * b.GetY();
	cb2 = b.GetX() * b2.GetY() - b2.GetX() * b.GetY();

	if (ca1 * ca2 <= 0 && cb1 * cb2 <= 0)
	{
		return true;
	}
	return false;
}

boolean Math::cross(CVertex* v1s, CVertex* v1e, CVertex* v2s, CVertex* v2e) {


	if (v1s->GetX() == v2e->GetX() && v1s->GetY() == v2e->GetY())  //�n�_�ƏI�_�������ꍇ
	{
		v1s = v2e;
		v2e = v2e->GetNext();
	}

	while (v1e != v2s) {

		if (cross_judge(v1s, v1e, v2s, v2e)) {
			return true;
		}

		v1s = v1e;
		v1e = v1e->GetNext();
	}

	return false;
}

boolean Math::cross_other(CVertex* v2s, CVertex* v2e, CShape* shs, CShape* she) {
	CShape* nowS;
	CVertex* v1s;
	CVertex* v1e;

	if (she== NULL)
	{
		return false;
	}

	while (shs != she) {
		v1s = shs->GetVertexhead();
		v1e = v1s->GetNext();
		while (v1e != NULL) {

			if (cross_judge(v1s, v1e, v2s, v2e)) {
				return true;
			}

			v1s = v1e;
			v1e = v1e->GetNext();
		}

		shs = shs->GetNext();
	}

	return false;
}*/




