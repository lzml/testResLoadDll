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
		printf("�޷��ҵ�ָ������Դ!\n");
		return ;
	}
	dwSize = SizeofResource(NULL, hResInfo);
	// װ����Դ
	hResData = LoadResource(NULL, hResInfo);
	if (hResData == NULL) 
	{
		printf("�޷�����ָ������Դ!\n");
		return ;
	}
	//������Դ������ȡָ����Դ��ָ��
	DllResourceModule=LockResource(hResData);
	// ����
	hDll=MemoryLoadLibrary(DllResourceModule);
	if (hDll==NULL)
	{
		printf("���ڴ�ֱ�Ӽ���Dllʧ��!\n");
		return ;
	}
	//��ȡ�����ĺ����ĵ�ַ
	pfn=MemoryGetProcAddress(hDll,"PopCurrentProcPath");
	if (pfn==NULL)
	{
		printf("�޷���ȡָ���ĺ�����ַ��\n");
		MemoryFreeLibrary(hDll);
		return;
	}
	//���õ����ĺ���
	pfn();
	//printf("���ý���!\n");
	if (hDll!=NULL)
	{
		MemoryFreeLibrary(hDll);
		hDll=NULL;
	}
}