#include "pch.h"
#include "CShape.h"

CShape::CShape()
{

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
	}
	else
	{
		CVertex* vp = vertex_head;
		while (vp->GetNext() != NULL)
		{
			vp = vp->GetNext();
		}
		vp->SetNext(New_Vertex);
	}
}
