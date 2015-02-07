/*
callproc.c - DLL Access Part for JsWin

JsWin - a JavaScript Framework for Win32 DLL Access
Designed by Morning Yellow, Version: 1.1, Last Modified: Nov. 2009
Copyright (C) 2004-2009 www.elephantbase.net

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <string.h>

#ifdef _WIN32

#include <windows.h>

__declspec(dllexport) VOID WINAPI CallProc(LPVOID lpProc, LPVOID lpParam, DWORD dwParamLen);
__declspec(dllexport) VOID WINAPI PrepareCallback(LPBYTE lpucCallbackMem, LPVOID lpCallback, LPVOID lpContext);

#else

#include <sys/mman.h>
#include <limits.h> // For PAGESIZE */
#ifndef PAGESIZE
  #define PAGESIZE 4096
#endif

#define WINAPI

typedef void VOID, *LPVOID;
typedef unsigned char BYTE, *LPBYTE;
typedef unsigned long DWORD, *LPDWORD;

#endif

VOID WINAPI CallProc(LPVOID lpProc, LPVOID lpParam, DWORD dwParamLen) {
#ifdef _MSC_VER
  __asm {
    mov   eax, lpProc;
    mov   edx, lpParam;
    mov   ecx, dwParamLen;
L_LOOP:
    jcxz  L_EXIT;
    sub   ecx, 4;
    push  [ecx+edx];
    jmp   L_LOOP;
L_EXIT:
    call  eax;
  }
#else
  asm __volatile__ (
    "1:" "\n\t"
    "jcxz  2f" "\n\t"
    "subl  $4, %%ecx" "\n\t"
    "pushl (%%ecx,%%edx)" "\n\t"
    "jmp   1b" "\n\t"
    "2:" "\n\t"
    "calll *%%eax" "\n\t"
    :
    : "a" (lpProc), "d" (lpParam), "c" (dwParamLen)
  );
#endif
}

#define CALLBACK_CONTEXT   9
#define CALLBACK_ADDRESS   14
#define CALLBACK_SIZE      32

// LPVOID WINAPI Callback(LPVOID lpContext, LPVOID lpParam);

static const unsigned char cucCallbackPattern[] = {
#ifdef _DEBUG
  0xCC,                         // int 3
#else
  0x90,                         // noop
#endif
  0x55,                         // push ebp
  0x8B, 0xEC,                   // mov esp, ebp
  0x8D, 0x45, 0x08,             // lea eax, [ebp+8]
  0x50,                         // push eax
  0x68, 0xCC, 0xCC, 0xCC, 0xCC, // push lpContext
  0xB8, 0xCC, 0xCC, 0xCC, 0xCC, // mov eax, lpCallback
  0xFF, 0xD0,                   // call eax
  0x8B, 0xE5,                   // mov ebp, esp
  0x5D,                         // pop ebp
  0xC3,                         // ret
  0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // Reserved
  0xCC, 0xCC, 0xCC              // Reserved
}; // 32 Bytes

VOID WINAPI PrepareCallback(LPBYTE lpucCallbackMem, LPVOID lpCallback, LPVOID lpContext) {
#ifdef _WIN32
  DWORD dwOldProtect;
  VirtualProtect(lpucCallbackMem, CALLBACK_SIZE, PAGE_EXECUTE_READWRITE, &dwOldProtect);
#else
  LPBYTE lpuc = (LPBYTE) ((int) lpucCallbackMem & ~(PAGESIZE - 1));
  mprotect(lpuc, lpucCallbackMem + CALLBACK_SIZE - lpuc, PROT_READ | PROT_WRITE | PROT_EXEC);
#endif
  memcpy(lpucCallbackMem, cucCallbackPattern, CALLBACK_SIZE);
  *(LPDWORD) (lpucCallbackMem + CALLBACK_CONTEXT) = (DWORD) lpContext;
  *(LPDWORD) (lpucCallbackMem + CALLBACK_ADDRESS) = (DWORD) lpCallback;
}
