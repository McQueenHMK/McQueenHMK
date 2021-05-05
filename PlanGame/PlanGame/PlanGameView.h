
// PlanGameView.h : CPlanGameView 
//

#pragma once
#include "GameObject.h"
#include "MyPlane.h"
#include "EnemyPlane.h"
#include "MyBullet.h"
#include "EnemyBullet.h"
#include "Explosion.h"

#define TIME1 30
#define TIME2 300
#define TIME3 600

class CPlanGameView : public CView
{
protected: // Created only from serialization
	CPlanGameView();
	DECLARE_DYNCREATE(CPlanGameView)

// features
public:
	CPlanGameDoc* GetDocument() const;

	/*Create individual GameObjects*/
	MyPlane *myPlane;
	EnemyPlane *enemyPlane;
	MyBullet *myBullet;
	EnemyBullet *enemyBullet;
	Explosion *explosion;

	/*Create a linked list of GameObjects*/
	CObList myPlaneList;
	CObList enemyPlaneList;
	CObList myBulletList;
	CObList enemyBulletList;
	CObList explosionList;

	/*Aircraft speed*/
	int myPlaneSpeed;	/*Aircraft speed*/
	int myLifeTime;		/*Fighter Health*/
	int myScore;	/*Aircraft score*/
	int myLifeCount;	/*Change in health*/
	int myPass;		/*The current level*/
	int is_pass;	/*Whether the customs clearance*/
	int is_pause;	/*Whether to suspend*/

// operation
public:
	int GetSpeed()	const{
		return myPlaneSpeed;
	}

	void SetSpeed(int s)
	{
		myPlaneSpeed = s;
	}

// rewrite
public:
	virtual void OnDraw(CDC* pDC);  // Overwrite to draw the view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	/*Draw the canvas*/
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
// implementation
public:
	virtual ~CPlanGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message mapping function
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	/*Restart the application*/
	afx_msg void OnRestart();
	/*Suspend application*/
	afx_msg void OnPause();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // PlanGameView.cpp Debug version in
inline CPlanGameDoc* CPlanGameView::GetDocument() const
   { return reinterpret_cast<CPlanGameDoc*>(m_pDocument); }
#endif

