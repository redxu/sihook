#ifndef __TABCTL__H__
#define __TABCTL__H__

#include <windows.h>
#include <commctrl.h>
#include <wingdi.h>
#include <stdio.h>

//创建TabCtl
void SiTabCtl_Create(HWND parent);
//获取页个数
int SiTabCtl_GetItemCount(void);
//获取行数
int SiTabCtl_GetRowCount(void);
//获取高度
int SiTabCtl_GetHeight(void);
//添加Item
void SiTabCtl_AddItem(char* title,HWND hwnd);
//查找item
int SiTabCtl_FindItem(HWND hwnd);
//删除Item
void SiTabCtl_DelItem(HWND hwnd);
//关闭标签页
void SiTabCtl_CloseItem(int idx);
//设置Item文字
void SiTabCtl_SetItemText(HWND hwnd,char* text);
//选中Item
void SiTabCtl_SetCurItem(HWND hwnd);
//获取当前Item
int SiTabCtl_GetCurItem(void);
//获取鼠标所在Item
int SiTabCtl_GetCursorItem(void);
//判断是否行数改变
BOOL SiTabCtl_IsRowChanged(void);
//位置改变
void SiTabCtl_OnPosChanging(WINDOWPOS* pos);
//选项卡改变
void SiTabCtl_OnSelChange(void);
//双击选项卡
void SiTabCtl_OnLButtonDblClk(void);
//右键单击选项卡
void SiTabCtl_OnRButtonClk(void);
//左键单击选项卡
void SiTabCtl_OnLButtonClk(void);
//重绘选项卡
void SiTabCtl_OnDrawItem(DRAWITEMSTRUCT* item);

#endif

