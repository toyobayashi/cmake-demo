#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <delayimp.h>
#include <string.h>
#include <stdio.h>
#include "../../../include/main.h"

static FARPROC WINAPI load_exe_hook(unsigned event, PDelayLoadInfo info) {
  if (event == dliStartProcessing) {
    printf("mainLoad: %s\n", "dliStartProcessing");
  } else if (event == dliNotePreLoadLibrary) {
    printf("mainLoad: %s\n", "dliNotePreLoadLibrary");
    printf("mainLoad: %s\n", info->szDll);
    if (stricmp(info->szDll, "main.exe") != 0) {
      return NULL;
    }
    return (FARPROC) GetModuleHandle(NULL);
  } else if (event == dliNotePreGetProcAddress) {
    printf("mainLoad: %s\n", "dliNotePreGetProcAddress");
    printf("mainLoad: %s\n", info->dlp.szProcName);
  } else if (event == dliNoteEndProcessing) {
    printf("mainLoad: %s\n", "dliNoteEndProcessing");
  }
  return NULL;
}

const PfnDliHook __pfnDliNotifyHook2 = load_exe_hook;

void __declspec(dllexport) call_main_export(int a, int b);
void call_main_export(int a, int b) {
  int result = add(a, b);
  printf("exe add result: %d", result);
}

#endif
