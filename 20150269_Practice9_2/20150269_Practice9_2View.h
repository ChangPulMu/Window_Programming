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

// 20150269_Practice9_2View.h : CMy20150269_Practice9_2View 클래스의 인터페이스
//

#pragma once
#include "atltypes.h"


class CMy20150269_Practice9_2View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy20150269_Practice9_2View();
	DECLARE_DYNCREATE(CMy20150269_Practice9_2View)

// 특성입니다.
public:
	CMy20150269_Practice9_2Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy20150269_Practice9_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CPoint m_ptPoints[20];
	int m_nCount;
	CString m_strText;
	int m_nObjectType;
	bool m_bDrawing;
	CPoint m_ptPrev;
	LOGFONT m_lfFont;
	COLORREF m_colorLine;
	COLORREF m_colorFill;
	COLORREF m_colorText;
	float m_fZoom;
	bool m_bViewPoints;
	void DrawEllipse(CDC* pDC);
	void DrawPolygon(CDC* pDC);
	void ResetZoom();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 20150269_Practice9_2View.cpp의 디버그 버전
inline CMy20150269_Practice9_2Doc* CMy20150269_Practice9_2View::GetDocument() const
   { return reinterpret_cast<CMy20150269_Practice9_2Doc*>(m_pDocument); }
#endif

