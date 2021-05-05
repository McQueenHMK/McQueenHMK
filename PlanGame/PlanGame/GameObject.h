#pragma once
#include "afx.h"
#include "Resource.h"
/************************************************************************/
/*                         The superclass of the GameObject
/************************************************************************/
/*The GameObject's flight direction*/
enum Direction{
	STOP,
	UP,
	DOWN
};

/*Object image index*/
enum ImageIdx{
	UP_IDX,
	DOWN_IDX
};

class GameObject :
	public CObject
{
public:
	GameObject(int x = 0, int y = 0);
	/*Virtual destructor, which correctly frees subclass object resources*/
	virtual ~GameObject();

	/*The plot*/
	virtual BOOL Draw(CDC *pDC, BOOL bPause) = 0;
	/*Rectangular region*/
	virtual CRect GetRect() = 0;

	/*Gets the upper-left coordinates of the GameObject*/
	CPoint GetPoint()
	{
		return m_ptPos;
	}

	/*Set the GameObject coordinates*/
	void SetPoint(int x, int y)
	{
		m_ptPos.x = x;
		m_ptPos.y = y;
	}

protected:
	/*Load the image*/
	static BOOL LoadImage(CImageList &imgList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial);

protected:
	/*The coordinate position of the GameObject*/
	CPoint m_ptPos;
};
