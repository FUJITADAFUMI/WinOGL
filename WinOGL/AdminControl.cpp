#include "pch.h"
#include "AdminControl.h"
#include <math.h>

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


	if (shape_final != NULL) {
		glBegin(GL_LINE_STRIP);
		for (CVertex* cv = shape_final->GetVertexhead(); cv != NULL; cv = cv->GetNext()) {
			glVertex2f(cv->GetX(), cv->GetY());
		}
		glEnd();
	}

	if (shape_head != NULL) {
		for (CShape* cs = shape_head; cs->GetNext() != NULL; cs = cs->GetNext()) {
			glBegin(GL_LINE_LOOP);
			for (CVertex* cv = cs->GetVertexhead(); cv != NULL; cv = cv->GetNext()) {
				glVertex2f(cv->GetX(), cv->GetY());
			}
			glEnd();
		}
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
		shape_final = New_Shape;
	}
	else
	{
		New_Shape->Setpreshape(shape_final);
		shape_final->SetNext(New_Shape);
		shape_final = New_Shape;
		/*CShape* cs = shape_head;
		while (cs->GetNext() != NULL)
		{
			cs = cs->GetNext();
		}
		cs->SetNext(New_Shape);*/
	}
}

void CAdminControl::CreateShape(float x, float y) {
	CVertex nowv;
	nowv.SetXY(x, y);
	if (shape_head != NULL)
	{
		CShape* cv = shape_final;
		if (cv->Count()<3)
		{	
			//Œð·”»’è
			if (cv->Count() >= 1 && cv->cross_other(&nowv, shape_head)) {
				
			}
			else
			{
				
				if (cv->inout_judge(&nowv, shape_head) == false) {
					shape_final->AppendVertex(x, y);
				}
			}
			//AppendShape();
		}

		else
		{
			CVertex* vp= shape_final->GetVertexhead();
			float xp = vp->GetX();
			float yp = vp->GetY();
			float dis = sqrt(pow(xp - x, 2) + pow(yp - y, 2));
			if (cv->cross(&nowv) || cv->cross_other(&nowv, shape_head)) {
			
			}
			else
			{

				if (dis <= 0.1&& !cv->cross_last(&nowv))
				{
					if (cv->inout_zu_judge(shape_head, shape_final)==false) {
						AppendShape();
					}
					
				}
				else
				{
					shape_final->AppendVertex(x, y);
				}
			}
		}
	}
	else
	{
		
			AppendShape();
			shape_head->AppendVertex(x, y);
		
	}
}

