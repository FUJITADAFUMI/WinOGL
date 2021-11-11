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
	// AxisFlagがtrueのとき座標軸を描画する
	if (AxisFlag) {
		DrawAxis();
	}
	if (VertexFlag) {
		VertexChoice(useX(), useY());
	}
	else if (SurfaceFlag) {
		SurfaceChoice(useX(), useY());
	}
	else if (EdgeFlag) {
		EdgeChoice(useX(), useY());
	}
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
//基本機能
void CAdminControl::CreateShape(float x, float y) {
	CVertex nowv;
	nowv.SetXY(x, y);
	if (VertexFlag==false && SurfaceFlag == false&& EdgeFlag == false) {
		if (shape_head != NULL)
		{
			CShape* cv = shape_final;
			if (cv->Count() < 3)
			{
				//交差判定
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
				CVertex* vp = shape_final->GetVertexhead();
				float xp = vp->GetX();
				float yp = vp->GetY();
				float dis = sqrt(pow(xp - x, 2) + pow(yp - y, 2));
				if (cv->cross(&nowv) || cv->cross_other(&nowv, shape_head)) {

				}
				else
				{

					if (dis <= 0.1 && !cv->cross_last(&nowv))
					{
						if (cv->inout_zu_judge(shape_head, shape_final) == false) {
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
}
//座標軸
void CAdminControl::SetAxisFlag()
{
	if (AxisFlag == true) {
		AxisFlag = false;
	}
	else {
		AxisFlag = true;
	}
}

bool CAdminControl::GetAxisFlag()
{
	return AxisFlag;
}
//点選択
void CAdminControl::SetVertexFlag()
{
	if (shape_head==NULL || SurfaceFlag == true || EdgeFlag == true) {
		VertexFlag = false;
	}
	else if (VertexFlag == false&& shape_final->GetVertexhead()==NULL) {
		VertexFlag = true;
	}
	else {
		VertexFlag = false;
	}
}

bool CAdminControl::GetVertexFlag()
{
	return VertexFlag;
}
//面選択
void CAdminControl::SetSurfaceFlag()
{
	if (shape_head == NULL|| VertexFlag == true||EdgeFlag==true) {
		SurfaceFlag = false;
	}
	else if (SurfaceFlag == false && shape_final->GetVertexhead() == NULL) {
		SurfaceFlag = true;
	}
	else {
		SurfaceFlag = false;
	}
}
bool CAdminControl::GetSurfaceFlag()
{
	return SurfaceFlag;
}
//現在点
void CAdminControl::SelX(float x)
{
	X = x;
}

void CAdminControl::SelY(float y)
{
	Y = y;
}

float CAdminControl::useX()
{
	return X;
}

float CAdminControl::useY()
{
	return Y;
}
//辺選択
void CAdminControl::SetEdgeFlag()
{
	if (shape_head == NULL || SurfaceFlag == true|| VertexFlag == true) {
		EdgeFlag = false;
	}
	else if (EdgeFlag == false && shape_final->GetVertexhead() == NULL) {
		EdgeFlag = true;
	}
	else {
		EdgeFlag = false;
	}
}
bool CAdminControl::GetEdgeFlag()
{
	return EdgeFlag;
}
//座標軸描画
void CAdminControl::DrawAxis()
{
	// TODO: ここに実装コードを追加します.
	glBegin(GL_LINES);
	// x軸
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	// y軸
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	// z軸
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
}
//点選択描画
void CAdminControl::VertexChoice(float x, float y)
{
	CVertex nowv;
	nowv.SetXY(x, y);
	CShape *nowS = shape_head;
	CVertex* nowV; 
	float xp;
	float yp;
	float dis;
	while (nowS->GetNext()!= NULL) {
		nowV=nowS->GetVertexhead();
		while (nowV!=NULL) {
			xp = nowV->GetX();
			yp = nowV->GetY();
			dis = sqrt(pow(xp - x, 2) + pow(yp - y, 2));
			if (dis <= 0.01) {
				glColor3f(255, 0, 0);
				glPointSize(10);
				glBegin(GL_POINTS);
				glVertex2f(xp,yp);
				glEnd();
			}
			nowV = nowV->GetNext();
		}
		nowS = nowS->GetNext();
	}
}
//面選択描画
void CAdminControl::SurfaceChoice(float x, float y)
{
	float all = 0;
	CVertex nowv;
	nowv.SetXY(x, y);
	CShape* nowS = shape_head;
	CVertex* As;
	CVertex* Ae;
	CVertex* usev;
	
	while (nowS->GetNext() != NULL) {
		As = nowS->GetVertexhead();
		Ae = As->GetNext();
		while (Ae != NULL) {
			all = all + math.substend_angle(As, Ae, &nowv);
			As = Ae;
			Ae = Ae->GetNext();
		}
		all = all + math.substend_angle(nowS->Getvertexfinal(), nowS->GetVertexhead(), &nowv);
		if (all < 0) {
			all = all * -1;
		}
		if (2 * M_PI - all < 0.1 && 2 * M_PI - all >-0.1) {
			glColor3f(255, 0, 0);
			glPointSize(10);
			glBegin(GL_POINTS);
			As = nowS->GetVertexhead();
			while (As!=NULL) {
				glVertex2f(As->GetX(), As->GetY());
				As = As->GetNext();
			}
			glEnd();
			glBegin(GL_LINE_STRIP);
			As = nowS->GetVertexhead();
			while (As != NULL) {
				glVertex2f(As->GetX(), As->GetY());
				As = As->GetNext();
			}
			As = nowS->GetVertexhead();
			glVertex2f(As->GetX(), As->GetY());
			glEnd();
		}
		nowS = nowS->GetNext();
		all = 0;
	}
}
//辺選択描画
void CAdminControl::EdgeChoice(float x, float y)
{
	// TODO: ここに実装コードを追加します.
	CVertex nowv;
	nowv.SetXY(x, y);
	CShape* nowS = shape_head;
	CVertex* As;
	CVertex* Ae;
	CVertex* usev;
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

	while (nowS->GetNext() != NULL) {
		As = nowS->GetVertexhead();
		Ae = As->GetNext();
		while (Ae != NULL) {
			if (math.edgechoicejud(*As, *Ae, nowv)) {
				glColor3f(255, 0, 0);
				glPointSize(10);
				glBegin(GL_LINE_STRIP);
				glVertex2f(As->GetX(), As->GetY());
				glVertex2f(Ae->GetX(), Ae->GetY());
				glEnd();
			}
			As = Ae;
			Ae = Ae->GetNext();
		}
		As = nowS->Getvertexfinal();
		Ae = nowS->GetVertexhead();
		if (math.edgechoicejud(*As, *Ae, nowv)) {
			glColor3f(255, 0, 0);
			glPointSize(10);
			glBegin(GL_LINE_STRIP);
			glVertex2f(As->GetX(), As->GetY());
			glVertex2f(Ae->GetX(), Ae->GetY());
			glEnd();
		}
		nowS = nowS->GetNext();
	}
}
