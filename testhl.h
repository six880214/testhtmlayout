// testhl.h : main header file for the TESTHL application
//

#if !defined(AFX_TESTHL_H__6C7B609B_28F8_4D57_8157_FB56ABAF5755__INCLUDED_)
#define AFX_TESTHL_H__6C7B609B_28F8_4D57_8157_FB56ABAF5755__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTesthlApp:
// See testhl.cpp for the implementation of this class
//

class CTesthlApp : public CWinApp
{
public:
	CTesthlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTesthlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTesthlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTHL_H__6C7B609B_28F8_4D57_8157_FB56ABAF5755__INCLUDED_)
