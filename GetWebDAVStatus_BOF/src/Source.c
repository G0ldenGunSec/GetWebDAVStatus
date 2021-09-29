#include <windows.h>
#include <stdio.h>
#include "beacon.h"

WINBASEAPI BOOL WINAPI KERNEL32$WaitNamedPipeA(LPCSTR lpNamedPipeName, DWORD nTimeOut);
WINBASEAPI void* WINAPI MSVCRT$malloc(SIZE_T);
WINBASEAPI SIZE_T WINAPI MSVCRT$strlen(const char* str);
WINBASEAPI void* WINAPI MSVCRT$strcpy(const char* dest, const char* source);
WINBASEAPI void* WINAPI MSVCRT$strcat(const char* dest, const char* source);
WINBASEAPI void* WINAPI MSVCRT$strtok(char* str, const char* delim);
WINBASEAPI void* WINAPI MSVCRT$free(void*);

void go(char* args, int length) 
{
	char* pipeNameHead = "\\\\";
	char* pipeNameTail = "\\pipe\\DAV RPC SERVICE";
	BOOL pipeStatus = 0;
	char* singleHost = MSVCRT$strtok(args, ",");

	while (singleHost != NULL)
	{
		char* fullPipeName = MSVCRT$malloc(MSVCRT$strlen(singleHost) + MSVCRT$strlen(pipeNameHead) + MSVCRT$strlen(pipeNameTail) + 1);
		MSVCRT$strcpy(fullPipeName, pipeNameHead);
		MSVCRT$strcat(fullPipeName, singleHost);
		MSVCRT$strcat(fullPipeName, pipeNameTail);
		pipeStatus = KERNEL32$WaitNamedPipeA(fullPipeName, 3000);
		if (pipeStatus == 0)
		{
			BeaconPrintf(CALLBACK_OUTPUT, "[x] Unable to hit DAV pipe on %s, system is either unreachable or does not have WebClient service running", singleHost);
		}
		else
		{
			BeaconPrintf(CALLBACK_OUTPUT, "[+] WebClient service is active on %s", singleHost);
		}
		MSVCRT$free((void*)fullPipeName);
		singleHost = MSVCRT$strtok(NULL, ",");
	}
}