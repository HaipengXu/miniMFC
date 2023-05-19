#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define MINI_MESSAGE_DECLARE()																\
	static LRESULT OnChar(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);				\
	static LRESULT OnLButtonDown(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);		\
	static LRESULT OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);				\
	static LRESULT OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			\
	static LRESULT OnCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			\

#define MINI_MESSAGE_MAP()									\
const MiniWnd::tagMESSAGEMAP MiniWnd::MessageMaps[] = {		\
		WM_CHAR,			OnChar,							\
		WM_LBUTTONDOWN,		OnLButtonDown,					\
		WM_PAINT,			OnPaint,						\
		WM_DESTROY,			OnDestroy,						\
		WM_CREATE,			OnCreate,						\
};															\

#include "MiniMFC.h"

MiniApp theApp;

LRESULT MiniWnd::OnChar(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	TCHAR sztchar[20];
	wsprintf(sztchar, TEXT("you pressed %c key"), (TCHAR)wParam);
	MessageBox(hWnd, sztchar, TEXT("WM_CHAR"), 0);
	return 0;
}

LRESULT MiniWnd::OnLButtonDown(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	HDC hdc;
	hdc = GetDC(hWnd);
	TextOut(hdc, 0, 50, TEXT("win32 to MFC"), wcslen(TEXT("win32 to MFC")));
	ReleaseDC(hWnd, hdc);
	return 0;
}

LRESULT MiniWnd::OnPaint(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	HDC hDC;
	PAINTSTRUCT ps;
	hDC = BeginPaint(hWnd, &ps);
	TextOut(hDC, 0, 0, TEXT("Hello world!"), wcslen(TEXT("Hello world!")));
	EndPaint(hWnd, &ps);
	return 0;
}

LRESULT MiniWnd::OnDestroy(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	PostQuitMessage(0);
	return 0;
}

LRESULT MiniWnd::OnCreate(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	::MessageBox(NULL, __T("onCreate"), __T("onCreate"), MB_OK);
	return 0;
}