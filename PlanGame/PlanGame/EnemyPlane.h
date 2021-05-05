#pragma once
#include "GameObject.h"

/************************************************************************/
/*                        The enemy plane object
/************************************************************************/

class EnemyPlane :
	public GameObject
{
public:
	EnemyPlane(int motion);
	~EnemyPlane();

	BOOL Draw(CDC *pDC, BOOL bPause);
	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMYPLANE_HEIGHT, m_ptPos.y + ENEMYPLANE_HEIGHT));
	}

	int GetDirection()	const
	{
		return m_direction;
	}

	void SetDirection(int dir)
	{
		m_direction = dir;
	}

	void SetSpeed(int s)
	{
		m_speed = s;
	}

	BOOL isFired();
private:
	/*The width and height of the enemy aircraft*/
	static const int ENEMYPLANE_HEIGHT = 35;
	static CImageList m_Images;

	/*Enemy flight direction 1*/
	int m_direction;

	/*Enemy plane image index*/
	int m_nImgIdx;

	/*Enemy aircraft speed*/
	int m_speed;

	/*Launch time delay*/
	int m_wait;
};

