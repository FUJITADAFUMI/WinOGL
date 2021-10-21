#include "pch.h"
#include "CShape.h"

CShape::CShape()
{

}

CShape::CShape(CVertex* new_vertexhead)
{
	vertex_head = new_vertexhead;
}


CShape::~CShape()
{
	FreeVertex();
}

void CShape::SetVertexhead(CVertex*new_vertexhead)
{
	vertex_head = new_vertexhead;
}

CVertex* CShape::GetVertexhead()
{
	return vertex_head;
}

CShape* CShape::Getpreshape()
{
	return pre_shape;
}

void CShape::Setpreshape(CShape* new_pre)
{
	pre_shape = new_pre;
}

CVertex* CShape::Getvertexfinal()
{
	return vertex_final;
}

void CShape::SetNext(CShape* new_next)
{
	next_shape = new_next;
}

CShape* CShape::GetNext()
{
	return next_shape;
}

void CShape::FreeVertex()
{
	CVertex* temp = NULL;
	CVertex* vp = vertex_head;
	while (vertex_head != NULL)
	{
		temp = vertex_head->GetNext();
		delete vertex_head;
		vertex_head = temp;
	}
}
void CShape::AppendVertex(float new_x, float new_y)
{
	CVertex* New_Vertex = new CVertex;
	New_Vertex->SetXY(new_x, new_y);

	if (vertex_head == NULL)
	{
		vertex_head = New_Vertex;
		vertex_final= New_Vertex;
	}
	else
	{
		New_Vertex->Setpre(vertex_final);
		vertex_final->SetNext(New_Vertex);
		vertex_final = New_Vertex;
	}
}

int CShape::Count()
{
	int count=0;
	for (CVertex* vp = vertex_head; vp != NULL;vp=vp->GetNext()) 
	{
		count++;
	}
	return count;
}

//交差判定
boolean CShape::cross_judge(CVertex* v1s, CVertex* v1e, CVertex* v2s,float new_x, float new_y)
{
	CVertex a, b, a1, b1, a2, b2;
	float ca1, ca2, cb1, cb2;
	
	//a
	a.SetX(v1e->GetX() - v1s->GetX());
	a.SetY(v1e->GetY() - v1s->GetY());
	//b
	b.SetX(new_x - v2s->GetX());
	b.SetY(new_y - v2s->GetY());
	//a1
	a1.SetX(v2s->GetX() - v1s->GetX());
	a1.SetY(v2s->GetY() - v1s->GetY());
	//b1
	b1.SetX(v1s->GetX() - v2s->GetX());
	b1.SetY(v1s->GetY() - v2s->GetY());
	//a2
	a2.SetX(new_x - v1s->GetX());
	a2.SetY(new_y - v1s->GetY());
	//b2
	b2.SetX(v1e->GetX() - v2s->GetX());
	b2.SetY(v1e->GetY() - v2s->GetY());

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


boolean CShape::cross(/*CVertex* */float new_x, float new_y) {
	CVertex* As = vertex_head;
	CVertex* Ae = As->GetNext();
	CVertex* Bs = Ae->GetNext();

	while (Bs->GetNext() != NULL)
	{
		Bs = Bs->GetNext();
	}

	/*if (As->GetX() == new_x && As->GetY() == new_y)  //始点と終点が同じ場合
	{
		As = Ae;
		Ae = Ae->GetNext();
	}*/

	while (Ae != Bs) {

		if (cross_judge(As, Ae, Bs, new_x, new_y)) {
			return true;
		}

		As = Ae;
		Ae = Ae->GetNext();
	}

	return false;
}

/*(CVertex* v1s, CVertex* v1e, CVertex* v2s, CVertex* v2e)
{
	if (v1s->GetX() == v2e->GetX() && v1s->GetY() == v2e->GetY())  //始点と終点が同じ場合
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
}*/

boolean CShape::cross_other(float new_x, float new_y, CShape* shape_head) {
	CShape* nowS= shape_head;
	CVertex* As;
	CVertex* Ae;
	CVertex* Bs = vertex_head;

	while (Bs->GetNext() != NULL) {
		Bs = Bs->GetNext();
	}
	while (nowS->GetNext() != NULL) {
		As = nowS->GetVertexhead();
		Ae = As->GetNext();
		while (Ae != NULL) {

			if (cross_judge(As, Ae, Bs, new_x, new_y)) {
				return true;
			}

			As = Ae;
			Ae = Ae->GetNext();
		}

		nowS = nowS->GetNext();
	}

	return false;
}
/*
(CVertex* v2s, CVertex* v2e, CShape* shs, CShape* she)
{
	CShape* nowS;
	CVertex* v1s;
	CVertex* v1e;

	if (she == NULL)
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
}
*/
