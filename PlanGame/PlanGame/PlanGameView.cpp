
// PlanGameView.cpp : CPlanGameView The realization of the class
//

#include "stdafx.h"
// SHARED_HANDLERS Can be implemented in the preview, thumbnail and search filter handle
// ATL Project and allows the document code to be shared with the project.
#ifndef SHARED_HANDLERS
#include "PlanGame.h"
#endif

#include "PlanGameDoc.h"
#include "PlanGameView.h"

#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include <MMSYSTEM.H>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanGameView

IMPLEMENT_DYNCREATE(CPlanGameView, CView)

BEGIN_MESSAGE_MAP(CPlanGameView, CView)
	/*Standard print command*/
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_UPDATEUISTATE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_RESTART, &CPlanGameView::OnRestart)
	ON_COMMAND(ID_PAUSE , &CPlanGameView::OnPause)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPlanGameView Construct/destruct
//Fighter health, Fighter score, Fighter increased health number, checkpoint, clearance, pause
CPlanGameView::CPlanGameView():
myLifeTime(10), myScore(0), myLifeCount(1), myPass(1), is_pass(0), is_pause(0)
{
	// TODO:  Add the construction code here
	/*Default speed of the fighter*/
	myPlaneSpeed = 30;

	/*Loads images of each GameObject*/
	MyPlane::LoadImageW();
	EnemyPlane::LoadImageW();
	MyBullet::LoadImageUp();
	MyBullet::LoadImageDown();
	EnemyBullet::LoadImageW();
	Explosion::LoadImageW();
}

CPlanGameView::~CPlanGameView()
{
}

BOOL CPlanGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  Modify it here
	//  CREATESTRUCT cs To modify the window class or style

	return CView::PreCreateWindow(cs);
}

// CPlanGameView 

void CPlanGameView::OnDraw(CDC* /*pDC*/)
{
	CPlanGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  Here, add the draw code for the native data
}

/*CPlaneGameView */
BOOL CPlanGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	/*The default*/
	return DoPreparePrinting(pInfo);
}

void CPlanGameView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlanGameView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlanGameView debug

#ifdef _DEBUG
void CPlanGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanGameDoc* CPlanGameView::GetDocument() const // The non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanGameDoc)));
	return (CPlanGameDoc*)m_pDocument;
}
#endif //_DEBUG

// CPlanGameView Message handler
int CPlanGameView::OnCreate(LPCREATESTRUCT lpcs)
{
	/*View creation failed*/
	if (CView::OnCreate(lpcs) == -1)
	{
		return -1;
	}//if

	/*TODO: Application-specific code*/
	//£¨1£©Create a fighter object
	myPlane = new MyPlane;
	//£¨2£©Setup instructions dialog box (#define IDYES 6 #define IDNO 7)
	if (AfxMessageBox(L"Please click "Yes" to view the game instructions, or "No" to enter the game directly¡±£¡", MB_YESNO) == 6)
	{
		AfxMessageBox(L"The direction key control aircraft direction, the space bar shooting, the mouse can be controlled. Initial health is 10, kill an enemy plane plus 1 point, if the score meets the requirements to proceed to the next level. With the increase of the checkpoints, the speed and number of enemy aircraft are increased, through 3 clearance can be cleared£¡");
		/*Set the sleep time in milliseconds*/
		Sleep(1000);
	}//if
	/*Enter the main interface and set the refresh time*/
	SetTimer(1, TIME1, NULL);
	SetTimer(2, TIME2, NULL);
	SetTimer(3, TIME3, NULL);
	return 0;
}

