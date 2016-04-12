#ifndef __UTILS__H__
#define __UTILS__H__

#include <windows.h>

//输出调试信息
void WINAPI OutputDebugStringEx(LPCTSTR lpcFormatText, ...);

//获取短标题
char* GetSiSwTitle(const char* lpc,char* title);

//获取文件类型
//0 无类型默认
//1 *.c *.cpp *.cxx *.cs
//2 *.h *.hpp *.hxx *.inc
//3 *.txt *.text *.doc
//4 *.php *.php3 *.htm *.js
//5 *.pas *.vb *.pb *.vbs
int GetColorIndex(const char* filename);

/**
 * 检查是否加载了siutf8插件
 * @return  [0-未加载 1-已加载]
 */
int CheckUtf8Loaded(void);

typedef int (* GetU8FlagFn)(char *);

#endif
