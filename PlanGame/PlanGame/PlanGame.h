
// PlanGame.h : PlanGame The main header file of the application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "Include "stdafx.h" before including this file to generate the PCH file"
#endif

#include "resource.h"       // The main symbol


// CPlanGameApp:
// See the implementation of this class PlanGame.cpp
//

class CPlanGameApp : public CWinAppEx
{
public:
	CPlanGameApp();


// rewrite
public:
	virtual BOOL InitInstance();

// implementation

	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPlanGameApp theApp;
