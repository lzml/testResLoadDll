
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the XDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// XDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef XDLL_EXPORTS
#define XDLL_API __declspec(dllexport)
#else
#define XDLL_API __declspec(dllimport)
#endif

// This class is exported from the xDll.dll

extern "C" XDLL_API int PopCurrentProcPath(void);

