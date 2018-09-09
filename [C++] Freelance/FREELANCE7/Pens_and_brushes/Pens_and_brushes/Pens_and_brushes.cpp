// Pens_and_brushes.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Pens_and_brushes.h"
#include <commdlg.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

COLORREF gColor;
int gBrushType, gStylePen, gWidthPen;


void HandleList(HWND hDlg) {
	SendDlgItemMessage(hDlg, IDC_COMBO_PENWIDTH, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1");
	SendDlgItemMessage(hDlg, IDC_COMBO_PENWIDTH, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"4");
	SendDlgItemMessage(hDlg, IDC_COMBO_PENWIDTH, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"6");
	SendDlgItemMessage(hDlg, IDC_COMBO_PENWIDTH, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"8"); 
	SendDlgItemMessage(hDlg, IDC_COMBO_PENWIDTH, LB_SETCURSEL, (WPARAM)1, 0);
}
void HandleColorChoise(HWND hDlg) {
	CHOOSECOLOR cc;
	static COLORREF custcolor[16];
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hDlg;
	cc.hInstance = NULL;
	cc.rgbResult = gColor;
	cc.lpCustColors = custcolor;
	cc.Flags = CC_RGBINIT;
	cc.lCustData = 0;
	cc.lpfnHook = NULL;
	cc.lpTemplateName = NULL;
	if (ChooseColor(&cc))
		gColor = cc.rgbResult;
}
void HandlerOnOk(HWND hDlg) {
	if (IsDlgButtonChecked(hDlg, IDC_HS_BDIAGONAL) == BST_CHECKED)
		gBrushType = HS_BDIAGONAL;
	if (IsDlgButtonChecked(hDlg, IDC_HS_CROSS) == BST_CHECKED)
		gBrushType = HS_CROSS;
	if (IsDlgButtonChecked(hDlg, IDC_HS_DIAGCROSS) == BST_CHECKED)
		gBrushType = HS_DIAGCROSS;
	if (IsDlgButtonChecked(hDlg, IDC_HS_FDIAGONAL) == BST_CHECKED)
		gBrushType = HS_FDIAGONAL;
	if (IsDlgButtonChecked(hDlg, IDC_HS_HORIZONTAL) == BST_CHECKED)
		gBrushType = HS_HORIZONTAL;
	if (IsDlgButtonChecked(hDlg, IDC_HS_VERTICAL) == BST_CHECKED)
		gBrushType = HS_VERTICAL;
	if (IsDlgButtonChecked(hDlg, IDC_PS_SOLID) == BST_CHECKED)
		gStylePen = PS_SOLID;
	if (IsDlgButtonChecked(hDlg, IDC_PS_DASH) == BST_CHECKED)
		gStylePen = PS_DASH;
	if (IsDlgButtonChecked(hDlg, IDC_PS_DOT) == BST_CHECKED)
		gStylePen = PS_DOT;
	if (IsDlgButtonChecked(hDlg, IDC_PS_DASHDOT) == BST_CHECKED)
		gStylePen = PS_DASHDOT;
	if (IsDlgButtonChecked(hDlg, IDC_PS_DASHDOTDOT) == BST_CHECKED)
		gStylePen = PS_DASHDOTDOT;
	wchar_t buff[3];
	GetDlgItemText(hDlg, IDC_COMBO_PENWIDTH, (LPWSTR)buff, 2);
	gWidthPen = _wtoi(buff);
}
void InitGroupBrush(HWND hDlg) {
	switch (gBrushType)
	{
	case HS_BDIAGONAL: {
		SendDlgItemMessage(hDlg, IDC_HS_BDIAGONAL, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	case HS_CROSS: {
		SendDlgItemMessage(hDlg, IDC_HS_CROSS, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	case HS_DIAGCROSS: {
		SendDlgItemMessage(hDlg, IDC_HS_DIAGCROSS, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	case HS_FDIAGONAL: {
		SendDlgItemMessage(hDlg, IDC_HS_FDIAGONAL, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	case HS_HORIZONTAL: {
		SendDlgItemMessage(hDlg, IDC_HS_HORIZONTAL, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	case HS_VERTICAL: {
		SendDlgItemMessage(hDlg, IDC_HS_VERTICAL, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	default:
		break;
	}
}
void InitPen(HWND hDlg) {
	switch (gStylePen)
	{
	case PS_SOLID: {
		SendDlgItemMessage(hDlg, IDC_PS_SOLID, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	case PS_DASH: {
		SendDlgItemMessage(hDlg, IDC_PS_DASH, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	case PS_DOT: {
		SendDlgItemMessage(hDlg, IDC_PS_DOT, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	case PS_DASHDOT: {
		SendDlgItemMessage(hDlg, IDC_PS_DASHDOT, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	case PS_DASHDOTDOT: {
		SendDlgItemMessage(hDlg, IDC_PS_DASHDOTDOT, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
	default:
		break;
	}
}
void HandleOnInitDialog(HWND hDlg) {
	InitGroupBrush(hDlg);
	InitPen(hDlg);
	HandleList(hDlg);
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PENSANDBRUSHES, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PENSANDBRUSHES));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PENSANDBRUSHES));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PENSANDBRUSHES);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK DlgSetup(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_INITDIALOG: {
		HandleOnInitDialog(hDlg);
		return TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_CHOOSE_COLOR: {
			HandleColorChoise(hDlg);
			break;
		}
		case IDOK: {
			HandlerOnOk(hDlg);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		case IDCANCEL: { 
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		default:
			break;
		}
	default:
		break;
	}
	return FALSE;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{ 
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case  IDC_CHOOSE_COLOR: {
			HandleColorChoise(hWnd);
			break;
		}
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_TEST_SETUP: {

			if (DialogBox(hInst, (LPCTSTR)IDD_DIALOG_PAINT, hWnd, (DLGPROC)DlgSetup) == IDOK) {
				RECT rc;
				GetClientRect(hWnd, &rc);
				InvalidateRect(hWnd, NULL, TRUE);
			}

			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rt;
		HBRUSH hbrNew, hbrOld;
		HPEN penNew, penOld;
		hbrNew = CreateHatchBrush(gBrushType, gColor);
		penNew = CreatePen(gStylePen, gWidthPen, gColor);
		hbrOld = (HBRUSH)SelectObject(hdc, hbrNew);
		penOld = (HPEN)SelectObject(hdc, penNew);
		GetClientRect(hWnd, &rt);
		Rectangle(hdc, 5, 5, rt.right - rt.left - 5, rt.bottom - rt.top - 5);
		SelectObject(hdc, hbrOld);
		SelectObject(hdc, penOld);
		DeleteObject(hbrNew);
		DeleteObject(penNew);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
