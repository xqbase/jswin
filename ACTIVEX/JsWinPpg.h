#if !defined(AFX_JSWINPPG_H__C13755CF_A986_4F6F_86E8_8D4361C9E610__INCLUDED_)
#define AFX_JSWINPPG_H__C13755CF_A986_4F6F_86E8_8D4361C9E610__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JsWinPpg.h : Declaration of the CJsWinPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CJsWinPropPage : See JsWinPpg.cpp for implementation.

class CJsWinPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CJsWinPropPage)
	DECLARE_OLECREATE_EX(CJsWinPropPage)

// Constructor
public:
	CJsWinPropPage();

// Dialog Data
	//{{AFX_DATA(CJsWinPropPage)
	enum { IDD = IDD_PROPPAGE_JSWIN };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CJsWinPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSWINPPG_H__C13755CF_A986_4F6F_86E8_8D4361C9E610__INCLUDED)
