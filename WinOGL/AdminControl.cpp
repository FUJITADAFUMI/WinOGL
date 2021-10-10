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
	// TODO: ここに実装コードを追加します.
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);
	/*Beginがないとできない*/
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

void CAdminControl::CreateShape(float x, float y) {
	AppendShape();
	shape_head->AppendVertex(x, y);

	if (CS.GetVertexhead() != NULL)
	{
		CVertex* pre_vp = NULL;
		for (CVertex* vp = CS.GetVertexhead(); vp != NULL; vp = vp->GetNext())
		{
			CVertex* del = vp;
			int xp = vp->GetX();
			int yp = vp->GetY();
			float dis = sqrt(pow(xp - x, 2) + pow(yp - y, 2));
			if (dis <= 10.0)
			{
				AppendShape();
				shape_head->AppendVertex(xp, yp);
			}
			pre_vp = vp;
		}
	}
}

