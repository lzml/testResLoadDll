// xDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "xDll.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}



// This is an example of an exported function.
extern "C" XDLL_API int PopCurrentProcPath(void)
{
	char szPath[MAX_PATH]={0};
	GetModuleFileName(NULL,szPath,MAX_PATH);
	MessageBox(NULL,szPath,"当前进程路径",MB_OK);
	return 42;
}

