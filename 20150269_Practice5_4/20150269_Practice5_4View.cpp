
// 20150269_Practice5_4View.cpp : CMy20150269_Practice5_4View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20150269_Practice5_4.h"
#endif

#include "20150269_Practice5_4Doc.h"
#include "20150269_Practice5_4View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20150269_Practice5_4View

IMPLEMENT_DYNCREATE(CMy20150269_Practice5_4View, CView)

BEGIN_MESSAGE_MAP(CMy20150269_Practice5_4View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy20150269_Practice5_4View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy20150269_Practice5_4View 생성/소멸

CMy20150269_Practice5_4View::CMy20150269_Practice5_4View()
	: m_strOutput(_T(""))
	, m_nTextWidth(0)
	, m_nTextHeight(0)
	, m_ptPosition(0)
	, m_bFont(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy20150269_Practice5_4View::~CMy20150269_Practice5_4View()
{
}

BOOL CMy20150269_Practice5_4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy20150269_Practice5_4View 그리기

void CMy20150269_Practice5_4View::OnDraw(CDC* pDC)
{
	CMy20150269_Practice5_4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	// 실제 글꼴 변수를 선언한다.
	CFont *oldFont, *currentFont, newFont;

	if (m_bFont == TRUE)			// 폰트 대화상자에서 선택한 글꼴을 현재 글꼴로 설정
	{
		newFont.CreateFontIndirect(&m_logFont);
		oldFont = pDC->SelectObject(&newFont);
	}
	else							// 폰트 대화상자에서 글꼴을 선택하지 않으면 현재 글꼴을 사용
	{
		currentFont = pDC->GetCurrentFont();
		oldFont = pDC->SelectObject(currentFont);
	}

	// 색상 대화상자에서 선택한 색상을 텍스트 색상으로 설정
	pDC->SetTextColor(m_colorText);

	// 설정한 위치에 문자열 출력
	pDC->TextOutW(m_ptPosition.x, m_ptPosition.y, m_strOutput);

	// 출력되는 문자열의 너비와 높이를 구함
	CSize sizeText;
	sizeText = pDC->GetTextExtent(m_strOutput);
	m_nTextWidth = sizeText.cx;
	m_nTextHeight = sizeText.cy;

	// 글꼴을 삭제
	pDC->SelectObject(oldFont);
}


// CMy20150269_Practice5_4View 인쇄


void CMy20150269_Practice5_4View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy20150269_Practice5_4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy20150269_Practice5_4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy20150269_Practice5_4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMy20150269_Practice5_4View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy20150269_Practice5_4View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy20150269_Practice5_4View 진단

#ifdef _DEBUG
void CMy20150269_Practice5_4View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20150269_Practice5_4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20150269_Practice5_4Doc* CMy20150269_Practice5_4View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20150269_Practice5_4Doc)));
	return (CMy20150269_Practice5_4Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20150269_Practice5_4View 메시지 처리기


void CMy20150269_Practice5_4View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)						// 가상키 코드 값에 대해
	{
	case VK_LEFT:						// 왼쪽 화살표 키를 누를 때
		m_ptPosition.x -= 10;			// 왼쪽으로 10 이동
		break;
	case VK_RIGHT:						// 오른쪽 화살표 키를 누를 때
		m_ptPosition.x += 10;			// 오른쪽으로 10 이동
		break;
	case VK_UP:							// 위쪽 화살표 키를 누를 때
		m_ptPosition.y -= 10;			// 위쪽으로 10 이동
		break;
	case VK_DOWN:						// 아래쪽 화살표 키를 누를 때
		m_ptPosition.y += 10;			// 아래쪽으로 10 이동
		break;
	}
	if (m_ptPosition.x < 0)				// 문자열이 왼쪽 경계선이 도달하면
	{
		m_ptPosition.x = 0;				// m_ptPosition.x = 0으로 초기화
		AfxMessageBox(_T("왼쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptPosition.y < 0)				// 문자열이 위쪽 경계선이 도달하면
	{
		m_ptPosition.y = 0;				// m_ptPosition.y = 0으로 초기화
		AfxMessageBox(_T("위쪽으로 더 이상 이동할 수 없습니다."));
	}
	RECT rect;
	GetClientRect(&rect);
	if (m_ptPosition.x > rect.right - m_nTextWidth)			// 문자열 끝이 오른쪽 경계선이 도달하면
	{
		m_ptPosition.x = rect.right - m_nTextWidth;
		AfxMessageBox(_T("오른쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptPosition.y > rect.bottom - m_nTextHeight)		// 문자열 끝이 아래쪽 경계선이 도달하면
	{
		m_ptPosition.y = rect.bottom - m_nTextHeight;
		AfxMessageBox(_T("아래쪽으로 더 이상 이동할 수 없습니다."));
	}

	// 변경된 문자열의 좌표 값을 도킹 팬의 X, Y Edit Control에 반영한다.
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->m_paneTextOut.m_ctrlTextOut.SetDlgItemInt(IDC_EDIT_X, m_ptPosition.x);
	pFrame->m_paneTextOut.m_ctrlTextOut.SetDlgItemInt(IDC_EDIT_Y, m_ptPosition.y);
	Invalidate();						// 화면 갱신

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
