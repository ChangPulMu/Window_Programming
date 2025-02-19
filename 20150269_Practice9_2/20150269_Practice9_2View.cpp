// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// 20150269_Practice9_2View.cpp : CMy20150269_Practice9_2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20150269_Practice9_2.h"
#endif

#include "20150269_Practice9_2Doc.h"
#include "20150269_Practice9_2View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20150269_Practice9_2View

IMPLEMENT_DYNCREATE(CMy20150269_Practice9_2View, CView)

BEGIN_MESSAGE_MAP(CMy20150269_Practice9_2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy20150269_Practice9_2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONDBLCLK()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMy20150269_Practice9_2View 생성/소멸

CMy20150269_Practice9_2View::CMy20150269_Practice9_2View()
	: m_nCount(0)
	, m_strText(_T(""))
	, m_nObjectType(0)
	, m_bDrawing(false)
	, m_ptPrev(0)
	, m_fZoom(0)
	, m_bViewPoints(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_strText = _T("Hello, MFC Programming!");
	m_nObjectType = -1;

	afxGlobalData.fontRegular.GetLogFont(&m_lfFont);
	m_lfFont.lfHeight = 20;

	m_colorLine = RGB(0, 0, 0);
	m_colorFill = RGB(255, 255, 255);
	m_colorText = RGB(0, 0, 255);
	m_fZoom = 1.0f;
	m_bViewPoints = true;
}

CMy20150269_Practice9_2View::~CMy20150269_Practice9_2View()
{
}

BOOL CMy20150269_Practice9_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy20150269_Practice9_2View 그리기

void CMy20150269_Practice9_2View::OnDraw(CDC* pDC)
{
	CMy20150269_Practice9_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CRect rc;
	GetClientRect(&rc);

	CPen pen, *pOldPen;
	CBrush brush, *pOldBrush;
	CFont font, *pOldFont;

	pen.CreatePen(PS_SOLID, 2, m_colorLine);
	brush.CreateSolidBrush(m_colorFill);
	font.CreateFontIndirect(&m_lfFont);

	pOldPen = pDC->SelectObject(&pen);
	pOldBrush = pDC->SelectObject(&brush);
	pOldFont = pDC->SelectObject(&font);

	switch (m_nObjectType)
	{
	case 0:
		DrawEllipse(pDC);		// 타원 그리기
		break;
	case 1:
		DrawPolygon(pDC);		// 다각형 그리기
		break;
	}

	pDC->SetTextColor(m_colorText);
	pDC->DrawText(m_strText, &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldFont);

	pen.DeleteObject();
	brush.DeleteObject();
	font.DeleteObject();
}


// CMy20150269_Practice9_2View 인쇄


void CMy20150269_Practice9_2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy20150269_Practice9_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy20150269_Practice9_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy20150269_Practice9_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMy20150269_Practice9_2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy20150269_Practice9_2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy20150269_Practice9_2View 진단

#ifdef _DEBUG
void CMy20150269_Practice9_2View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20150269_Practice9_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20150269_Practice9_2Doc* CMy20150269_Practice9_2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20150269_Practice9_2Doc)));
	return (CMy20150269_Practice9_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20150269_Practice9_2View 메시지 처리기


void CMy20150269_Practice9_2View::DrawEllipse(CDC* pDC)
{
	if (!m_nCount)
		return;

	int x1, y1, x2, y2;
	if (m_nCount < 2)
	{
		x1 = (int)((float)m_ptPoints[0].x*m_fZoom);
		y1 = (int)((float)m_ptPoints[0].y*m_fZoom);
		if (m_bViewPoints)
			pDC->Ellipse(x1 - 4, y1 - 4, x1 + 4, y1 + 4);
	}
	else
	{
		x1 = (int)((float)m_ptPoints[0].x*m_fZoom);
		y1 = (int)((float)m_ptPoints[0].y*m_fZoom);
		x2 = (int)((float)m_ptPoints[1].x*m_fZoom);
		y2 = (int)((float)m_ptPoints[1].y*m_fZoom);
		pDC->Ellipse(x1, y1, x2, y2);
		if (m_bViewPoints)
		{
			pDC->Ellipse(x1 - 4, y1 - 4, x1 + 4, y1 + 4);
			pDC->Ellipse(x2 - 4, y2 - 4, x2 + 4, y2 + 4);
		}
	}
}


void CMy20150269_Practice9_2View::DrawPolygon(CDC* pDC)
{
	CPoint pPoints[20];
	for (int i = 0; i < m_nCount; i++)
	{
		pPoints[i].x = (int)((float)m_ptPoints[i].x*m_fZoom);
		pPoints[i].y = (int)((float)m_ptPoints[i].y*m_fZoom);
	}

	// 다각형 그리기
	if (m_bDrawing)
		pDC->Polyline(pPoints, m_nCount);
	else
		pDC->Polygon(pPoints, m_nCount);

	if (m_bViewPoints)
	{
		for (int i = 0; i < m_nCount; i++)
			pDC->Ellipse(pPoints[i].x - 4, pPoints[i].y - 4, pPoints[i].x + 4, pPoints[i].y + 4);
	}
}


void CMy20150269_Practice9_2View::ResetZoom()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCRibbonSlider* pZoom = DYNAMIC_DOWNCAST(CMFCRibbonSlider, pFrame->GetRibbonBar()->FindByID(ID_SLIDER_ZOOM));
	pZoom->SetPos(100);

	m_fZoom = 1.0f;
	Invalidate();
}


void CMy20150269_Practice9_2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nObjectType == 0)
	{
		if (m_nCount == 0 || m_nCount >= 2)
		{
			ResetZoom();
			m_nCount = 0;
			m_bDrawing = true;
		}
		m_ptPoints[m_nCount++] = point;
		if (m_nCount == 2)
			m_bDrawing = false;

		Invalidate();
	}
	else if (m_nObjectType == 1)
	{
		if (!m_bDrawing)
		{
			ResetZoom();
			m_nCount = 0;
			m_bDrawing = true;
		}
		m_ptPoints[m_nCount++] = point;
		Invalidate();
	}
	m_ptPrev = point;

	CView::OnLButtonDown(nFlags, point);
}


void CMy20150269_Practice9_2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nObjectType == 1)
	{
		if (m_bDrawing)
			m_bDrawing = false;

		Invalidate();
	}

	CView::OnLButtonDblClk(nFlags, point);
}


void CMy20150269_Practice9_2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nCount < 1 || !m_bDrawing)
		return;

	CClientDC dc(this);
	switch (m_nObjectType)
	{
	case 0:
		DrawEllipse(&dc);		// 타원 그리기
		break;
	case 1:
		DrawPolygon(&dc);		// 다각형 그리기
		break;
	}
	dc.SetROP2(R2_NOT);
	dc.MoveTo(m_ptPoints[m_nCount - 1]);
	dc.LineTo(m_ptPrev);

	dc.SetROP2(R2_COPYPEN);
	dc.MoveTo(m_ptPoints[m_nCount - 1]);
	dc.LineTo(point);

	m_ptPrev = point;

	CView::OnMouseMove(nFlags, point);
}
