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
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);
	/*Begin���Ȃ��Ƃł��Ȃ�*/
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
	// AxisFlag��true�̂Ƃ����W����`�悷��
	if (AxisFlag) {
		DrawAxis();
	}
	if (VertexFlag) {
		if (VtMoveFlag) {
			VertexMove(mvX(), mvY());
			//VertexChoice(VtMove->GetX(), VtMove->GetY());
		}
		else {
			VertexChoice(useX(), useY());
		}
		
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
//��{�@�\
void CAdminControl::CreateShape(float x, float y) {
	CVertex nowv;
	nowv.SetXY(x, y);
	if (VertexFlag==false && SurfaceFlag == false&& EdgeFlag == false) {
		if (shape_head != NULL)
		{
			CShape* cv = shape_final;
			if (cv->Count() < 3)
			{
				//��������
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
//���W��
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
//�_�I��
void CAdminControl::SetVertexFlag()
{
	if (shape_head==NULL) {
		VertexFlag = false;
	}
	else if (VertexFlag == false&& shape_final->GetVertexhead()==NULL) {
		if (SurfaceFlag == true || EdgeFlag == true) {
			SurfaceFlag = false;
			EdgeFlag = false;
		}
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
//�ʑI��
void CAdminControl::SetSurfaceFlag()
{
	if (shape_head == NULL) {
		SurfaceFlag = false;
	}
	else if (SurfaceFlag == false && shape_final->GetVertexhead() == NULL) {
		if (VertexFlag == true || EdgeFlag == true) {
			VertexFlag = false;
			EdgeFlag = false;
		}
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
//���ݓ_
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
//�ړ��_
void CAdminControl::MvX(float x)
{
	X = x;
}
void CAdminControl::MvY(float y)
{
	Y = y;
}
float CAdminControl::mvX()
{
	return X;
}
float CAdminControl::mvY()
{
	return Y;
}
//�ӑI��
void CAdminControl::SetEdgeFlag()
{
	if (shape_head == NULL ) {
		EdgeFlag = false;
	}
	else if (EdgeFlag == false && shape_final->GetVertexhead() == NULL) {
		if (SurfaceFlag == true || VertexFlag == true) {
			VertexFlag = false;
			SurfaceFlag = false;
		}
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
//���_�ړ�
void CAdminControl::SetVtMoveFlag()
{
	if (VertexFlag && VtMove!=NULL&& VtMoveFlag == false) {
		VtMoveFlag = true;
	}
	else {
		VtMoveFlag = false;
	}
}
bool CAdminControl::GetVtMoveFlag()
{
	return VtMoveFlag;
}
//�}�E�X���������ǂ���
void CAdminControl::SetVtmouseflag()
{
	if (mouseflag) {
		mouseflag = false;
	}
	else {
		mouseflag = true;
	}
}
bool CAdminControl::GetVtmouseflag()
{
	return mouseflag;
}
void CAdminControl::MoveIn(float x, float y)
{
	CVertex nowv;
	nowv.SetXY(x, y);
	CShape* nowS = shape_head;
	CVertex* nowV;
	CVertex* moveV = VtMove;
	CVertex* premoveV = VtpreMove;
	CVertex* nextmoveV = VtnextMove;
	if (VtMoveFlag==true) {
			while (nowS->GetNext() != NULL) {
				nowV = nowS->GetVertexhead();
				while (nowV != NULL) {
					if (nowV == moveV) {
						if (nowS->mvcross(premoveV, moveV, &nowv) == false  && nowS->mvcross(nextmoveV, moveV, &nowv) == false) {
							if (nowS->mvcross_other(premoveV, shape_head, nowS, &nowv) == false && nowS->mvcross_other(nextmoveV, shape_head, nowS, &nowv) == false) {
								if (nowS->mvinout_zu_judge(shape_head, nowS, shape_final, moveV, &nowv)==false) {
									nowV->SetXY(x, y);
									VtMoveFlag = false;
								}
							}							
						}
					}
					nowV = nowV->GetNext();
				}
				nowS = nowS->GetNext();
			}
	}
}

//�E�N���b�N������
void CAdminControl::SetRmouseflag()
{
	if (Rmouseflag == false) {
		Rmouseflag = true;
	}
	else {
		Rmouseflag = false;
	}
}
bool CAdminControl::GetRmouseflag()
{
	return Rmouseflag;
}
//�E�N���b�N�_
void CAdminControl::RSelX(float x)
{
	RX = x;
}
void CAdminControl::RSelY(float y)
{
	RY = y;
}
float CAdminControl::RuseX()
{
	return RX;
}
float CAdminControl::RuseY()
{
	return RY;
}
//�}�`�ړ��������ǂ���
void CAdminControl::SetShapeMoovflag()
{
	if (ShapeMoovflag) {
		ShapeMoovflag = false;
	}
	else {
		ShapeMoovflag = true;
	}
}
bool CAdminControl::GetShapeMoovflag()
{
	return ShapeMoovflag;
}
//���W���`��
void CAdminControl::DrawAxis()
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	glBegin(GL_LINES);
	// x��
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	// y��
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	// z��
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
}
//�_�I��`��
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
				VtMove = nowV;
				RtShape = nowS;
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
	if (GetRmouseflag()) {
		VertexDel(RuseX(), RuseY());
	}
}
//�ʑI��`��
void CAdminControl::SurfaceChoice(float x, float y)
{
	float all = 0;
	CVertex nowv;
	nowv.SetXY(x, y);
	CShape* nowS = shape_head;
	CVertex* As;
	CVertex* Ae;
	CVertex* usev;
	
	if (!GetRmouseflag()) {
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
				SelectSf = nowS;
				glColor3f(255, 0, 0);
				glPointSize(10);
				glBegin(GL_POINTS);
				As = nowS->GetVertexhead();
				while (As != NULL) {
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
	if (GetRmouseflag()&& SelectSf!=NULL) {
		ShapeMoov(RuseX(), RuseY(), mvX(), mvY());
	}

}
//�ӑI��`��
void CAdminControl::EdgeChoice(float x, float y)
{
	// TODO: �����Ɏ����R�[�h��ǉ����܂�.
	CVertex nowv;
	nowv.SetXY(x, y);
	CVertex savev;
	CShape* nowS = shape_head;
	CVertex* As;
	CVertex* Ae;
	CVertex* usev;
	float min1 = 2;
	//�I�����ꂽ���W
	CVertex chs;
	CVertex che;

	while (nowS->GetNext() != NULL) {
		As = nowS->GetVertexhead();
		Ae = As->GetNext();
		while (Ae != NULL) {
			if (min1 > math.edgechoicejud(*As, *Ae, nowv)) {
				min1 = math.edgechoicejud(*As, *Ae, nowv);
				chs = *As;
				che = *Ae;
			}
			As = Ae;
			Ae = Ae->GetNext();
		}
		As = nowS->Getvertexfinal();
		Ae = nowS->GetVertexhead();
		if (min1 > math.edgechoicejud(*As, *Ae, nowv)) {
			min1 = math.edgechoicejud(*As, *Ae, nowv);
			chs = *As;
			che = *Ae;
		}
		nowS = nowS->GetNext();
	}
	if (GetRmouseflag()) {
		VertexInsert(RuseX(), RuseY());
		EdgeFlag = false;
	}
	else {
		Vta = chs;
		Vtb = che;
		glColor3f(255, 0, 0);
		glPointSize(10);
		glBegin(GL_LINE_STRIP);
		glVertex2f(chs.GetX(), chs.GetY());
		glVertex2f(che.GetX(), che.GetY());
		glEnd();
	}
	
}
//���_�ړ�
void CAdminControl::VertexMove(float x, float y)
{
	CVertex nowv;
	nowv.SetXY(x, y);
	CShape* nowS = shape_head;
	CVertex* nowV;
	CVertex* moveV = VtMove;
	float xp;
	float yp;

	float ax;
	float ay;

	float nx;
	float ny;

	float dis;
	while (nowS->GetNext() != NULL) {
		nowV = nowS->GetVertexhead();
		while (nowV != NULL) {
			xp = nowV->GetX();
			yp = nowV->GetY();
				if (moveV->GetX() == xp && moveV->GetY() == yp) {
					if (nowS->GetVertexhead() == moveV) {
						ax = nowS->Getvertexfinal()->GetX();
						ay = nowS->Getvertexfinal()->GetY();
						
						VtpreMove = nowS->Getvertexfinal();
					}
					else {
						ax = nowV->Getpre()->GetX();
						ay = nowV->Getpre()->GetY();
						
						VtpreMove = nowV->Getpre();
					}
					if (nowS->Getvertexfinal() == moveV) {
						nx = nowS->GetVertexhead()->GetX();
						ny = nowS->GetVertexhead()->GetY();
						
						VtnextMove = nowS->GetVertexhead();
					}
					else {
						nx = nowV->GetNext()->GetX();
						ny = nowV->GetNext()->GetY();
						
						VtnextMove = nowV->GetNext();
					}
					glColor3f(0, 255, 0);
					glPointSize(10);
					glBegin(GL_POINTS);
					glVertex2f(x, y);
					glEnd();
					glColor3f(0, 255, 0);
					glPointSize(10);
					glBegin(GL_LINE_STRIP);
					glVertex2f(x, y);
					glVertex2f(nx, ny);
					glVertex2f(x, y);
					glVertex2f(ax, ay);
					glEnd();
			}
			nowV = nowV->GetNext();
		}
		nowS = nowS->GetNext();
	}
	
}

//���_�}��
void CAdminControl::VertexInsert(float x, float y)
{
	CVertex nowv;
	nowv.SetXY(x, y);
	CVertex savev;
	CVertex* newV = new CVertex();
	CShape* nowS = shape_head;
	CVertex* As;
	CVertex* Ae;
	CVertex* usev=NULL;
	float min1 = 2;
	//�I�����ꂽ���W
	CVertex chs;
	CVertex che;
	//s+t=1
	float s;
	float t;

	float newx;
	float newy;

	while (nowS->GetNext() != NULL) {
		As = nowS->GetVertexhead();
		Ae = As->GetNext();
		while (Ae != NULL) {
			if (min1 > math.edgechoicejud(*As, *Ae, nowv)) {
				min1 = math.edgechoicejud(*As, *Ae, nowv);
				chs = *As;
				che = *Ae;
			}
			As = Ae;
			Ae = Ae->GetNext();
		}
		As = nowS->Getvertexfinal();
		Ae = nowS->GetVertexhead();
		if (min1 > math.edgechoicejud(*As, *Ae, nowv)) {
			min1 = math.edgechoicejud(*As, *Ae, nowv);
			chs = *As;
			che = *Ae;
		}
		nowS = nowS->GetNext();
	}
	if (Vta.GetX()==chs.GetX()&& Vta.GetY() == chs.GetY()&& Vtb.GetX() == che.GetX()&& Vtb.GetY() == che.GetY()) {
		s=math.Gets();
		t=math.Gett();
		newx = (s * Vta.GetX()) + (t * Vtb.GetX());
		newy = (s * Vta.GetY()) + (t * Vtb.GetY());
		Insert(x, y);
		/*newV->SetXY(newx, newy);
		newV->Setpre(&chs);
		newV->SetNext(&che);*/

		//return true;
	}
	//return false;
}

void CAdminControl::Insert(float x, float y)
{
	CVertex* nowv= new CVertex();
	nowv->SetXY(x, y);
	CShape* nowS = shape_head;
	CVertex* nowV;
	CVertex* moveV = VtMove;
	CVertex* premoveV = VtpreMove;
	CVertex* nextmoveV = VtnextMove;
		while (nowS->GetNext() != NULL) {
			nowV = nowS->GetVertexhead();
			while (nowV != NULL) {
				
				if (nowV->GetX()==Vta.GetX()&& nowV->GetY() == Vta.GetY()) {
					//a->nowv->b
					if (nowV->GetNext()!=NULL) {
						nowv->Setpre(nowV);
						nowv->SetNext(nowV->GetNext());
						nowV->SetNext(nowv);
						nowv->GetNext()->Setpre(nowv);
					}
					//a->nowv
					else {
						nowv->Setpre(nowV);
						nowV->SetNext(nowv);
						nowS->Setvertexfinal(nowv);
					}
					
				}
				nowV = nowV->GetNext();
			}
			nowS = nowS->GetNext();
		}
}
//���_�폜
void CAdminControl::VertexDel(float x, float y)
{
	CVertex nowv;
	nowv.SetXY(x, y);
	CShape* nowS = shape_head;
	CVertex* nowV;
	float xp;
	float yp;
	float dis;
	int count;
	CVertex* del = VtMove;
	while (nowS->GetNext() != NULL) {
		nowV = nowS->GetVertexhead();
		count = nowS->Count();
		while (nowV != NULL) {
			xp = nowV->GetX();
			yp = nowV->GetY();
			dis = sqrt(pow(xp - x, 2) + pow(yp - y, 2));
			if (dis <= 0.01) {
				if (del==nowV) {
					if (count > 3) {
						if (nowS->GetVertexhead() == nowV) {
								if (Del(nowS) == false) {
									nowV->GetNext()->Setpre(NULL);
									nowS->SetVertexhead(nowV->GetNext());
									delete nowV;
									VertexFlag = false;
									break;
								}
								else {
									break;
								}

							}
							else if (nowS->Getvertexfinal() == nowV) {
								if (Del(nowS) == false) {
									nowV->Getpre()->SetNext(NULL);
									nowS->Setvertexfinal(nowV->Getpre());
									delete nowV;
									VertexFlag = false;
									break;
								}
								else {
									break;
								}
							}
							else {
							if (Del(nowS) == false) {
								nowV->Getpre()->SetNext(del->GetNext());
								nowV->GetNext()->Setpre(del->Getpre());
								delete nowV;
								VertexFlag = false;
								break;
							}
							else {
								break;
							}
						}
						

					}
				}
			}
			nowV = nowV->GetNext();
		}
		nowS = nowS->GetNext();
	}
}

bool CAdminControl::Del(CShape* delS)
{
	//�Ȃ��p���v
	float all = 0;
	//���݂Ă�shape
	CShape* nowS = shape_head;
	CVertex* nowV=NULL;
	//�����_
	CVertex* del = VtMove;
	//�����_�̑O��
	CVertex* delp = NULL;
	CVertex* deln = NULL;
	if (delS->GetVertexhead()==del) {
		deln = del->GetNext();
		delp = delS->Getvertexfinal();
	}
	else if (delS->Getvertexfinal() == del) {
		deln =  delS->GetVertexhead();
		delp = del->Getpre();
	}
	else {
		deln = del->GetNext();
		delp = del->Getpre();
	}
	while (nowS != NULL) {
		nowV = nowS->GetVertexhead();
		while (nowV != NULL) {
			if (nowV != del&& nowV != delp&& nowV != deln) {
				all = all + math.substend_angle(deln, delp, nowV);
				all = all + math.substend_angle(delp, del, nowV);
				all = all + math.substend_angle(del, deln, nowV);
				if (all < 0) {
					all = all * -1;
				}

				if (2 * M_PI - all < 0.1 && 2 * M_PI - all >-0.1) {
					return true;
				}
			}

			nowV = nowV->GetNext();
			all = 0;
		}
		nowS = nowS->GetNext();
	}
	return false;
}
//�}�`�ړ�
void CAdminControl::ShapeMoov(float x, float y, float mx, float my)
{
	CVertex nowv;
	nowv.SetXY(x, y);
	CVertex nowmv;
	nowmv.SetXY(mx, my);
	//2�_�Ԃ̋���
	float wdisx = mx-x;
	float wdisy = my-y;
	CShape* movS = SelectSf;
	CVertex* movV = movS->GetVertexhead();
	CVertex* As;
	CVertex* Ae;

		glColor3f(0, 255, 0);
		glPointSize(10);
		glBegin(GL_POINTS);
		As = movS->GetVertexhead();
		while (As != NULL) {
			glVertex2f(As->GetX() + wdisx, As->GetY() + wdisy);
			As = As->GetNext();
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		As = movS->GetVertexhead();
		while (As != NULL) {
			glVertex2f(As->GetX() + wdisx, As->GetY() + wdisy);
			As = As->GetNext();
		}
		As = movS->GetVertexhead();
		glVertex2f(As->GetX() + wdisx, As->GetY() + wdisy);
		glEnd();

		diffvt.SetXY(wdisx, wdisy);
		ShapeMoovflag=true;
}

//���������}�`�̓_���}�`�̒��ɂ���
bool CAdminControl::Inoutshape(CShape* selsp)
{
	float all = 0;
	CShape* movS = selsp;
	CVertex* movV;
	CVertex newmovV;
	CVertex* nowV;
	CVertex* nextV;
	CVertex diff = diffvt;

	CShape* nowS = shape_head;
	while (nowS->GetNext() != NULL) {
		if (nowS != movS) {
			movV = movS->GetVertexhead();
			while (movV != NULL) {
				nowV = nowS->GetVertexhead();
				nextV = nowV->GetNext();
				while (nextV != NULL) {
					newmovV.SetXY(movV->GetX() + diff.GetX(), movV->GetY() + diff.GetY());
					all = all + math.substend_angle(nowV, nextV, &newmovV);
					nowV = nextV;
					nextV = nextV->GetNext();
				}
				all = all + math.substend_angle(nowS->Getvertexfinal(), nowS->GetVertexhead(), &newmovV);
				if (all < 0) {
					all = all * -1;
				}
				if (2 * M_PI - all < 0.1 && 2 * M_PI - all >-0.1) {
					return true;
				}	
				movV = movV->GetNext();
				all = 0;
			}
		}
		nowS = nowS->GetNext();
	}
	return false;
	
}
//�}�`�̓_�����������}�`�̒��ɂ���
bool CAdminControl::OtherInoutshape(CShape* selsp)
{
	float all = 0;
	CShape* movS = selsp;
	CVertex* movV;
	CVertex* nextmV;
	CVertex newmovV;
	CVertex newnextmV;
	CVertex* nowV;
	CVertex diff = diffvt;

	CShape* nowS = shape_head;
	while (nowS->GetNext() != NULL) {
		if (nowS != movS) {
			nowV = nowS->GetVertexhead();
			while (nowV!=NULL) {
				movV = movS->GetVertexhead();
				nextmV = movV->GetNext();
				while (nextmV!=NULL) {
					newmovV.SetXY(movV->GetX() + diff.GetX(), movV->GetY() + diff.GetY());
					newnextmV.SetXY(nextmV->GetX() + diff.GetX(), nextmV->GetY() + diff.GetY());
					all = all + math.substend_angle(&newmovV, &newnextmV, nowV);
					movV = nextmV;
					nextmV = nextmV->GetNext();
				}
				newmovV.SetXY(movS->GetVertexhead()->GetX()+ diff.GetX(), movS->GetVertexhead()->GetY() + diff.GetY());
				newnextmV.SetXY(movS->Getvertexfinal()->GetX() + diff.GetX(), movS->Getvertexfinal()->GetY() + diff.GetY());
				all = all + math.substend_angle(&newnextmV, &newmovV, nowV);
				if (all < 0) {
					all = all * -1;
				}
				if (2 * M_PI - all < 0.1 && 2 * M_PI - all >-0.1) {
					return true;
				}
				nowV = nowV->GetNext();
				all = 0;
			}

		}
		nowS = nowS->GetNext();
	}
	return false;
}
//��������
bool CAdminControl::Crossshape(CShape* selsp)
{
	CShape* movS = selsp;
	CVertex* movV;
	CVertex* nextmV;
	CVertex newmovV;
	CVertex newnextmV;
	CVertex* nowV;
	CVertex* nextV;
	CVertex diff = diffvt;
	CShape* nowS = shape_head;
	while (nowS->GetNext() != NULL) {
		if (nowS != movS) {
			movV = movS->GetVertexhead();
			nextmV=movV->GetNext();
			while (nextmV != NULL) {
				newmovV.SetXY(movV->GetX() + diff.GetX(), movV->GetY() + diff.GetY());
				newnextmV.SetXY(nextmV->GetX() + diff.GetX(), nextmV->GetY() + diff.GetY());
				nowV = nowS->GetVertexhead();
				nextV = nowV->GetNext();
				while (nextV != NULL) {	
					if (nowS->cross_judge(&newmovV,&newnextmV,nowV,nextV)) {
						return true;
					}
					nowV = nextV;
					nextV = nextV->GetNext();
				}
				
				movV = nextmV;
				nextmV = movV->GetNext();
			}
		}
		nowS = nowS->GetNext();
	}
	return false;
}

//�g��k���̂Ƃ��_���}�`�̒��ɂ���
bool CAdminControl::LRInoutshape(CShape* selsp, float a)
{
	float all = 0;
	CShape* movS = selsp;
	CVertex* movV;
	CVertex newmovV;
	CVertex* nowV;
	CVertex* nextV;

	CShape* nowS = shape_head;
	while (nowS->GetNext() != NULL) {
		if (nowS != movS) {
			movV = movS->GetVertexhead();
			while (movV != NULL) {
				nowV = nowS->GetVertexhead();
				nextV = nowV->GetNext();
				while (nextV != NULL) {
					//a*(mowV->GetX()-0)-0
					newmovV.SetXY(a * (movV->GetX() - 0) - 0, a * (movV->GetY() - 0) - 0);
					all = all + math.substend_angle(nowV, nextV, &newmovV);
					nowV = nextV;
					nextV = nextV->GetNext();
				}
				all = all + math.substend_angle(nowS->Getvertexfinal(), nowS->GetVertexhead(), &newmovV);
				if (all < 0) {
					all = all * -1;
				}
				if (2 * M_PI - all < 0.1 && 2 * M_PI - all >-0.1) {
					return true;
				}
				movV = movV->GetNext();
				all = 0;
			}
		}
		nowS = nowS->GetNext();
	}
	return false;
}
//�g��k���̂Ƃ��_�����������}�`�̒��ɂ���
bool CAdminControl::LROtherInoutsp(CShape* selsp, float a)
{
	float all = 0;
	CShape* movS = selsp;
	CVertex* movV;
	CVertex* nextmV;
	CVertex newmovV;
	CVertex newnextmV;
	CVertex* nowV;

	CShape* nowS = shape_head;
	while (nowS->GetNext() != NULL) {
		if (nowS != movS) {
			nowV = nowS->GetVertexhead();
			while (nowV != NULL) {
				movV = movS->GetVertexhead();
				nextmV = movV->GetNext();
				while (nextmV != NULL) {
					//a*(nextmV->GetX()-0)-0
					newmovV.SetXY(a * (movV->GetX() - 0) - 0, a * (movV->GetY() - 0) - 0);
					newnextmV.SetXY(a * (nextmV->GetX() - 0) - 0, a * (nextmV->GetY() - 0) - 0);
					all = all + math.substend_angle(&newmovV, &newnextmV, nowV);
					movV = nextmV;
					nextmV = nextmV->GetNext();
				}
				//a*(movS->GetVertexhead()->GetX()-0)-0
				//a*(movS->Getvertexfinal()->GetX()-0)-0
				newmovV.SetXY(a * (movS->GetVertexhead()->GetX() - 0) - 0, a * (movS->GetVertexhead()->GetY() - 0) - 0);
				newnextmV.SetXY(a * (movS->Getvertexfinal()->GetX() - 0) - 0, a * (movS->Getvertexfinal()->GetY() - 0) - 0);
				all = all + math.substend_angle(&newnextmV, &newmovV, nowV);
				if (all < 0) {
					all = all * -1;
				}
				if (2 * M_PI - all < 0.1 && 2 * M_PI - all >-0.1) {
					return true;
				}
				nowV = nowV->GetNext();
				all = 0;
			}

		}
		nowS = nowS->GetNext();
	}
	return false;
}
//��]�̂Ƃ��_���}�`�̒��ɂ���
bool CAdminControl::RTInoutshape(CShape* selsp, double tha)
{
	float all = 0;
	CVertex* rtV = VtMove;
	CShape* movS = RtShape;
	CVertex* movV;
	CVertex newmovV;
	CVertex* nowV;
	CVertex* nextV;
	float Rx;
	float Ry;
	
	CShape* nowS = shape_head;
	while (nowS->GetNext() != NULL) {
		if (nowS != movS) {
			movV = movS->GetVertexhead();
			while (movV != NULL) {
				nowV = nowS->GetVertexhead();
				nextV = nowV->GetNext();
				while (nextV != NULL) {
					Rx = (movV->GetX() - rtV->GetX()) * cos(tha) - (movV->GetY() - rtV->GetY()) * sin(tha) + rtV->GetX();
					Ry = (movV->GetX() - rtV->GetX()) * sin(tha) + (movV->GetY() - rtV->GetY()) * cos(tha) + rtV->GetY();
					newmovV.SetXY(Rx,Ry);
					all = all + math.substend_angle(nowV, nextV, &newmovV);
					nowV = nextV;
					nextV = nextV->GetNext();
				}
				all = all + math.substend_angle(nowS->Getvertexfinal(), nowS->GetVertexhead(), &newmovV);
				if (all < 0) {
					all = all * -1;
				}
				if (2 * M_PI - all < 0.1 && 2 * M_PI - all >-0.1) {
					return true;
				}
				movV = movV->GetNext();
				all = 0;
			}
		}
		nowS = nowS->GetNext();
	}
	return false;
}
//��]�̂Ƃ��_�����������}�`�̒��ɂ���
bool CAdminControl::RTOtherInoutsp(CShape* selsp, double tha)
{
	float all = 0;
	CVertex* rtV = VtMove;
	CShape* movS = RtShape;
	CVertex* movV;
	CVertex* nextmV;
	CVertex newmovV;
	CVertex newnextmV;
	CVertex* nowV;
	float Rx1;
	float Ry1;
	float Rx2;
	float Ry2;

	CShape* nowS = shape_head;
	while (nowS->GetNext() != NULL) {
		if (nowS != movS) {
			nowV = nowS->GetVertexhead();
			while (nowV != NULL) {
				movV = movS->GetVertexhead();
				nextmV = movV->GetNext();
				while (nextmV != NULL) {
					Rx1 = (movV->GetX() - rtV->GetX()) * cos(tha) - (movV->GetY() - rtV->GetY()) * sin(tha) + rtV->GetX();
					Ry1 = (movV->GetX() - rtV->GetX()) * sin(tha) + (movV->GetY() - rtV->GetY()) * cos(tha) + rtV->GetY();
					Rx2 = (nextmV->GetX() - rtV->GetX()) * cos(tha) - (nextmV->GetY() - rtV->GetY()) * sin(tha) + rtV->GetX();
					Ry2 = (nextmV->GetX() - rtV->GetX()) * sin(tha) + (nextmV->GetY() - rtV->GetY()) * cos(tha) + rtV->GetY();
					newmovV.SetXY(Rx1,Ry1);
					newnextmV.SetXY(Rx2,Ry2);
					all = all + math.substend_angle(&newmovV, &newnextmV, nowV);
					movV = nextmV;
					nextmV = nextmV->GetNext();
				}
				Rx1 = (movS->GetVertexhead()->GetX() - rtV->GetX()) * cos(tha) - (movS->GetVertexhead()->GetY() - rtV->GetY()) * sin(tha) + rtV->GetX();
				Ry1 = (movS->GetVertexhead()->GetX() - rtV->GetX()) * sin(tha) + (movS->GetVertexhead()->GetY() - rtV->GetY()) * cos(tha) + rtV->GetY();
				Rx2 = (movS->Getvertexfinal()->GetX() - rtV->GetX()) * cos(tha) - (movS->Getvertexfinal()->GetY() - rtV->GetY()) * sin(tha) + rtV->GetX();
				Ry2 = (movS->Getvertexfinal()->GetX() - rtV->GetX()) * sin(tha) + (movS->Getvertexfinal()->GetY() - rtV->GetY()) * cos(tha) + rtV->GetY();
				newmovV.SetXY(Rx1, Ry1);
				newnextmV.SetXY(Rx2, Ry2);
				all = all + math.substend_angle(&newnextmV, &newmovV, nowV);
				if (all < 0) {
					all = all * -1;
				}
				if (2 * M_PI - all < 0.1 && 2 * M_PI - all >-0.1) {
					return true;
				}
				nowV = nowV->GetNext();
				all = 0;
			}

		}
		nowS = nowS->GetNext();
	}
	return false;
}
//��]��������
bool CAdminControl::RTCrossshape(CShape* selsp, double tha)
{
	CVertex* rtV = VtMove;
	CShape* movS = RtShape;
	CVertex* movV;
	CVertex* nextmV;
	CVertex newmovV;
	CVertex newnextmV;
	CVertex* nowV;
	CVertex* nextV;
	float Rx1;
	float Ry1;
	float Rx2;
	float Ry2;
	CVertex diff = diffvt;
	CShape* nowS = shape_head;
	while (nowS->GetNext() != NULL) {
		if (nowS != movS) {
			movV = movS->GetVertexhead();
			nextmV = movV->GetNext();
			while (nextmV != NULL) {
				Rx1 = (movV->GetX() - rtV->GetX()) * cos(tha) - (movV->GetY() - rtV->GetY()) * sin(tha) + rtV->GetX();
				Ry1 = (movV->GetX() - rtV->GetX()) * sin(tha) + (movV->GetY() - rtV->GetY()) * cos(tha) + rtV->GetY();
				Rx2 = (nextmV->GetX() - rtV->GetX()) * cos(tha) - (nextmV->GetY() - rtV->GetY()) * sin(tha) + rtV->GetX();
				Ry2 = (nextmV->GetX() - rtV->GetX()) * sin(tha) + (nextmV->GetY() - rtV->GetY()) * cos(tha) + rtV->GetY();
				newmovV.SetXY(Rx1, Ry1);
				newnextmV.SetXY(Rx2, Ry2);
				nowV = nowS->GetVertexhead();
				nextV = nowV->GetNext();
				while (nextV != NULL) {
					if (nowS->cross_judge(&newmovV, &newnextmV, nowV, nextV)) {
						return true;
					}
					nowV = nextV;
					nextV = nextV->GetNext();
				}

				movV = nextmV;
				nextmV = movV->GetNext();
			}
		}
		nowS = nowS->GetNext();
	}
	return false;
}
//�}�`�ړ�����
void CAdminControl::ShapeMvHouse()
{
		CVertex diff = diffvt;
		CShape* nowS = shape_head;
		CVertex* nowV;
		CShape* movS = SelectSf;
		if (Inoutshape(SelectSf) == false&& OtherInoutshape(SelectSf) == false&&Crossshape(SelectSf) == false) {
			while (nowS->GetNext() != NULL) {
				nowV = nowS->GetVertexhead();
				while (nowV != NULL) {
					if (nowS == movS) {
						nowV->SetXY(nowV->GetX() + diff.GetX(), nowV->GetY() + diff.GetY());
					}
					nowV = nowV->GetNext();
				}
				nowS = nowS->GetNext();
			}
		}
		
}
//�g��k��
void CAdminControl::LargeReduce(float zDelta)
{
	CShape* movS = SelectSf;
	CShape* nowS = shape_head;
	CVertex* nowV;
	//CVertex cg = math.Center_gravity(nowS->GetVertexhead());
	float a;
	if (0 > zDelta) {
		a = 0.95;
	}
	else {
		a = 1.05;
	}

	while (nowS ->GetNext() != NULL) {
		if (nowS==movS) {
			nowV = nowS->GetVertexhead();
			while (nowV != NULL) {
				if (LRInoutshape(movS,a)==false&& LROtherInoutsp(movS, a) == false) {
					//nowV->SetXY(a * (nowV->GetX() - 0) - 0, a * (nowV->GetY() - 0) - 0);
					LRflag = true;
				}
				nowV = nowV->GetNext();
			}
			if (LRflag == true) {
				nowV = nowS->GetVertexhead();
				while (nowV != NULL) {
					nowV->SetXY(a * (nowV->GetX() - 0) - 0, a * (nowV->GetY() - 0) - 0);
					nowV = nowV->GetNext();
				}
				LRflag = false;
			}
		}
		nowS = nowS->GetNext();
	}

}
//��]
void CAdminControl::Rotate(float zDelta)
{
	CVertex* movV=VtMove;
	CVertex* nowV;
	CShape* nowS = shape_head;
	CShape* movS = RtShape;
	float Rx;
	float Ry;
	double tha;
	if (0 > zDelta) {
		tha = 0.05;
	}
	else {
		tha = -0.05;
	}
	while (nowS->GetNext() != NULL) {
		if (nowS == movS) {
			nowV = nowS->GetVertexhead();
			while (nowV != NULL) {
				if (RTInoutshape(movS,tha)==false&& RTOtherInoutsp(movS, tha) == false&&RTCrossshape(movS, tha) == false) {
					//Rx = (nowV->GetX() - movV->GetX()) * cos(tha) - (nowV->GetY() - movV->GetY()) * sin(tha) + movV->GetX();
					//Ry = (nowV->GetX() - movV->GetX()) * sin(tha) + (nowV->GetY() - movV->GetY()) * cos(tha) + movV->GetY();
					//nowV->SetXY(Rx, Ry);
					RTflag = true;
				}
				nowV = nowV->GetNext();
			}
			if (RTflag == true) {
				nowV = nowS->GetVertexhead();
				while (nowV != NULL) {
					Rx = (nowV->GetX() - movV->GetX()) * cos(tha) - (nowV->GetY() - movV->GetY()) * sin(tha) + movV->GetX();
					Ry = (nowV->GetX() - movV->GetX()) * sin(tha) + (nowV->GetY() - movV->GetY()) * cos(tha) + movV->GetY();
					nowV->SetXY(Rx, Ry);
					nowV = nowV->GetNext();
				}
				RTflag = false;
			}
			
		}
		nowS = nowS->GetNext();
	}
}
