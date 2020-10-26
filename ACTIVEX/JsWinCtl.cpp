// JsWinCtl.cpp : Implementation of the CJsWinCtrl ActiveX Control class.

#include "stdafx.h"
#include "JsWin.h"
#include "JsWinCtl.h"
#include "JsWinPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CJsWinCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CJsWinCtrl, COleControl)
	//{{AFX_MSG_MAP(CJsWinCtrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CJsWinCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CJsWinCtrl)
	DISP_FUNCTION(CJsWinCtrl, "MemCpy", MemCpy, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "StrLen", StrLen, VT_I4, VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "GetMem1", GetMem1, VT_I4, VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "GetMem2", GetMem2, VT_I4, VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "GetMem4", GetMem4, VT_I4, VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "PutMem1", PutMem1, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "PutMem2", PutMem2, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "PutMem4", PutMem4, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "Alloc", Alloc, VT_I4, VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "Free", Free, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "LoadLibrary", LoadLibrary, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CJsWinCtrl, "FreeLibrary", FreeLibrary, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "GetProcAddress", GetProcAddress, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION(CJsWinCtrl, "CallProc", CallProc, VT_I4, VTS_I4 VTS_I4 VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CJsWinCtrl, COleControl)
	//{{AFX_EVENT_MAP(CJsWinCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CJsWinCtrl, 1)
	PROPPAGEID(CJsWinPropPage::guid)
END_PROPPAGEIDS(CJsWinCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CJsWinCtrl, "JSWIN.JsWinCtrl.1",
	0x560d4dc2, 0x6730, 0x49f8, 0xb4, 0x7b, 0x5b, 0x67, 0xc3, 0xf1, 0xb1, 0xa8)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CJsWinCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DJsWin =
		{ 0x3c3335f5, 0x6c1c, 0x4e1a, { 0x82, 0x19, 0x94, 0xb7, 0x13, 0x44, 0x6d, 0xb7 } };
const IID BASED_CODE IID_DJsWinEvents =
		{ 0x7a796794, 0x4ffd, 0x4e79, { 0x84, 0xa0, 0xac, 0x5b, 0xb7, 0x32, 0x74, 0x6d } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwJsWinOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CJsWinCtrl, IDS_JSWIN, _dwJsWinOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CJsWinCtrl::CJsWinCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CJsWinCtrl

BOOL CJsWinCtrl::CJsWinCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_JSWIN,
			IDB_JSWIN,
			afxRegApartmentThreading,
			_dwJsWinOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

/////////////////////////////////////////////////////////////////////////////
// CJsWinCtrl::~CJsWinCtrl - Destructor

CJsWinCtrl::~CJsWinCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CJsWinCtrl::OnDraw - Drawing function

void CJsWinCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	// pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	// pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CJsWinCtrl::DoPropExchange - Persistence support

void CJsWinCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CJsWinCtrl::OnResetState - Reset control to default state

void CJsWinCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}

/////////////////////////////////////////////////////////////////////////////
// CJsWinCtrl::CJsWinCtrl - Constructor

CJsWinCtrl::CJsWinCtrl()
{
	InitializeIIDs(&IID_DJsWin, &IID_DJsWinEvents);

	// TODO: Initialize your control's instance data here.
    SetInitialSize(1, 1);
}

void CJsWinCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	COleControl::OnLButtonDown(nFlags, point);
}

BOOL CJsWinCtrl::OnSetExtent(LPSIZEL lpSizeL) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// return COleControl::OnSetExtent(lpSizeL);
	return FALSE;
}

/* === Security Codes Below === */

BEGIN_INTERFACE_MAP(CJsWinCtrl, COleControl) 
	INTERFACE_PART(CJsWinCtrl, IID_IObjectSafety, ObjectSafety) 
END_INTERFACE_MAP() 

// Implementation of IObjectSafety 
STDMETHODIMP CJsWinCtrl::XObjectSafety::GetInterfaceSafetyOptions( 
			REFIID riid,  
			DWORD __RPC_FAR *pdwSupportedOptions,  
			DWORD __RPC_FAR *pdwEnabledOptions) 
{ 
	METHOD_PROLOGUE_EX(CJsWinCtrl, ObjectSafety) 

	if (!pdwSupportedOptions || !pdwEnabledOptions) 
	{ 
		return E_POINTER; 
	} 

	*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA; 
	*pdwEnabledOptions = 0; 

	if (NULL == pThis->GetInterface(&riid)) 
	{ 
		TRACE("Requested interface is not supported.\n"); 
		return E_NOINTERFACE; 
	} 

	// What interface is being checked out anyhow? 
	OLECHAR szGUID[39]; 
	int i = StringFromGUID2(riid, szGUID, 39); 

	if (riid == IID_IDispatch) 
	{ 
		// Client wants to know if object is safe for scripting 
		*pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER; 
		return S_OK; 
	} 
	else if (riid == IID_IPersistPropertyBag  
		  || riid == IID_IPersistStreamInit 
		  || riid == IID_IPersistStorage 
		  || riid == IID_IPersistMemory) 
	{ 
		// Those are the persistence interfaces COleControl derived controls support 
		// as indicated in AFXCTL.H 
		// Client wants to know if object is safe for initializing from persistent data 
		*pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA; 
		return S_OK; 
	} 
	else 
	{ 
		// Find out what interface this is, and decide what options to enable 
		TRACE("We didn¡¯t account for the safety of this interface, and it¡¯s one we support...\n"); 
		return E_NOINTERFACE; 
	} 
} 

