#include <string.h>
#include "tabctl.h"
#include "const.h"
#include "utils.h"
#include "sisw.h"

static WNDPROC old_si_sw_proc = NULL;

static LRESULT CALLBACK SiSwSubClass(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lr = CallWindowProc(old_si_sw_proc, hWnd, uMsg, wParam, lParam);
	
	switch(uMsg)
	{
	case WM_SETTEXT:
		{
			char text[SI_BUF_SIZE];
			GetSiSwTitle((LPCSTR)lParam,text);
			SiTabCtl_SetItemText(hWnd,text);
		}
		break;
	default:
		break;
	}

	return lr;
}

//获取si_Sw窗口过程
void HookSiSw(HWND hwnd)
{
	old_si_sw_proc = (WNDPROC)GetWindowLong(hwnd,GWL_WNDPROC);
	SetWindowLong(hwnd,GWL_WNDPROC,(DWORD)SiSwSubClass);
}

//恢复si_Sw窗口过程
void UnhookSiSw(HWND hwnd)
{
	SetWindowLong(hwnd,GWL_WNDPROC,(DWORD)old_si_sw_proc);
}