/************************************************************************/
/*nIDEvent This is from the setTimer function in the previous step*/
void CPlanGameView::OnTimer(UINT nIDEvent)
{
	/*Get Rectangular Region*/
	CDC *pDC = GetDC();
	CRect cRect;
	GetClientRect(&cRect);

	/*Device environment object class ---- CDC class*/
	CDC cdc;
	/*Host temporary map bitmap in memory*/
	CBitmap bitMap1;

	//This function creates a memory device context that is compatible with the specified device£¨DC£©
	cdc.CreateCompatibleDC(pDC);
	//This function creates a device - compatible bitmap that is relevant to the specified device environment
	bitMap1.CreateCompatibleBitmap(pDC, cRect.Width(), cRect.Height());
	//This function selects an object into the specified device context. The new object replaces the previous object of the same type.
	CBitmap *pOldBit = cdc.SelectObject(&bitMap1);
	//Fill the text rectangle with a fixed solid color
	cdc.FillSolidRect(cRect, RGB(51, 255, 255));
	//Add a background image
	CBitmap bgBitMap;
	bgBitMap.LoadBitmap(IDB_BACKGROUND);

	/*The bitmap2*/
	BITMAP bitMap2;
	bgBitMap.GetBitmap(&bitMap2);

	/*Define a compatible CDC*/
	CDC bgCdc;
	bgCdc.CreateCompatibleDC(&cdc);

	CBitmap *old = bgCdc.SelectObject(&bgBitMap);
	cdc.StretchBlt(0, 0, cRect.Width(), cRect.Height(), &bgCdc, 0, 0, bitMap2.bmWidth, bitMap2.bmHeight, SRCCOPY);

	/*==================================Add aircraft, keyboard manual control aircraft======================================*/
	if (myPlane != NULL)
	{
		myPlane->Draw(&cdc, TRUE);
	}//if
	/*Get the keyboard message pressed by the user, and the fighter position responds*/
	if ((GetKeyState(VK_UP) < 0 || GetKeyState('W') < 0) && is_pause == 0)
	{
		/*The aircraft coordinates are over the upper boundary*/
		if (myPlane->GetPoint().y < cRect.top)
			myPlane->SetPoint(myPlane->GetPoint().x, cRect.bottom);
		else
			myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y - myPlaneSpeed);
	}//if
	if ((GetKeyState(VK_DOWN) < 0 || GetKeyState('S') < 0) && is_pause == 0)//Under the direction key
	{
		if (myPlane->GetPoint().y>cRect.bottom)
			myPlane->SetPoint(myPlane->GetPoint().x, cRect.top);
		else
			myPlane->SetPoint(myPlane->GetPoint().x, (myPlane->GetPoint().y + myPlaneSpeed));
	}//if
	if ((GetKeyState(VK_LEFT) < 0 || GetKeyState('A') < 0) && is_pause == 0)//The left arrow keys
	{
		if (myPlane->GetPoint().x < cRect.left)
			myPlane->SetPoint(cRect.right, myPlane->GetPoint().y);
		else
			myPlane->SetPoint((myPlane->GetPoint().x - myPlaneSpeed), myPlane->GetPoint().y);
	}//if
	if ((GetKeyState(VK_RIGHT) < 0 || GetKeyState('D') < 0) && is_pause == 0)//Right direction key
	{
		if (myPlane->GetPoint().x > cRect.right)
			myPlane->SetPoint(cRect.left, myPlane->GetPoint().y);
		else
			myPlane->SetPoint((myPlane->GetPoint().x + myPlaneSpeed), myPlane->GetPoint().y);
	}//if
	/*Space bar fire bullets (warplanes fire double columns of bullets)*/
	if (GetKeyState(VK_SPACE) < 0 && is_pause == 0)
	{
		MyBullet *bullet1 = new MyBullet(myPlane->GetPoint().x, myPlane->GetPoint().y, UP);
		myBulletList.AddTail(bullet1);
		MyBullet *bullet2 = new MyBullet(myPlane->GetPoint().x + 35, myPlane->GetPoint().y, UP);
		myBulletList.AddTail(bullet2);
		/*Play the sound of fighter firing bullets*/
		PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	}//if

	/*The Z key stands for pause*/
	if (GetKeyState('Z') < 0)
	{
		is_pause += 1;
		if (is_pause != 1)
			is_pause = 0;
	}//if

	/*=====Add enemy planes randomly, and the enemy planes launch bombs randomly. At this time, the speed of enemy planes is related to the number and level =======================*/
	if (myPlane != NULL && is_pause == 0)
	{
		switch (nIDEvent)
		{
		case 2:
			{
				  /*This is level 1*/
				  if (1 == myPass)
				  {
					  int dir = UP;
					  EnemyPlane *enemyPlane1 = new EnemyPlane(dir);
					  enemyPlaneList.AddTail(enemyPlane1);
				  }//if
				  /*You are currently in level 2 and above. Enemy planes are flying out from both directions*/
				  else if (2 <= myPass)
				  {
					  int dir1 = UP;
					  EnemyPlane *enemyPlane1 = new EnemyPlane(dir1);
					  /*Enemy planes will fly at different speeds depending on the level*/
					  enemyPlane1->SetSpeed((rand() % 5 + 1) * myPass);
					  enemyPlaneList.AddTail(enemyPlane1);

					  int dir2 = DOWN;
					  EnemyPlane *enemyPlane2 = new EnemyPlane(dir2);
					  enemyPlane2->SetSpeed((rand() % 5 + 1) * myPass);
					  enemyPlaneList.AddTail(enemyPlane2);
				  }//elif
			}//case
			break;

		default:
			break;
		}//switch

		/*Delete enemy planes outside the game screen*/
		POSITION epPos = NULL, epPosTmp = NULL;
		epPos = enemyPlaneList.GetHeadPosition();
		while (epPos != NULL)
		{
			epPosTmp = epPos;
			enemyPlane = (EnemyPlane *)enemyPlaneList.GetNext(epPos);
			/*Determine whether enemy aircraft are out of bounds*/
			if (enemyPlane->GetPoint().x < cRect.left || enemyPlane->GetPoint().x > cRect.right ||
				enemyPlane->GetPoint().y < cRect.top || enemyPlane->GetPoint().y > cRect.bottom)
			{
				enemyPlaneList.RemoveAt(epPosTmp);
				delete enemyPlane;
			}//if
			else{
				enemyPlane->Draw(&cdc, TRUE);
				switch (nIDEvent)
				{
				//Set the timer to generate enemy bombs
				case 3:
					{
						  EnemyBullet *eb = new EnemyBullet(enemyPlane->GetPoint().x + 17, enemyPlane->GetPoint().y + 30, enemyPlane->GetDirection());
						  enemyBulletList.AddTail(eb);
						  /*The enemy plane fired bullets*/
						  PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					}//case
					break;
				}//switch
			}//else
		}//while

		/*Determine whether the bullets fired by the enemy aircraft are out of bounds. If so, delete them*/
		POSITION ebPos = NULL, ebPosTmp = NULL;
		ebPos = enemyBulletList.GetHeadPosition();
		while (ebPos != NULL)
		{
			ebPosTmp = ebPos;
			enemyBullet = (EnemyBullet *)enemyBulletList.GetNext(ebPos);
			if (enemyBullet->GetPoint().x <cRect.left || enemyBullet->GetPoint().x > cRect.right ||
				enemyBullet->GetPoint().y < cRect.top || enemyBullet->GetPoint().y >cRect.bottom)
			{
				enemyBulletList.RemoveAt(ebPosTmp);
				delete enemyBullet;
			}//if
			else{
				enemyBullet->Draw(&cdc, TRUE);
			}//else
		}//while
	}//if

	/*=============================Deal with fighters firing bullets======================================*/
	if (myPlane != NULL && is_pause == 0)
	{
		/*Declare the position of the bullet*/
		POSITION mbPos = NULL, mbPosTmp = NULL;
		mbPos = myBulletList.GetHeadPosition();
		while (mbPos != NULL)
		{
			mbPosTmp = mbPos;
			myBullet = (MyBullet *)myBulletList.GetNext(mbPos);
			/*Delete bullets that are out of bounds*/
			if (myBullet->GetPoint().x < cRect.left || myBullet->GetPoint().x > cRect.right ||
				myBullet->GetPoint().y < cRect.top || myBullet->GetPoint().y > cRect.bottom)
			{
				myBulletList.RemoveAt(mbPosTmp);
				delete myBullet;
			}//if
			else
				myBullet->Draw(&cdc, TRUE);
		}//while
	}//if

	/*=================£¨1£©Added explosion effect, fighter bullets hit enemy aircraft================================*/
	if (myPlane != NULL && is_pause == 0)
	{
		POSITION explosionPos = NULL;
		explosionPos = explosionList.GetHeadPosition();
		/*Check the explosion list and display it at its location when it is not empty*/
		while (explosionPos != NULL)
		{
			explosion = (Explosion *)explosionList.GetNext(explosionPos);
			explosion->Draw(&cdc, TRUE);
		}//while
		POSITION mbPos, mbPosTmp, epPos, epPosTmp;
		for (mbPos = myBulletList.GetHeadPosition(); (mbPosTmp = mbPos) != NULL;)
		{
			/*Aircraft bullets*/
			myBullet = (MyBullet *)myBulletList.GetNext(mbPos);
			/*Obtain a rectangular area for the fighter's bullets*/
			CRect myBulletRect = myBullet->GetRect();
			/*Go through all enemy planes, and if they cross bullets, they explode, destroying them*/
			for (epPos = enemyPlaneList.GetHeadPosition(); (epPosTmp = epPos) != NULL;)
			{
				enemyPlane = (EnemyPlane *)enemyPlaneList.GetNext(epPos);
				/*Obtain the rectangular area where the enemy aircraft is*/
				CRect enemyPlaneRect = enemyPlane->GetRect();
				/*Determine whether the enemy plane and fighter bullets have crossed*/
				CRect tmpRect;
				if (tmpRect.IntersectRect(&myBulletRect, &enemyPlaneRect))
				{
					/*Add the explosion object to the explosion list*/
					Explosion *explosion = new Explosion((enemyPlane->GetPoint().x + 17), (enemyPlane->GetPoint().y + 17));
					explosionList.AddTail(explosion);
					/*Play the explosion sound*/
					PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					
					/*Remove the bullet after the explosion*/
					myBulletList.RemoveAt(mbPosTmp);
					delete myBullet;

					/*Delete the enemy planes*/
					enemyPlaneList.RemoveAt(epPosTmp);
					delete enemyPlane;

					/*If you hit an enemy plane, the fighters gain one point*/
					++myScore;
					break;
				}//if
			}
		}//for
	}//if

	/*=================£¨2£©Added an explosion effect. Enemy bullets hit the fighter================================*/
	if (myPlane != NULL && is_pause == 0)
	{
		/*Bullet position of enemy aircraft*/
		POSITION ebPos, ebPosTmp;
		for (ebPos = enemyBulletList.GetHeadPosition(); (ebPosTmp = ebPos) != NULL;)
		{
			enemyBullet = (EnemyBullet *)enemyBulletList.GetNext(ebPos);
			/*Receive a rectangular area for enemy aircraft bullets*/
			CRect enemyBulletRect = enemyBullet->GetRect();
			/*Obtain the Fighter Rectangular Area*/
			CRect myPlaneRect = myPlane->GetRect();
			/*Determine whether there is crossover*/
			CRect tmpRect;
			if (tmpRect.IntersectRect(&enemyBulletRect, &myPlaneRect))
			{
				/*Add the explosion object to the explosion list*/
				Explosion *explosion = new Explosion((enemyPlane->GetPoint().x + 17), (enemyPlane->GetPoint().y + 17));
				explosionList.AddTail(explosion);
				/*Play the explosion sound*/
				PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				/*Delete enemy cartridges*/
				enemyBulletList.RemoveAt(ebPosTmp);
				delete enemyBullet;

				/*Health minus 1*/
				--myLifeTime;
				if (0 == myLifeTime)
				{
					/*Delete the aircraft,*/
					delete myPlane;
					myPlane = NULL;
				}//if
				break;
			}//if
		}//for
	}//if
	/*=================£¨3£©Add an explosion effect, and the fighter will collide with the enemy================================*/
	if (myPlane != NULL && is_pause == 0)
	{
		POSITION epPos, epPosTmp;
		for (epPos = enemyPlaneList.GetHeadPosition(); (epPosTmp = epPos) != NULL;)
		{
			enemyPlane = (EnemyPlane *)enemyPlaneList.GetNext(epPos);
			/*Obtain a rectangular area for enemy aircraft*/
			CRect enemyPlaneRect = enemyPlane->GetRect();
			/*Obtain the Fighter Rectangular Area*/
			CRect myPlaneRect = myPlane->GetRect();

			CRect tmpRect;
			if (tmpRect.IntersectRect(&enemyPlaneRect, &myPlaneRect))
			{
				Explosion *explosion = new Explosion((enemyPlane->GetPoint().x + 18), (enemyPlane->GetPoint().y + 18));
				explosionList.AddTail(explosion);
				/*Play the explosion sound*/
				PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				/*Delete the enemy planes*/
				enemyPlaneList.RemoveAt(epPosTmp);
				delete enemyPlane;

				/*Fighter health reduced by 1*/
				--myLifeTime;
				if (0 == myLifeTime)
				{
					/*Delete Fighter Object*/
					delete myPlane;
					myPlane = NULL;
				}//if
				break;
			}//if
		}//for
	}//if
	/*=================£¨4£©Added an explosion effect. Fighter bullets collide with enemy bullets================================*/
	if (myPlane != NULL && is_pause == 0)
	{
		/*Declare the position of fighter bullets and enemy bullets*/
		POSITION mbPos, mbPosTmp, ebPos, ebPosTmp;
		for (mbPos = myBulletList.GetHeadPosition(); (mbPosTmp = mbPos) != NULL;)
		{
			myBullet = (MyBullet *)myBulletList.GetNext(mbPos);
			/*Obtain a rectangular area for the fighter's bullets*/
			CRect myBulletRect = myBullet->GetRect();
			for (ebPos = enemyBulletList.GetHeadPosition(); (ebPosTmp = ebPos) != NULL;)
			{
				enemyBullet = (EnemyBullet *)enemyBulletList.GetNext(ebPos);
				/*Receive a rectangular area for enemy aircraft bullets*/
				CRect enemyBulletRect = enemyBullet->GetRect();
				/*Determine whether there is crossover*/
				CRect tmpRect;
				if (tmpRect.IntersectRect(&myBulletRect, &enemyBulletRect))
				{
					//Adds an explosion object to the explosion linked list
					Explosion *explosion = new Explosion((enemyBullet->GetPoint().x + 17), (enemyBullet->GetPoint().y + 17));
					explosionList.AddTail(explosion);

					/*Play the explosion sound*/
					PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					//Delete fighter bullets after explosion
					myBulletList.RemoveAt(mbPosTmp);
					delete myBullet;

					/*Delete enemy cartridges*/
					enemyBulletList.RemoveAt(ebPosTmp);
					delete enemyBullet;

					/*The fighters gain one point*/
					++myLifeTime;
					break;
				}//if
			}//for
		}//for
	}//if
	/*=================================The game interface outputs the current information of the game========================*/
	if (myPlane != NULL && is_pause == 0)
	{
		HFONT font;
		font = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(font);
		CString str;
		cdc.SetTextColor(RGB(255, 0, 0));
		str.Format(_T("The current level:%d"), myPass);
		cdc.TextOutW(10, 20, str);
		str.Format(_T("The current score:%d"), myScore);
		cdc.TextOutW(10, 40, str);
		str.Format(_T("The remaining life:%d"), myLifeTime);
		cdc.TextOutW(10, 60, str);
	}//if
	/*Increases aircraft health as requested*/
	if (myPlane != NULL && is_pause == 0)
	{
		if (myScore > 10 * myLifeCount * myPass)
		{
			myLifeTime++;
			myLifeCount++;
		}
	}//if
	/*=================================Enter the next level interface========================*/
	if (myPlane != NULL && myScore > 50 * myPass && is_pause == 0)
	{
		delete myPlane;
		myPlane = NULL;
		/*That pass has been passed*/
		is_pass = 1;
	}//if
	/*Enter the next level*/
	if (is_pass == 1)
	{
		/*After the third pass, the game fighter has cleared the customs*/
		if (3 == myPass)
		{
			/*Turn off the timer*/
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			if (AfxMessageBox(L"Wow, congratulations! You've finished! Whether to start over£¿", MB_YESNO) == 6)
			{
				/*Clear the fighter list*/
				myPlaneList.RemoveAll();
				/*Clear the list of enemy planes*/
				enemyPlaneList.RemoveAll();
				/*Clear the Fighter Bullet List*/
				myBulletList.RemoveAll();
				/*Clear the enemy's bullet list*/
				enemyBulletList.RemoveAll();
				/*Clear the bomb list*/
				explosionList.RemoveAll();

				/*Generate new fighters*/
				myPlane = new MyPlane;
				myScore = 0;
				myLifeCount = 1;
				myLifeTime = 10;
				myPass = 1;
				is_pass = 0;
				SetTimer(1, TIME1, NULL);
				SetTimer(2, TIME2, NULL);
				SetTimer(3, TIME3, NULL);
			}//if
			else
				exit(1);
		}//if
		else{
			/*Turn off the timer*/
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			if (AfxMessageBox(L"Wow, congratulations, you got through! Whether to proceed to the next level£¿", MB_YESNO) == 6)
			{
				/*Clear the fighter list*/
				myPlaneList.RemoveAll();
				/*Clear the list of enemy planes*/
				enemyPlaneList.RemoveAll();
				/*Clear the Fighter Bullet List*/
				myBulletList.RemoveAll();
				/*Clear the enemy's bullet list*/
				enemyBulletList.RemoveAll();
				/*Clear the bomb list*/
				explosionList.RemoveAll();
				/*Generate new fighters*/
				myPlane = new MyPlane;
				myScore = 0;
				myLifeCount = 1;
				myLifeTime = 10;
				++myPass;
				is_pass = 0;
				SetTimer(1, TIME1, NULL);
				SetTimer(2, TIME2, NULL);
				SetTimer(3, TIME3, NULL);
			}//if
			else
				exit(1);
		}//else
	}//if
	/*=================================End the game interface========================*/
	if (myPlane == NULL && is_pass == 0 && is_pause == 0)
	{
		KillTimer(1);
		KillTimer(2);
		KillTimer(3);
		if (AfxMessageBox(L"GAME OVER£¡COME ON £¡restart£¿", MB_YESNO) == 6)
		{
			/*Clear the fighter list*/
			myPlaneList.RemoveAll();
			/*Clear the list of enemy planes*/
			enemyPlaneList.RemoveAll();
			/*Clear the Fighter Bullet List*/
			myBulletList.RemoveAll();
			/*Clear the enemy's bullet list*/
			enemyBulletList.RemoveAll();
			/*Clear the bomb list*/
			explosionList.RemoveAll();

			/*Generate new fighters*/
			myPlane = new MyPlane;
			myScore = 0;
			myLifeCount = 1;
			myLifeTime = 10;
			myPass = 1;
			is_pass = 0;
			SetTimer(1, TIME1, NULL);
			SetTimer(2, TIME2, NULL);
			SetTimer(3, TIME3, NULL);
		}//if
		else
			exit(1);
	}//if

	/*This function converts the pixels in the specified area of the source device environment to bit_blocks for transfer to the target device environment*/
	pDC->BitBlt(0, 0, cRect.Width(), cRect.Height(), &cdc, 0, 0, SRCCOPY);
	cdc.DeleteDC();
	bitMap1.DeleteObject();
	ReleaseDC(pDC);
	CView::OnTimer(nIDEvent);
}//onTimer
/*===================================================================================*/
void CPlanGameView::OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/)
{
	// TODO: This is where you add the message handler code and/or invoke default values	
}

