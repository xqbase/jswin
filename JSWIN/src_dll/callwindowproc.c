typedef int (*WNDPROC)(int, int, int, int);

int CallWindowProc(WNDPROC lpProc, int hWnd, int uMsg, int wParam, int lParam) {
  return lpProc(hWnd, uMsg, wParam, lParam);
}
