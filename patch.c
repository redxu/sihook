#include <windows.h>
#include "utils.h"
#include "patch.h"


static void PatchCode(PBYTE addr,BYTE* patch,int size)
{
	DWORD OldProtect = 0;
	VirtualProtect(addr,size,PAGE_EXECUTE_READWRITE,&OldProtect);
	RtlCopyMemory(addr,patch,size);
	VirtualProtect(addr,size,OldProtect,&OldProtect);
	FlushInstructionCache((HANDLE)-1,addr,size);
}


//ÐÞ¸´SI Ctrl+FµÄbug
//reference:http://bbs.pediy.com/showthread.php?t=185736
int PatchSI(void)
{
	//004055E1      806405 F4 00  and     byte ptr [ebp+eax-0xC], 0x0
	BYTE TARGET[5] = {0x80,0x64,0x05,0xF4,0x00};
	BYTE PATCH[5] = {0x90,0x90,0x90,0x90,0x90};
	PBYTE exemod = GetModuleHandle(NULL);
	PBYTE address = exemod;
	PBYTE start;
	MEMORY_BASIC_INFORMATION mbi;
	
	while(TRUE)
	{
		if(VirtualQueryEx(GetCurrentProcess(),address,&mbi,sizeof(mbi)) != sizeof(mbi))
		{
			break;
		}
		if(mbi.AllocationBase != exemod)
		{
			break;
		}
		if((mbi.Protect&PAGE_EXECUTE_READ) && (mbi.State == MEM_COMMIT))
		{	
			for(start = mbi.BaseAddress;start < mbi.BaseAddress+mbi.RegionSize-5;start++)
			{
				if(memcmp(start,TARGET,sizeof(TARGET)) == 0)
				{
					OutputDebugStringEx("BaseAddress[%08x] RegionSize[%08x]",mbi.BaseAddress,mbi.RegionSize);
					OutputDebugStringEx("Find Patch Address %08x",start);
					PatchCode(start,PATCH,sizeof(PATCH));
					return 0;
				}
				
			}
		}
		address = ((PBYTE)mbi.BaseAddress+mbi.RegionSize);
	}
	
	return -1;
}
