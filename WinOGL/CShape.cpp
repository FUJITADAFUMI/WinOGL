#include "pch.h"
#include "CShape.h"
#define _USE_MATH_DEFINES
#include <math.h>

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
boolean CShape::cross_judge(CVertex* v1s, CVertex* v1e, CVertex* v2s, CVertex* v2e/*float new_x, float new_y*/)
{
	CVertex a, b, a1, b1, a2, b2;
	float ca1, ca2, cb1, cb2;
	
	//a
	a=math.calc_vertex(v1e, v1s);
	//b
	b = math.calc_vertex(v2e, v2s);
	//a1
	a1 = math.calc_vertex(v2s, v1s);
	//b1
	b1 = math.calc_vertex(v1s, v2s);
	//a2
	a2 = math.calc_vertex(v2e, v1s);
	//b2
	b2 = math.calc_vertex(v1e, v2s);

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

//自己交差
boolean CShape::cross(CVertex* Be) {
	CVertex* As = vertex_head;
	CVertex* Ae = As->GetNext();
	CVertex* Bs = vertex_final;

	while (Ae != Bs) {

		if (cross_judge(As, Ae, Bs, Be)) {
			return true;
		}
		As = Ae;
		Ae = Ae->GetNext();
	}
	


	return false;
}

boolean CShape::cross_last(CVertex* Be) {
	CVertex* As = vertex_head->GetNext();
	CVertex* Ae = As->GetNext();
	CVertex* Bs = vertex_final;

	while (Ae != Bs) {

		if (cross_judge(As, Ae, Be, vertex_head)) {
			return true;
		}
		As = Ae;
		Ae = Ae->GetNext();
	}



	return false;
}

//点が内部にあるか
boolean CShape::inout_judge(CVertex* Be, CShape* shape_head)
{
	float all=0;
	CShape* nowS = shape_head;
	CVertex* As;
	CVertex* Ae;
	while (nowS->GetNext() != NULL) {
		As = nowS->GetVertexhead();
		Ae = As->GetNext();
		while (Ae != NULL) {
			all=all+ math.substend_angle(As,Ae,Be);
			As = Ae;
			Ae = Ae->GetNext();
		}
		all = all + math.substend_angle(nowS->Getvertexfinal(),nowS->GetVertexhead(), Be);
		if (all<0) {
			all = all * -1;
		}

		if (2 * M_PI - all < 0.1 && 2 * M_PI - all >-0.1) {
			return true;
		}
		nowS = nowS->GetNext();
		all = 0;
	}
	
	return false;

}

//図形が内部にあるか
boolean CShape::inout_zu_judge(CShape* shape_head, CShape* shape_final)
{
	float all = 0;
	CShape* nowS = shape_head;
	CShape* nowE = shape_final;
	//始点
	CVertex* As;
	//Shape最後の点
	CVertex* Bs;
	CVertex* Be;
	/*if(nowE== NULL) {
		return false;
	}*/
	while (nowS->GetNext() != NULL) {
		As = nowS->GetVertexhead();	
		while (As != NULL) {
			Bs = nowE->GetVertexhead();
			Be = Bs->GetNext();
			while (Be!=NULL) {
				all = all + math.substend_angle(Bs, Be, As);
				Bs = Be;
				Be = Be->GetNext();
			}
			all = all + math.substend_angle(nowE->Getvertexfinal(), nowE->GetVertexhead(), As);
			if (all < 0) {
				all = all * -1;
			}

			if (2 * M_PI - all < 0.1&& 2 * M_PI - all >- 0.1) {
				return true;
			}
			else {
				all = 0;
			}

			As = As->GetNext();
		}
		nowS = nowS->GetNext();
	}
	return false;
}

//他交差
boolean CShape::cross_other(CVertex* Be, CShape* shape_head) {
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

			if (cross_judge(As, Ae, Bs, Be)) {
				return true;
			}

			As = Ae;
			Ae = Ae->GetNext();
		}
		if (cross_judge(nowS->GetVertexhead(), nowS->Getvertexfinal(), Bs, Be)) {
			return true;
		}


		nowS = nowS->GetNext();
	}

	return false;
}

