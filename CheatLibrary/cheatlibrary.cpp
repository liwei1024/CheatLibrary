#include "stdafx.h"
#include "cheatlibrary.h"

HWND hWnd = NULL;
DWORD dwProcessId = NULL;
HANDLE hProcess = NULL;

BOOL cheatLibraryInit(LPCSTR lpClassName, LPCSTR lpWindowName, BYTE caller)
{
	hWnd = FindWindow(lpClassName, lpWindowName);
	if (caller == NULL)
	{
		::GetWindowThreadProcessId(hWnd, &dwProcessId);
		hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, false, dwProcessId);
		if (hProcess)
		{
			debugPrint("ªÒ»° hProcess  ß∞‹");
			return false;
		}
	}
	return true;
}

VOID debugPrint(LPCSTR str)
{
	string newstr(str);
	newstr = "[LE]" + newstr;
	OutputDebugString(newstr.c_str());
}

BOOL readMemory(DWORD dwBaseAddress,LPVOID lpBuffer,SIZE_T nSize)
{
	if (hProcess != NULL)
	{
		SIZE_T lpNumberOfBytesRead;
		if (ReadProcessMemory(hProcess, (LPCVOID)dwBaseAddress, lpBuffer, nSize, &lpNumberOfBytesRead)) {
			return true;
		}
		else {
			debugPrint("readMemory  ß∞‹");
		}
	}
	else {
		__try {
			if (IsBadReadPtr((LPCVOID)dwBaseAddress, nSize) == 0)
			{
				memcpy(lpBuffer, (PVOID)dwBaseAddress, nSize);
				return true;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			char str[255] = { NULL };
			sprintf_s(str, "readMemory - exception code < %8x >\n", GetExceptionCode());
			debugPrint(str);
		}
	}
	return false;
}
INT readInteger(DWORD dwBaseAddress)
{
	INT buffer;
	if (readMemory(dwBaseAddress, &buffer, sizeof(buffer))) {
		return buffer;
	}
	else {
		return -1;
	}
}
FLOAT readFloat(DWORD dwBaseAddress)
{
	FLOAT buffer;
	if (readMemory(dwBaseAddress, &buffer, sizeof(buffer))) {
		return buffer;
	}
	else {
		return -1;
	}
}