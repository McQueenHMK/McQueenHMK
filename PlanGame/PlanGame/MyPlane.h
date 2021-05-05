#pragma once
#include "GameObject.h"

/************************************************************************/
/*                        Aircraft object
/************************************************************************/
class MyPlane :
	public GameObject
{
public:
	MyPlane();
	~MyPlane();

	BOOL Draw(CDC *pDC, BOOL bPause);

	static BOOL LoadImage();

	/*Get the rectangular area where the fighter is*/
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + PLANE_WIDTH, m_ptPos.y + PLANE_HEIGHT));
	}

	/*Can fighter jets fire bullets*/
	BOOL isFired();

public:
	/*Sets the length and width of the fighter*/
	static const int PLANE_WIDTH = 50;
	static const int PLANE_HEIGHT = 60;

private:
	static CImageList m_Images;/*Storage fighter pictures*/
};

