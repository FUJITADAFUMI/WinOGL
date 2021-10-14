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
