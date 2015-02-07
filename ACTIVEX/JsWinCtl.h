#if !defined(AFX_JSWINCTL_H__FFD433A1_BFCF_4BA6_947F_67756786860C__INCLUDED_)
#define AFX_JSWINCTL_H__FFD433A1_BFCF_4BA6_947F_67756786860C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JsWinCtl.h : Declaration of the CJsWinCtrl ActiveX Control class.

#include <objsafe.h>

/////////////////////////////////////////////////////////////////////////////
// CJsWinCtrl : See JsWinCtl.cpp for implementation.

class CJsWinCtrl : public COleControl
{
	DECLARE_DYNCREATE(CJsWinCtrl)

// Constructor
public:
	BEGIN_INTERFACE_PART(ObjectSafety, IObjectSafety) 
		STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD __RPC_FAR *pdwSupportedOptions, DWORD __RPC_FAR *pdwEnabledOptions); 
		STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions); 
	END_INTERFACE_PART(ObjectSafety) 

	DECLARE_INTERFACE_MAP(); 

	CJsWinCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJsWinCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BOOL OnSetExtent(LPSIZEL lpSizeL);
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CJsWinCtrl();

	DECLARE_OLECREATE_EX(CJsWinCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CJsWinCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CJsWinCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CJsWinCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CJsWinCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CJsWinCtrl)
	afx_msg void MemCpy(long lpDst, long lpSrc, long dwCount);
	afx_msg long StrLen(long lpcstr);
	afx_msg long GetMem1(long lpuc);
	afx_msg long GetMem2(long lpw);
	afx_msg long GetMem4(long lpdw);
	afx_msg void PutMem1(long lpuc, long uc);
	afx_msg long PutMem2(long lpw, long w);
	afx_msg void PutMem4(long lpdw, long dw);
	afx_msg long Alloc(long dwSize);
	afx_msg void Free(long lp);
	afx_msg long LoadLibrary(LPCTSTR szLibFileName);
	afx_msg void FreeLibrary(long hMod);
	afx_msg long GetProcAddress(long hMod, long szProcName);
	afx_msg long CallProc(long lpProc, long lpParams, long dwParamNum);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CJsWinCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CJsWinCtrl)
	dispidFlip = 1L,
	dispidRestart = 2L,
	dispidMemCpy = 1L,
	dispidStrLen = 2L,
	dispidGetMem1 = 3L,
	dispidGetMem2 = 4L,
	dispidGetMem4 = 5L,
	dispidPutMem1 = 6L,
	dispidPutMem2 = 7L,
	dispidPutMem4 = 8L,
	dispidAlloc = 9L,
	dispidFree = 10L,
	dispidLoadLibrary = 11L,
	dispidFreeLibrary = 12L,
	dispidGetProcAddress = 13L,
	dispidCallProc = 14L,
	//}}AFX_DISP_ID
	};

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSWINCTL_H__FFD433A1_BFCF_4BA6_947F_67756786860C__INCLUDED)
