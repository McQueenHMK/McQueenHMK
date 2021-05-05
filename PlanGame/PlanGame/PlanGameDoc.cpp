
// PlanGameDoc.cpp : CPlanGameDoc 
//

#include "stdafx.h"
// SHARED_HANDLERS Can be implemented in the preview, thumbnail and search filter handle
// ATL Project and allows the document code to be shared with the project¡£
#ifndef SHARED_HANDLERS
#include "PlanGame.h"
#endif

#include "PlanGameDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPlanGameDoc

IMPLEMENT_DYNCREATE(CPlanGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlanGameDoc, CDocument)
END_MESSAGE_MAP()


// CPlanGameDoc Construct/destruct

CPlanGameDoc::CPlanGameDoc()
{
	// TODO:  Add one-time construct code here

}

CPlanGameDoc::~CPlanGameDoc()
{
}

BOOL CPlanGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: Add the reinitialization code here
	// (This document is reused by the SDI document)

	return TRUE;
}




// CPlanGameDoc serialization

void CPlanGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  Add the storage code here
	}
	else
	{
		// TODO:  Add the loading code here
	}
}

#ifdef SHARED_HANDLERS

// Thumbnail support
void CPlanGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw document data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Search handler support
void CPlanGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Search for content from document data Settings¡£
	// The content part should be composed of ";" separated

	//exmple:     strSearchContent = _T("point;rectangle;circle;ole object;")£»
	SetSearchContent(strSearchContent);
}

void CPlanGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPlanGameDoc diagnosis

#ifdef _DEBUG
void CPlanGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlanGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPlanGameDoc order
