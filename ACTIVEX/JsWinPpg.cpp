// JsWinPpg.cpp : Implementation of the CJsWinPropPage property page class.

#include "stdafx.h"
#include "JsWin.h"
#include "JsWinPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CJsWinPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CJsWinPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CJsWinPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CJsWinPropPage, "JSWIN.JsWinPropPage.1",
	0x649d1fa0, 0x3298, 0x4c82, 0x92, 0x42, 0xc3, 0x11, 0x8b, 0x7a, 0x99, 0x34)


/////////////////////////////////////////////////////////////////////////////
// CJsWinPropPage::CJsWinPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CJsWinPropPage

BOOL CJsWinPropPage::CJsWinPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_JSWIN_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CJsWinPropPage::CJsWinPropPage - Constructor

CJsWinPropPage::CJsWinPropPage() :
	COlePropertyPage(IDD, IDS_JSWIN_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CJsWinPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CJsWinPropPage::DoDataExchange - Moves data between page and properties

void CJsWinPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CJsWinPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CJsWinPropPage message handlers
