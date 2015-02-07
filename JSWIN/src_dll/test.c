#include <stdio.h>

#define CALLBACK_SIZE 32

#ifdef _WIN32

#include <windows.h>

DWORD WINAPI CallProc(LPVOID lpProc, LPVOID lpParams, DWORD dwParamLen);
VOID WINAPI PrepareCallback(LPBYTE lpucCallbackMem, LPVOID lpCallback, LPVOID lpContext);

DWORD WINAPI GenericCallback(DWORD dwContext, DWORD *lpdwParam) {
  return dwContext + lpdwParam[0] + lpdwParam[1] + lpdwParam[2] + lpdwParam[3];
}

void main(void) {
  BYTE ucCallbackMem[CALLBACK_SIZE];
  DWORD dwParams[5];
  PrepareCallback((LPVOID) ucCallbackMem, (LPVOID) GenericCallback, (LPVOID) 5);
  dwParams[0] = (DWORD) ucCallbackMem;
  dwParams[1] = 1;
  dwParams[2] = 2;
  dwParams[3] = 3;
  dwParams[4] = 4;
  printf("%d\n", CallProc((LPVOID) CallWindowProc, dwParams, 20));
}

#else

#include <dlfcn.h>
#include <sys/mman.h>

int CallProc(void *lpProc, void *lpParams, int dwParamLen);
void PrepareCallback(unsigned char *lpucCallbackMem, void *lpCallback, void *lpContext);

typedef int (*CALL_WINDOW_PROC)(int, int, int, int, int);
typedef int (*CALL_PROC)(void *, void *, int);
typedef void (*PREPARE_CALLBACK)(unsigned char *, void *, void *);

static int GenericCallback(int dwContext, int *lpdwParam) {
  return dwContext + lpdwParam[0] + lpdwParam[1] + lpdwParam[2] + lpdwParam[3];
}

int main(void) {
  void *hModule = dlopen("./libcallwindowproc.so", RTLD_LAZY);
  if (hModule == NULL) {
    return 0;
  }
  CALL_WINDOW_PROC CallWindowProc = (CALL_WINDOW_PROC)  dlsym(hModule, "CallWindowProc");
  unsigned char ucCallbackMem[CALLBACK_SIZE];
  PrepareCallback(ucCallbackMem, (void *) GenericCallback, (void *) 5);
  int dwParams[5];
  dwParams[0] = (int) ucCallbackMem;
  dwParams[1] = 1;
  dwParams[2] = 2;
  dwParams[3] = 3;
  dwParams[4] = 4;
  printf("%d\n", CallProc((void *) CallWindowProc, dwParams, 20));
  dlclose(hModule);
  return 0;
}

#endif
