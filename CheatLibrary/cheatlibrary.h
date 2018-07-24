#pragma once
using namespace std;

extern HWND hWnd;
extern DWORD dwProcessId;
extern HANDLE hProcess;

BOOL cheatLibraryInit(LPCSTR lpClassName, LPCSTR lpWindowName, BYTE caller);

VOID debugPrint(LPCSTR str);

BOOL readMemory(DWORD dwBaseAddress, LPVOID lpBuffer, SIZE_T nSize);
INT readInteger(DWORD dwBaseAddress);
FLOAT readFloat(DWORD dwBaseAddress);