BOOL CPlanGameView::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}
/*Restart the application*/
void CPlanGameView::OnRestart()
{
	/*Clear the fighter list*/
	myPlaneList.RemoveAll();
	/*Clear the list of enemy planes*/
	enemyPlaneList.RemoveAll();
	/*Clear the Fighter Bullet List*/
	myBulletList.RemoveAll();
	/*Clear the enemy's bullet list*/
	enemyBulletList.RemoveAll();
	/*Clear the bomb list*/
	explosionList.RemoveAll();

	/*Generate new fighters*/
	myPlane = new MyPlane;
	myScore = 0;
	myLifeCount = 1;
	myLifeTime = 10;
	myPass = 1;
	is_pass = 0;

	SetTimer(1, TIME1, NULL);
	SetTimer(2, TIME2, NULL);
	SetTimer(3, TIME3, NULL);
}
/*Suspend application*/
void CPlanGameView::OnPause()
{
	// TODO: Add the command handler code here
	Sleep(1000);
}
void CPlanGameView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: This is where you add the message handler code and/or invoke default values
	CView::OnMouseMove(nFlags, point);
	if (is_pause == 0)
		myPlane->SetPoint(point.x, point.y);
}

void CPlanGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add the message handler code and/or invoke default values here
	CView::OnLButtonDown(nFlags, point);
	if (is_pause == 0)
	{
		MyBullet *myBullet1 = new MyBullet(myPlane->GetPoint().x, myPlane->GetPoint().y, UP);
		/*Sound of firing bullets*/
		PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		myBulletList.AddTail(myBullet1);
		MyBullet *myBullet2 = new MyBullet(myPlane->GetPoint().x + 35, myPlane->GetPoint().y, UP);
		myBulletList.AddTail(myBullet2);
	}//if
}

void CPlanGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: This is where you add the message handler code and/or invoke default values

	switch (nChar)
	{
	case VK_UP:
		myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y - myPlaneSpeed);
		break;
	case VK_DOWN:
		myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y + myPlaneSpeed);
		break;
	case VK_RIGHT:
		myPlane->SetPoint(myPlane->GetPoint().x + myPlaneSpeed, myPlane->GetPoint().y);
		break;
	case VK_LEFT:
		myPlane->SetPoint(myPlane->GetPoint().x - myPlaneSpeed, myPlane->GetPoint().y);
		break;
	}

	Invalidate(true);//According to the information
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
