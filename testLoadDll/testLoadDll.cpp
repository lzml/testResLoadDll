// testLoadDll.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <stdio.h>
#include "MemoryModule.h"
#include "resource.h"

typedef int (WINAPI *PFN_POPMSGBOX)(void);
 
void LoadDllFromMemAndCall();

int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	LoadDllFromMemAndCall();
	printf("Finished!\n");
	return 0;
}

void LoadDllFromMemAndCall()
{
	HRSRC hResInfo;
	HGLOBAL hResData;
	DWORD dwSize;
	PVOID DllResourceModule=NULL;
	HMEMORYMODULE hDll;
	PFN_POPMSGBOX pfn;
	hResInfo = FindResource(NULL,MAKEINTRESOURCE(IDR_MYDLL), "MYDLL");
	if (hResInfo == NULL) 
	{
		printf("无法找到指定的资源!\n");
		return ;
	}
	dwSize = SizeofResource(NULL, hResInfo);
	// 装载资源
	hResData = LoadResource(NULL, hResInfo);
	if (hResData == NULL) 
	{
		printf("无法加载指定的资源!\n");
		return ;
	}
	//锁定资源，并获取指向资源的指针
	DllResourceModule=LockResource(hResData);
	// 加载
	hDll=MemoryLoadLibrary(DllResourceModule);
	if (hDll==NULL)
	{
		printf("从内存直接加载Dll失败!\n");
		return ;
	}
	//获取导出的函数的地址
	pfn=MemoryGetProcAddress(hDll,"PopCurrentProcPath");
	if (pfn==NULL)
	{
		printf("无法获取指定的函数地址！\n");
		MemoryFreeLibrary(hDll);
		return;
	}
	//调用导出的函数
	pfn();
	//printf("调用结束!\n");
	if (hDll!=NULL)
	{
		MemoryFreeLibrary(hDll);
		hDll=NULL;
	}
}