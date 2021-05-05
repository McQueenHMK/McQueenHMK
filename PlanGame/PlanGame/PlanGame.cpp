
// PlanGame.cpp : Define the class behavior of the application。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PlanGame.h"
#include "MainFrm.h"

#include "PlanGameDoc.h"
#include "PlanGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanGameApp

BEGIN_MESSAGE_MAP(CPlanGameApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPlanGameApp::OnAppAbout)
	// File-based standard document commands
	//ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CPlanGameApp structure

CPlanGameApp::CPlanGameApp()
{
	m_bHiColorIcons = TRUE;

	// TODO:  Replace the following application ID string with a unique ID string; Suggested string format
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("PlanGame.AppID.NoVersion"));

	// TODO:  Add the construction code here，
	//Place all important initializations in InitInstance
}

//The only CPlangameApp object

CPlanGameApp theApp;


// CPlanGameApp Initialize

BOOL CPlanGameApp::InitInstance()
{
	CWinAppEx::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// Using the Richedit control requires AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and want to reduce them
	// The size of the final executable should be removed as follows
	// A specific initialization routine that is not required
	// Change the registry key used to store Settings
	// TODO:  This string should be modified as appropriate，
	// For example, change it to a company or organization name
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // Loading standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the document template for your application. The document template
	// Will be used as a connection between the document, the frame window, and the view
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPlanGameDoc),
		RUNTIME_CLASS(CMainFrame),       // Main SDI frame window
		RUNTIME_CLASS(CPlanGameView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Analyze the command line for standard shell commands, DDE, and open file operations
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Schedules the commands specified on the command line.
	// Starting the application with /RegServer, /Register, /Unregserver, or /Unregister returns FALSE.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//The only window is initialized, so display it and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CPlanGameApp Message handler


// The CabOutDLG dialog box for the application's About menu item

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// The application command to run the dialog box
void CPlanGameApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPlanGameApp Custom load/save methods

void CPlanGameApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CPlanGameApp::LoadCustomState()
{
}

void CPlanGameApp::SaveCustomState()
{
}

// CPlanGameApp Message handler



