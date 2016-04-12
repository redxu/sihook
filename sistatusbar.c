#include <windows.h>

extern HWND hwnd_si_frame;

#define SI_GetRectXY(zone, rect, x, y) (((int (__stdcall *)(int, RECT*, int*, int*))0x4F5BB7)(zone, rect, x, y))

static const char* codec_name[10] = {
	"ANSI",
	"UTF8",
	"UTF8(dom)"
};

//si build0082
//disasm from 0x4F5BB7
static void SiStatusBar_GetRectXY1(RECT* rect, int* x, int* y)
{
	int _loc1,_loc2,_loc3,_loc4,_loc5;
	GetClientRect(hwnd_si_frame,rect);
	rect->top = rect->bottom - 0x12;
	rect->top += (0xc / 4);
	rect->bottom -= (0xc / 4);
	_loc2 = 0x60 / 8;
	rect->left = _loc2;
	rect->right -= _loc2;  //local2
	//6 * 5;  //local5
	_loc5 = 6 * 5;
	//call 404166 ->local1  = rect->right - rect->left;
	//local1 -= (local2 + local5)
	_loc1 = rect->right - rect->left;
	_loc1 -= (_loc2 + _loc5);
	
	//jle 6*0x50
	if(_loc1 > 6*0x50)
	{
		//call 408beb ->local4 = local1 / 2;
		_loc4 = _loc1 / 2;
	}
	else
	{
		//i don't know loc4
		_loc4 = 0;
		OutputDebugString("jle!!!!!!!!");
	}
	//local3 = local1 - local4 - local2
	//if(sbid == 1)
	_loc3 = _loc1 - _loc4 - _loc2;
	rect->left += _loc3;
	rect->left += _loc2;

	rect->right = rect->left + _loc4;
	rect->top += 1;

	*x = rect->left + _loc2;
	*y = rect->top;
}

//在状态栏显示文件编码
void SiStatusBar_ShowCodec(int codec)
{
	int x, y;
	RECT rect;
	HDC hdc = GetDC(hwnd_si_frame);
	HGDIOBJ hobj = GetStockObject(DEFAULT_GUI_FONT);
	SelectObject(hdc,hobj);
	SetBkColor(hdc,RGB(240,240,240));
	SetTextColor(hdc,RGB(0,0,0));
	
	//SI_GetRectXY(1, &rect, &x, &y);
	SiStatusBar_GetRectXY1(&rect, &x, &y);
	ExtTextOut(hdc,x,y,ETO_OPAQUE|ETO_CLIPPED,&rect,codec_name[codec],strlen(codec_name[codec]),NULL);
	ReleaseDC(hwnd_si_frame,hdc);
}