STDMETHODIMP CJsWinCtrl::XObjectSafety::SetInterfaceSafetyOptions( 
		REFIID riid,  
		DWORD dwOptionSetMask,  
		DWORD dwEnabledOptions) 
{ 
	METHOD_PROLOGUE_EX(CJsWinCtrl, ObjectSafety) 

	OLECHAR szGUID[39]; 
	// What is this interface anyway? 
	// We can do a quick lookup in the registry under HKEY_CLASSES_ROOT\Interface 
	int i = StringFromGUID2(riid, szGUID, 39); 

	if (0 == dwOptionSetMask && 0 == dwEnabledOptions) 
	{ 
		// the control certainly supports NO requests through the specified interface 
		// so it¡¯s safe to return S_OK even if the interface isn¡¯t supported. 
		return S_OK; 
	} 

	// Do we support the specified interface? 
	if (NULL == pThis->GetInterface(&riid)) 
	{ 
		TRACE1("%s is not support.\n", szGUID); 
		return E_FAIL; 
	} 


	if (riid == IID_IDispatch) 
	{ 
		TRACE("Client asking if it¡¯s safe to call through IDispatch.\n"); 
		TRACE("In other words, is the control safe for scripting?\n"); 
		if (INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwOptionSetMask && INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwEnabledOptions) 
		{ 
			return S_OK; 
		} 
		else 
		{ 
			return E_FAIL; 
		} 
	} 
	else if (riid == IID_IPersistPropertyBag  
		  || riid == IID_IPersistStreamInit 
		  || riid == IID_IPersistStorage 
		  || riid == IID_IPersistMemory) 
	{ 
		TRACE("Client asking if it¡¯s safe to call through IPersist*.\n"); 
		TRACE("In other words, is the control safe for initializing from persistent data?\n"); 

		if (INTERFACESAFE_FOR_UNTRUSTED_DATA == dwOptionSetMask && INTERFACESAFE_FOR_UNTRUSTED_DATA == dwEnabledOptions) 
		{ 
			return NOERROR; 
		} 
		else 
		{ 
			return E_FAIL; 
		} 
	} 
	else 
	{ 
		TRACE1("We didn¡¯t account for the safety of %s, and it¡¯s one we support...\n", szGUID); 
		return E_FAIL; 
	} 
} 

STDMETHODIMP_(ULONG) CJsWinCtrl::XObjectSafety::AddRef() 
{ 
	METHOD_PROLOGUE_EX_(CJsWinCtrl, ObjectSafety) 
	return (ULONG)pThis->ExternalAddRef(); 
} 

STDMETHODIMP_(ULONG) CJsWinCtrl::XObjectSafety::Release() 
{ 
	METHOD_PROLOGUE_EX_(CJsWinCtrl, ObjectSafety) 
	return (ULONG)pThis->ExternalRelease(); 
} 

STDMETHODIMP CJsWinCtrl::XObjectSafety::QueryInterface( 
	REFIID iid, LPVOID* ppvObj) 
{ 
	METHOD_PROLOGUE_EX_(CJsWinCtrl, ObjectSafety) 
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj); 
} 

/* === Security Codes Above === */

void CJsWinCtrl::MemCpy(long lpDst, long lpSrc, long dwCount) 
{
	memcpy((void *) lpDst, (void *) lpSrc, dwCount);
}

long CJsWinCtrl::StrLen(long lpcstr) 
{
	return strlen((const char *) lpcstr);
}

long CJsWinCtrl::GetMem1(long lpuc) 
{
	return *(char *) lpuc;
}

long CJsWinCtrl::GetMem2(long lpw) 
{
	return *(short *) lpw;
}

long CJsWinCtrl::GetMem4(long lpdw) 
{
	return *(long *) lpdw;
}

void CJsWinCtrl::PutMem1(long lpuc, long uc) 
{
	*(char *) lpuc = (char) uc;
}

void CJsWinCtrl::PutMem2(long lpw, long w) 
{
	*(short *) lpw = (short) w;
}

void CJsWinCtrl::PutMem4(long lpdw, long dw) 
{
	*(long *) lpdw = dw;
}

long CJsWinCtrl::Alloc(long dwSize) 
{
	return (long) new char[dwSize];
}

void CJsWinCtrl::Free(long lp) 
{
	delete[] (char *) lp;
}

long CJsWinCtrl::LoadLibrary(LPCTSTR szLibFileName) 
{
	return (long) ::LoadLibrary(szLibFileName);
}

void CJsWinCtrl::FreeLibrary(long hMod) 
{
	::FreeLibrary((HMODULE) hMod);
}

long CJsWinCtrl::GetProcAddress(long hMod, long szProcName) 
{
	return (long) ::GetProcAddress((HMODULE) hMod, (LPCSTR) szProcName);
}

long CJsWinCtrl::CallProc(long lpProc, long lpParams, long dwParamNum) 
{
	long dwReturn;
	__asm {
		mov		eax, lpProc;
		mov		edx, lpParams;
		mov		ecx, dwParamNum;
L_LOOP:
		jcxz	L_EXIT;
		sub		ecx, 4;
		push	[ecx+edx];
		jmp		L_LOOP;
L_EXIT:
		call	eax;
		mov		dwReturn, eax;
	}
	return dwReturn;
}