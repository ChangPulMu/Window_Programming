// CalenderDll.cpp : 해당 DLL의 초기화 루틴을 정의합니다.
//

#include "stdafx.h"
#include "CalenderDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 이 DLL이 MFC DLL에 대해 동적으로 링크되어 있는 경우
//		MFC로 호출되는 이 DLL에서 내보내지는 모든 함수의
//		시작 부분에 AFX_MANAGE_STATE 매크로가
//		들어 있어야 합니다.
//
//		예:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 일반적인 함수 본문은 여기에 옵니다.
//		}
//
//		이 매크로는 MFC로 호출하기 전에
//		각 함수에 반드시 들어 있어야 합니다.
//		즉, 매크로는 함수의 첫 번째 문이어야 하며 
//		개체 변수의 생성자가 MFC DLL로
//		호출할 수 있으므로 개체 변수가 선언되기 전에
//		나와야 합니다.
//
//		자세한 내용은
//		MFC Technical Note 33 및 58을 참조하십시오.
//

// CCalenderDllApp

BEGIN_MESSAGE_MAP(CCalenderDllApp, CWinApp)
END_MESSAGE_MAP()


// CCalenderDllApp 생성

CCalenderDllApp::CCalenderDllApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CCalenderDllApp 개체입니다.

CCalenderDllApp theApp;


// CCalenderDllApp 초기화

BOOL CCalenderDllApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

// 외부에서 호출할 함수
extern "C" __declspec(dllexport) void Calender(int year, int month, int *Days);

// Calender 함수에서 사용할 함수들로서 미리 선언한다.
int FirstDay(int year, int month);
bool IsLeapYear(int year);

// 윤년일 때와 윤년이 아닐 때의 각 달에 대한 날자 수를 변수에 저장한다.
static int DaysOfMonth[2][12] =
{
	{31,28,31,30,31,30,31,31,30,31,30,31},
	{31,29,31,30,31,30,31,31,30,31,30,31},
};

// 시작 년도와 마지막 년도를 설정한다.
int m_nStartYear = 1583;
int m_nEndYear = 4040;
int m_nStartMonth = 0;

bool IsLeapYear(int year)
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;			// 윤년입니다.
	else
		return false;			// 윤년이 아닙니다.
}

int FirstDay(int year, int month)
{
	int i, day = 0;

	// 시작 년도부터 현재 입력된 년도까지 일수를 계산한다.
	for (i = m_nStartYear; i < year; i++)
	{
		if (IsLeapYear(i))
			day += 366;				// 윤년일 경우는 366일로 계산한다.
		else
			day += 365;				// 윤년이 아닌 경우는 365일로 계산한다.
		day %= 7;
	}

	// 1월부터 전달까지의 날짜 수를 더한다.
	for (i = m_nStartMonth; i < month; ++i)
	{
		day += DaysOfMonth[IsLeapYear(year)][i];
		day %= 7;
	}
	if (day == 0)
		day = 7;

	return(day - 1);
}

_declspec(dllexport) void Calender(int year, int month, int *Days)
{
	int ThisDay, EndDay, Week, i;

	// 그 달의 첫 번째 날이 무슨 요일에 시작하는지를 구한다.
	ThisDay = FirstDay(year, month);

	// 그 달이 며칠까지 있는지를 계산한다.
	EndDay = DaysOfMonth[IsLeapYear(year)][month];
	Week = 0;

	// 각 날짜를 호출한 함수에서 받는 6*7 행렬에 저장한다.
	for (i = 1; i <= EndDay; i++)
	{
		*(Days + (Week * 7) + ThisDay) = i;
		ThisDay++;
		if (ThisDay == 7)
		{
			ThisDay = 0;
			Week++;
		}
	}
}