#include <windows.h>
#include "siframe.h"
#include "mdiclient.h"
#include "patch.h"

HWND hwnd_si_frame = NULL;
HWND hwnd_mdi_client = NULL;
HWND hwnd_tab_ctl = NULL;

void HookSI(void)
{
	//hook si_frame
	hwnd_si_frame = GetSiFrameHwnd();
	if(hwnd_si_frame == NULL)
	{
		OutputDebugString("GetSiFrameHwnd=NULL");
		ExitProcess(-1);
	}
    HookSiFrame();

    //hook MDIClient
    hwnd_mdi_client = GetMdiClientHwnd(hwnd_si_frame);
    if(hwnd_mdi_client == NULL)
    {
		OutputDebugString("GetMdiClientHwnd=NULL");
		ExitProcess(-1);
    }
	HookMdiClient();

	//Path SI
	if(PatchSI() == 0)
	{
		OutputDebugString("PatchSI Success!");
	}
	else 
	{
		OutputDebugString("PatchSI Failed!");
	}
	
	//hook apis
	//HookWinApi();
}

void UnhookSI(void)
{
};

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            HookSI();
            break;

        case DLL_PROCESS_DETACH:
            UnhookSI();
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE; // succesful
}
