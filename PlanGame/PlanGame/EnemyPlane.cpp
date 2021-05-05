#include "stdafx.h"
#include "EnemyPlane.h"

CImageList EnemyPlane::m_Images;

EnemyPlane::EnemyPlane(int motion) :m_wait(0), m_speed(1)
{
	m_direction = motion;
	int random = rand();
	/*Randomly generates the position of enemy aircraft*/
	m_ptPos.x = rand() % 1000;
	/*The enemy plane was flying in a downward direction*/
	if (m_direction == DOWN)
	{
		m_ptPos.y = 600;
		m_nImgIdx = DOWN_IDX;
	}//if
	/*The enemy plane was flying in an upward direction*/
	else{
		m_ptPos.y = 0;
		m_nImgIdx = UP_IDX;
	}//else
}


EnemyPlane::~EnemyPlane()
{
}

BOOL EnemyPlane::Draw(CDC *pDC, BOOL bPause)
{
	/*The position of the enemy aircraft varies randomly*/
	/*The enemy planes flew upward*/
	if (m_direction == UP)
		m_ptPos.y += (m_speed + rand() % 10);
	/*The enemy planes were flying down*/
	else
		m_ptPos.y -= (m_speed + rand() % 10);
	m_Images.Draw(pDC, m_nImgIdx, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL EnemyPlane::LoadImageW()
{
	return GameObject::LoadImage(m_Images, IDB_ENEMYPLANE, RGB(0, 0, 0), 35, 35, 1);
}

BOOL EnemyPlane::isFired()
{
	return TRUE;
}