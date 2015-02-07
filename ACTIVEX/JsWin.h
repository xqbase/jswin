#if !defined(AFX_JSWIN_H__4D005BE9_24CB_4363_B929_FBF170605863__INCLUDED_)
#define AFX_JSWIN_H__4D005BE9_24CB_4363_B929_FBF170605863__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JsWin.h : main header file for JSWIN.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CJsWinApp : See JsWin.cpp for implementation.

class CJsWinApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSWIN_H__4D005BE9_24CB_4363_B929_FBF170605863__INCLUDED)
