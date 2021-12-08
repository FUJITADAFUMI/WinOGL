
// WinOGLView.cpp : CWinOGLView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "WinOGL.h"
#endif

#include "WinOGLDoc.h"
#include "WinOGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinOGLView

IMPLEMENT_DYNCREATE(CWinOGLView, CView)

BEGIN_MESSAGE_MAP(CWinOGLView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_XYZ, &CWinOGLView::OnXyz)
	ON_COMMAND(ID_vtchoice, &CWinOGLView::Onvtchoice)
	ON_UPDATE_COMMAND_UI(ID_XYZ, &CWinOGLView::OnUpdateXyz)
	ON_UPDATE_COMMAND_UI(ID_vtchoice, &CWinOGLView::OnUpdatevtchoice)
	ON_COMMAND(ID_sfchoice, &CWinOGLView::Onsfchoice)
	ON_UPDATE_COMMAND_UI(ID_sfchoice, &CWinOGLView::OnUpdatesfchoice)
	ON_COMMAND(ID_edgechoice, &CWinOGLView::Onedgechoice)
	ON_UPDATE_COMMAND_UI(ID_edgechoice, &CWinOGLView::OnUpdateedgechoice)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_vtmove, &CWinOGLView::Onvtmove)
	ON_UPDATE_COMMAND_UI(ID_vtmove, &CWinOGLView::OnUpdatevtmove)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CWinOGLView コンストラクション/デストラクション

CWinOGLView::CWinOGLView() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CWinOGLView::~CWinOGLView()
{
}

BOOL CWinOGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CWinOGLView 描画

void CWinOGLView::OnDraw(CDC* pDC)
{
	CWinOGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。

	wglMakeCurrent(pDC->m_hDC, m_hRC);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT	/*	|	GL_DEPTH_BUFFER_BIT*/);

	AC.Draw();

	glFlush();
	SwapBuffers(pDC->m_hDC);

	wglMakeCurrent(pDC->m_hDC, NULL);
}


// CWinOGLView の診断

#ifdef _DEBUG
void CWinOGLView::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDoc* CWinOGLView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDoc)));
	return (CWinOGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLView メッセージ ハンドラー


void CWinOGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	CRect rect;
	GetClientRect(rect);

	float hi;
	float w = rect.Width();
	float h = rect.Height();

	clickX = (float)point.x/w;
	clickY = 1-(float)point.y/h;

	if (w > h)
	{
		hi = (float)w / h;
		clickX = (float)clickX * 2 - 1;
		clickX = (float)clickX * hi;
		clickY = (float)clickY * 2 - 1;
		glOrtho(-1 * hi,1*hi, -1, 1, -100, 100);
	}
	else
	{
		hi = (float)h / w;
		clickX = (float)clickX * 2 - 1;
		clickX = (float)clickY * 2 - 1;
		clickY = (float)clickY *hi;
		glOrtho(-1, 1, -1 * hi, 1 * hi, -100, 100);
	}

	AC.CreateShape(clickX, clickY);
	if (AC.GetVertexFlag()&&AC.GetVtMoveFlag()==false) {
		AC.SelX(clickX);
		AC.SelY(clickY);
	}
	if (AC.GetSurfaceFlag()) {
		AC.SelX(clickX);
		AC.SelY(clickY);
	}
	if (AC.GetEdgeFlag()) {
		AC.SelX(clickX);
		AC.SelY(clickY);
	}
	//AC.AppendShape();
	//AC.Append_vertex(clickX, clickY);
	AC.SetVtmouseflag();

	RedrawWindow();

	CView::OnLButtonDown(nFlags, point);
}


int CWinOGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: ここに特定な作成コードを追加してください。
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|
		PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		24,
		0,0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	CClientDC	clientDC(this);
	int	pixelFormat = ChoosePixelFormat(clientDC.m_hDC, &pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	return 0;
}


void CWinOGLView::OnDestroy()
{
	CView::OnDestroy();
	wglDeleteContext(m_hRC);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
}


BOOL CWinOGLView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	return true;
}


void CWinOGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	CClientDC clientDC(this);
	wglMakeCurrent(clientDC.m_hDC, m_hRC);

	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);	//問5.2で考える内容
	glLoadIdentity();

	double hi;
	if (cx<cy)
	{
		hi = (double)cy / cx;
		glOrtho(-1, 1, -1*hi, 1 * hi, -100, 100);
	}
	else
	{
		hi = (double)cx / cy;
		glOrtho(-1 * hi, 1 * hi, -1, 1, -100, 100);
	}

	glMatrixMode(GL_MODELVIEW);

	RedrawWindow();
	wglMakeCurrent(clientDC.m_hDC, NULL);
}


void CWinOGLView::OnXyz()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	/*--------------------------------------------------------*/
/* CAdminControlクラスのメンバ変数AxisFlagの状態を切り替える
*/
/*--------------------------------------------------------*/
	AC.SetAxisFlag();
	RedrawWindow();
}



void CWinOGLView::Onvtchoice()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.SetVertexFlag();
	RedrawWindow();
}


void CWinOGLView::OnUpdateXyz(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (AC.GetAxisFlag()) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnUpdatevtchoice(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (AC.GetVertexFlag()) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::Onsfchoice()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.SetSurfaceFlag();
	RedrawWindow();
}


void CWinOGLView::OnUpdatesfchoice(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (AC.GetSurfaceFlag()) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::Onedgechoice()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.SetEdgeFlag();
	RedrawWindow();
}


void CWinOGLView::OnUpdateedgechoice(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (AC.GetEdgeFlag()) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if ((AC.GetVtmouseflag() &&AC.GetVtMoveFlag())||(AC.GetRmouseflag()&&AC.GetSurfaceFlag())) {
		CRect rect;
		GetClientRect(rect);

		float hi;
		float w = rect.Width();
		float h = rect.Height();

		if (AC.GetVtMoveFlag()|| AC.GetRmouseflag()) {
			clickX = (float)point.x / w;
			clickY = 1 - (float)point.y / h;

			if (w > h)
			{
				hi = (float)w / h;
				clickX = (float)clickX * 2 - 1;
				clickX = (float)clickX * hi;
				clickY = (float)clickY * 2 - 1;
				glOrtho(-1 * hi, 1 * hi, -1, 1, -100, 100);
			}
			else
			{
				hi = (float)h / w;
				clickX = (float)clickX * 2 - 1;
				clickX = (float)clickY * 2 - 1;
				clickY = (float)clickY * hi;
				glOrtho(-1, 1, -1 * hi, 1 * hi, -100, 100);
			}

			AC.MvX(clickX);
			AC.MvY(clickY);
		}
	}
	RedrawWindow();
	CView::OnMouseMove(nFlags, point);
}


void CWinOGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	
	AC.MoveIn(AC.mvX(),AC.mvY());
	AC.SetVtmouseflag();
	RedrawWindow();
	CView::OnLButtonUp(nFlags, point);
}


void CWinOGLView::Onvtmove()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.SetVtMoveFlag();
	
	RedrawWindow();
}


void CWinOGLView::OnUpdatevtmove(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (AC.GetVtMoveFlag()) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	AC.SetRmouseflag();
	CRect rect;
	GetClientRect(rect);

	float hi;
	float w = rect.Width();
	float h = rect.Height();

	RclickX = (float)point.x / w;
	RclickY = 1 - (float)point.y / h;

	if (w > h)
	{
		hi = (float)w / h;
		RclickX = (float)RclickX * 2 - 1;
		RclickX = (float)RclickX * hi;
		RclickY = (float)RclickY * 2 - 1;
		glOrtho(-1 * hi, 1 * hi, -1, 1, -100, 100);
	}
	else
	{
		hi = (float)h / w;
		RclickX = (float)RclickX * 2 - 1;
		RclickX = (float)RclickY * 2 - 1;
		RclickY = (float)RclickY * hi;
		glOrtho(-1, 1, -1 * hi, 1 * hi, -100, 100);
	}

	AC.RSelX(RclickX);
	AC.RSelY(RclickY);
	//AC.AppendShape();
	//AC.Append_vertex(clickX, clickY);
	
	RedrawWindow();

	CView::OnLButtonDown(nFlags, point);
}


void CWinOGLView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if (AC.GetShapeMoovflag()) {
		AC.ShapeMvHouse();
		AC.SetShapeMoovflag();
	}
	AC.SetRmouseflag();
	
	RedrawWindow();
	CView::OnRButtonUp(nFlags, point);
}
