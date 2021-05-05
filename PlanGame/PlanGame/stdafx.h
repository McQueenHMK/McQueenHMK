
// stdafx.h : The inclusion file of a standard system containing file£¬
// Or frequently used but not often changed
// Project-specific include files

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely used data from the Windows header
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // Some of the CString constructors will be explicit

// Turn off MFC's hiding of some common warning messages that can often be safely ignored
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core components and standard components
#include <afxext.h>         //MFC extension





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 common controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             //MFC support for Windows common controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for Ribbon and control bars











