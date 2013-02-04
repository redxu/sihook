#include <windows.h>

static HMODULE m_hModule = NULL;	// 原始模块句柄
static DWORD m_dwReturn[5] = {0};	// 原始函数返回地址

// 加载原始模块
static inline BOOL WINAPI Load()
{
    TCHAR tzPath[MAX_PATH];
    TCHAR tzTemp[MAX_PATH * 2];

    GetSystemDirectory(tzPath, MAX_PATH);
    lstrcat(tzPath, TEXT("\\msimg32"));
    m_hModule = LoadLibrary(tzPath);
    if (m_hModule == NULL)
    {
        wsprintf(tzTemp, TEXT("无法加载 %s，程序无法正常运行。"), tzPath);
        OutputDebugString(tzTemp);
        ExitProcess(-2);
    }
    else OutputDebugString("引导msimg32");
    return (m_hModule != NULL);
}

// 释放原始模块
static inline VOID WINAPI Free()
{
    if (m_hModule)
    {
        FreeLibrary(m_hModule);
    }
}

// 获取原始函数地址
static FARPROC WINAPI GetAddress(PCSTR pszProcName)
{
    FARPROC fpAddress;
    CHAR szProcName[16];
    TCHAR tzTemp[MAX_PATH];

    fpAddress = GetProcAddress(m_hModule, pszProcName);
    if (fpAddress == NULL)
    {
        if (HIWORD(pszProcName) == 0)
        {
            wsprintfA(szProcName, "%d", pszProcName);
            pszProcName = szProcName;
        }

        wsprintf(tzTemp, TEXT("无法找到函数 %s，程序无法正常运行。"), pszProcName);
        OutputDebugString(tzTemp);
        ExitProcess(-2);
    }

    return fpAddress;
}


BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        Load();

        HMODULE hMyDLL = LoadLibrary("sihook.dll");
        if (hMyDLL == NULL)
            OutputDebugString("加载sihook.dll失败");
        else
            OutputDebugString("加载sihook.dll成功");
        return TRUE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        Free();
    }
    return TRUE;
}

typedef void (__cdecl *RemoteFunc)(void);

void __cdecl vSetDdrawflag(void)
{
    RemoteFunc func = (RemoteFunc)GetAddress("vSetDdrawflag");
    func();
}
void __cdecl AlphaBlend(void)
{
    RemoteFunc func = (RemoteFunc)GetAddress("AlphaBlend");
    func();
}
void __cdecl DllInitialize(void)
{
    RemoteFunc func = (RemoteFunc)GetAddress("DllInitialize");
    func();
}
void __cdecl GradientFill(void)
{
    RemoteFunc func = (RemoteFunc)GetAddress("GradientFill");
    func();
}
void __cdecl TransparentBlt(void)
{
    RemoteFunc func = (RemoteFunc)GetAddress("TransparentBlt");
    func();
}
