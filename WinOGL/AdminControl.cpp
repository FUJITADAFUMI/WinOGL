#include "pch.h"
#include "AdminControl.h"

CAdminControl::CAdminControl()
{
}

CAdminControl::~CAdminControl()
{
	FreeShape();
}



void CAdminControl::Draw()
{
	// TODO: ‚±‚±‚ÉŽÀ‘•ƒR[ƒh‚ð’Ç‰Á‚µ‚Ü‚·.
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);
	/*Begin‚ª‚È‚¢‚Æ‚Å‚«‚È‚¢*/
	glBegin(GL_POINTS);
	for (CShape* cs = shape_head; cs != NULL; cs = cs->GetNext()) {
		for (CVertex* cv = cs->GetVertexhead(); cv != NULL; cv = cv->GetNext()) {
			glVertex2f(cv->GetX(), cv->GetY());
		}
	}
	glEnd();


	for (CShape* cs = shape_head; cs != NULL; cs = cs->GetNext()) {
		glBegin(GL_LINE_STRIP);
		for (CVertex* cv = cs->GetVertexhead(); cv != NULL; cv = cv->GetNext()) {
			glVertex2f(cv->GetX(), cv->GetY());
		}
		glEnd();
	}
	
	/*glBegin(GL_LINE_LOOP);

	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);*/
}

void CAdminControl::FreeShape()
{
	CShape* temp = NULL;
	CShape* cs = shape_head;
	while (shape_head != NULL)
	{
		temp = shape_head->GetNext();
		delete shape_head;
		shape_head = temp;
	}
}
void CAdminControl::AppendShape()
{
	CShape* New_Shape = new CShape;

	if (shape_head == NULL)
	{
		shape_head = New_Shape;
	}
	else
	{
		CShape* cs = shape_head;
		while (cs->GetNext() != NULL)
		{
			cs = cs->GetNext();
		}
		cs->SetNext(New_Shape);
	}
}

void CAdminControl::Append_vertex(float x, float y) {
	shape_head->AppendVertex(x,y);
}

