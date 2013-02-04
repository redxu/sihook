#ifndef __MDICLIENT__H__
#define __MDICLIENT__H__

#include <windows.h>

//获取窗口句柄
HWND GetMdiClientHwnd(HWND parent);

//重新调整窗口大小
void ResizeMdiClient(void);

//替换窗口消息
void HookMdiClient(void);

#endif
