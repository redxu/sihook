#ifndef __SIFRAME__H__
#define __SIFRAME__H__

#include <windows.h>

//获取窗口句柄
HWND GetSiFrameHwnd(void);

//替换窗口消息
void HookSiFrame(void);

#endif
