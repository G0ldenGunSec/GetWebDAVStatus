#include <windows.h>
#include <stdio.h>
#include "beacon.h"

WINBASEAPI BOOL WINAPI KERNEL32$WaitNamedPipeW(LPCWSTR lpNamedPipeName, DWORD nTimeOut);
WINBASEAPI void* WINAPI MSVCRT$malloc(size_t);
WINBASEAPI size_t WINAPI MSVCRT$wcslen(const wchar_t* str);
WINBASEAPI wchar_t* WINAPI MSVCRT$wcscpy(wchar_t* dest, const wchar_t* source);
WINBASEAPI wchar_t* WINAPI MSVCRT$wcscat(wchar_t* dest, const wchar_t* source);
WINBASEAPI void WINAPI MSVCRT$free(void*);

void go(char* args, int length) 
{
    wchar_t* host;
    datap parser;
    BeaconDataParse(&parser, args, length);
    host = (wchar_t*)BeaconDataExtract(&parser, NULL);
    //BeaconPrintf(CALLBACK_OUTPUT, "Value of host: %S", host);
    
    wchar_t* pipeNameHead = L"\\\\";
    wchar_t* pipeNameTail = L"\\pipe\\DAV RPC SERVICE";
    BOOL pipeStatus = 0;

    wchar_t* fullPipeName = (wchar_t*)MSVCRT$malloc((MSVCRT$wcslen(host) + MSVCRT$wcslen(pipeNameHead) + MSVCRT$wcslen(pipeNameTail) + 1) * sizeof(wchar_t));
    MSVCRT$wcscpy(fullPipeName, pipeNameHead);
    MSVCRT$wcscat(fullPipeName, host);
    MSVCRT$wcscat(fullPipeName, pipeNameTail);

    pipeStatus = KERNEL32$WaitNamedPipeW(fullPipeName, 3000);
    if (pipeStatus == 0)
    {
        BeaconPrintf(CALLBACK_ERROR, "[x] Unable to hit DAV pipe on %S, system is either unreachable or does not have WebClient service running", host);
    }
    else
    {
        BeaconPrintf(CALLBACK_OUTPUT, "[+] WebClient service is active on %S", host);
    }
    MSVCRT$free((void*)fullPipeName);
}
