
// 20150269_Practice10_1Doc.cpp : CMy20150269_Practice10_1Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20150269_Practice10_1.h"
#endif

#include "20150269_Practice10_1Doc.h"
#include "MainFrm.h"
#include "20150269_Practice10_1View.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy20150269_Practice10_1Doc

IMPLEMENT_DYNCREATE(CMy20150269_Practice10_1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy20150269_Practice10_1Doc, CDocument)
END_MESSAGE_MAP()


// CMy20150269_Practice10_1Doc 생성/소멸

CMy20150269_Practice10_1Doc::CMy20150269_Practice10_1Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMy20150269_Practice10_1Doc::~CMy20150269_Practice10_1Doc()
{
}

BOOL CMy20150269_Practice10_1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMy20150269_Practice10_1Doc serialization

void CMy20150269_Practice10_1Doc::Serialize(CArchive& ar)
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20150269_Practice10_1View * pView = (CMy20150269_Practice10_1View *)pFrame->GetActiveView();
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar << pView->m_nX;
		ar << pView->m_nY;
		ar << pView->m_nRed;
		ar << pView->m_nGreen;
		ar << pView->m_nBlue;
		ar << pView->m_strText;
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		ar >> pView->m_nX;
		ar >> pView->m_nY;
		ar >> pView->m_nRed;
		ar >> pView->m_nGreen;
		ar >> pView->m_nBlue;
		ar >> pView->m_strText;
		pView->m_colorText = RGB(pView->m_nRed, pView->m_nGreen, pView->m_nBlue);
		UpdateAllViews(NULL);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMy20150269_Practice10_1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMy20150269_Practice10_1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMy20150269_Practice10_1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy20150269_Practice10_1Doc 진단

#ifdef _DEBUG
void CMy20150269_Practice10_1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy20150269_Practice10_1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy20150269_Practice10_1Doc 명령
