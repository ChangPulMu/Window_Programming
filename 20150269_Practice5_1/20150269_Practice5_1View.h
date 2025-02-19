
// 20150269_Practice5_1View.h : CMy20150269_Practice5_1View 클래스의 인터페이스
//
#include "atltypes.h"
enum DRAW_MODE { LINE_MODE, ELLIPSE_MODE, POLYGON_MODE };

#pragma once


class CMy20150269_Practice5_1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy20150269_Practice5_1View();
	DECLARE_DYNCREATE(CMy20150269_Practice5_1View)

// 특성입니다.
public:
	CMy20150269_Practice5_1Doc* GetDocument() const;

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
	virtual ~CMy20150269_Practice5_1View();
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
	afx_msg void OnLine();
	afx_msg void OnEllipse();
	afx_msg void OnPolygon();
	afx_msg void OnLineColor();
	afx_msg void OnFaceColor();
	afx_msg void OnBdiagonal();
	afx_msg void OnCross();
	afx_msg void OnVertical();
	int m_nDrawMode;
	int m_nHatchStyle;
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePolygon(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CPoint m_ptStart;				// 시작점을 저장하는 변수
	CPoint m_ptPrev;				// 이전점을 저장하는 변수
	bool m_bFirst;					// 처음 그리는 것인지 체크하는 변수
	bool m_bLButtonDown;			// 왼쪽 버튼이 눌렸는지 체크하는 변수
	bool m_bContextMenu;			// 컨텍스트 메뉴의 활성화를 체크하는 변수
	bool m_bHatch;					// 해치 브러시를 사용하는지를 체크하는 변수
	CPoint m_ptData[50];			// 다각형의 점을 저장할 배열
	int m_nCount;					// m_ptData 배열의 카운트를 저장하는 변수
	COLORREF m_colorPen;			// 펜 색상을 설정하는 변수
	COLORREF m_colorBrush;			// 브러시 색상을 설정하는 변수
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 20150269_Practice5_1View.cpp의 디버그 버전
inline CMy20150269_Practice5_1Doc* CMy20150269_Practice5_1View::GetDocument() const
   { return reinterpret_cast<CMy20150269_Practice5_1Doc*>(m_pDocument); }
#endif

