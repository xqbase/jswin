#include <string.h>
#include <wchar.h>
#include "callproc.h"

#ifdef _WIN32

#include <windows.h>

#else

#include <dlfcn.h>
#include <sys/mman.h>
#include <limits.h> // For PAGESIZE */
#ifndef PAGESIZE
  #define PAGESIZE 4096
#endif

#endif

static JavaVM *vm = NULL;
static jmethodID callbackMethod;

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_initCallback
    (JNIEnv *env, jclass clazz) {
  env->GetJavaVM(&vm);
  jclass callbackClass = env->FindClass("com/googlecode/jswin/Callback");
  callbackMethod = env->GetMethodID(callbackClass, "callback", "(I)I");
}

JNIEXPORT jint JNICALL Java_com_googlecode_jswin_CallProc_newRef
    (JNIEnv *env, jclass clazz, jobject o) {
  return (jint) env->NewGlobalRef(o);
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_delRef
    (JNIEnv *env, jclass clazz, jint ref) {
  env->DeleteGlobalRef((jobject) ref);
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_memcpy
    (JNIEnv *env, jclass clazz, jint lpDst, jint lpSrc, jint dwCount) {
  memcpy((void *) lpDst, (void *) lpSrc, dwCount);
}

JNIEXPORT jint JNICALL Java_com_googlecode_jswin_CallProc_strlen
    (JNIEnv *env, jclass clazz, jint lpcstr) {
  return (jint) strlen((const char *) lpcstr);
}

JNIEXPORT jbyte JNICALL Java_com_googlecode_jswin_CallProc_getMem1
    (JNIEnv *env, jclass clazz, jint lpuc) {
  return *(jbyte *) lpuc;
}

JNIEXPORT jshort JNICALL Java_com_googlecode_jswin_CallProc_getMem2
    (JNIEnv *env, jclass clazz, jint lpw) {
  return *(jshort *) lpw;
}

JNIEXPORT jint JNICALL Java_com_googlecode_jswin_CallProc_getMem4
    (JNIEnv *env, jclass clazz, jint lpdw) {
  return *(jint *) lpdw;
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_getByteArray
    (JNIEnv *env, jclass clazz, jint lpucSrc, jbyteArray dest, jint destPos, jint length) {
  env->SetByteArrayRegion(dest, destPos, length, (jbyte *) lpucSrc);
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_getShortArray
    (JNIEnv *env, jclass clazz, jint lpwSrc, jshortArray dest, jint destPos, jint length) {
  env->SetShortArrayRegion(dest, destPos, length, (jshort *) lpwSrc);
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_getIntArray
    (JNIEnv *env, jclass clazz, jint lpdwSrc, jintArray dest, jint destPos, jint length) {
  env->SetIntArrayRegion(dest, destPos, length, (jint *) lpdwSrc);
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_putMem1
    (JNIEnv *env, jclass clazz, jint lpuc, jbyte uc) {
  *(jbyte *) lpuc = uc;
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_putMem2
    (JNIEnv *env, jclass clazz, jint lpw, jshort w) {
  *(jshort *) lpw = w;
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_putMem4
    (JNIEnv *env, jclass clazz, jint lpdw, jint dw) {
  *(jint *) lpdw = dw;
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_putByteArray
    (JNIEnv *env, jclass clazz, jint lpucDest, jbyteArray src, jint srcPos, jint length) {
  env->GetByteArrayRegion(src, srcPos, length, (jbyte *) lpucDest);
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_putShortArray
    (JNIEnv *env, jclass clazz, jint lpwDest, jshortArray src, jint srcPos, jint length) {
  env->GetShortArrayRegion(src, srcPos, length, (jshort *) lpwDest);
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_putIntArray
    (JNIEnv *env, jclass clazz, jint lpdwDest, jintArray src, jint srcPos, jint length) {
  env->GetIntArrayRegion(src, srcPos, length, (jint *) lpdwDest);
}

JNIEXPORT jint JNICALL Java_com_googlecode_jswin_CallProc_alloc
    (JNIEnv *env, jclass clazz, jint size) {
  return (jint) new char[size];
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_free
    (JNIEnv *env, jclass clazz, jint lp) {
  delete[] (char *) lp;
}

JNIEXPORT jint JNICALL Java_com_googlecode_jswin_CallProc_loadLibrary
    (JNIEnv *env, jclass clazz, jbyteArray libFileName) {
  jint length = env->GetArrayLength(libFileName);
  char *szLibFileName = new char[length + 1];
  env->GetByteArrayRegion(libFileName, 0, length, (jbyte *) szLibFileName);
  szLibFileName[length] = '\0';
#ifdef _WIN32
  jint hMod = (jint) LoadLibrary(szLibFileName);
#else
  jint hMod = (jint) dlopen(szLibFileName, RTLD_LAZY);
#endif
  delete[] szLibFileName;
  return hMod;
}

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_freeLibrary
    (JNIEnv *env, jclass clazz, jint hMod) {
#ifdef _WIN32
  FreeLibrary((HMODULE) hMod);
#else
  dlclose((void *) hMod);
#endif
}

JNIEXPORT jint JNICALL Java_com_googlecode_jswin_CallProc_getProcAddress
    (JNIEnv *env, jclass clazz, jint hMod, jbyteArray procName) {
  jint length = env->GetArrayLength(procName);
  char *szProcName = new char[length + 1];
  env->GetByteArrayRegion(procName, 0, length, (jbyte *) szProcName);
  szProcName[length] = '\0';
#ifdef _WIN32
  jint lpProc = (jint) GetProcAddress((HMODULE) hMod, szProcName);
#else
  jint lpProc = (jint) dlsym((void *) hMod, szProcName);
#endif
  delete[] szProcName;
  return lpProc;
}

JNIEXPORT jint JNICALL Java_com_googlecode_jswin_CallProc_callProc
    (JNIEnv *env, jclass clazz, jint lpProc, jintArray params) {
  jint dwParamLen = env->GetArrayLength(params) * sizeof(jint);
  jint *lpParam = env->GetIntArrayElements(params, NULL);
  jint dwReturn;
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
    mov   dwReturn, eax;
  }
#else
  jint edx, ecx;
  asm __volatile__ (
    "1:" "\n\t"
    "jcxz  2f" "\n\t"
    "subl  $4, %%ecx" "\n\t"
    "pushl (%%ecx,%%edx)" "\n\t"
    "jmp   1b" "\n\t"
    "2:" "\n\t"
    "calll *%%eax" "\n\t"
    : "=a" (dwReturn), "=d" (edx), "=c" (ecx)
    : "a" (lpProc), "d" (lpParam), "c" (dwParamLen)
  );
#endif
  env->ReleaseIntArrayElements(params, lpParam, JNI_ABORT);
  return dwReturn;
}

const int CALLBACK_CONTEXT      = 9;
const int CALLBACK_ADDRESS      = 14;
const int CALLBACK_SIZE         = 32;

static jint GenericCallback(jobject lpContext, jint lpParam) {
  JNIEnv *env;
  vm->AttachCurrentThread((void **) &env, NULL);
  jint ret = env->CallIntMethod(lpContext, callbackMethod, lpParam);
  vm->DetachCurrentThread();
  return ret;
}

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

JNIEXPORT void JNICALL Java_com_googlecode_jswin_CallProc_prepareCallback
    (JNIEnv *env, jclass clazz, jint lpucCallbackMem, jint lpContext) {
#ifdef _WIN32
  DWORD dwOldProtect;
  VirtualProtect((LPVOID) lpucCallbackMem, CALLBACK_SIZE, PAGE_EXECUTE_READWRITE, &dwOldProtect);
#else
  jint lpuc = lpucCallbackMem & ~(PAGESIZE - 1);
  mprotect((void *) lpuc, lpucCallbackMem + CALLBACK_SIZE - lpuc, PROT_READ | PROT_WRITE | PROT_EXEC);
#endif
  memcpy((void *) lpucCallbackMem, cucCallbackPattern, CALLBACK_SIZE);
  *(jint *) (lpucCallbackMem + CALLBACK_CONTEXT) = lpContext;
  *(jint *) (lpucCallbackMem + CALLBACK_ADDRESS) = (jint) GenericCallback;
}
