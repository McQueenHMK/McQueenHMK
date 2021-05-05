
// PlanGameDoc.h : CPlanGameDoc 
//


#pragma once


class CPlanGameDoc : public CDocument
{
protected: // Created only from serialization
	CPlanGameDoc();
	DECLARE_DYNCREATE(CPlanGameDoc)

// features
public:

// operation
public:

// rewrite
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// implementation
public:
	virtual ~CPlanGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message mapping function
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
