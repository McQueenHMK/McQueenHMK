#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(int x, int y) :m_ptPos(x,y)
{
}


GameObject::~GameObject()
{
}

/*Load the GameObject image*/
BOOL GameObject::LoadImageW(CImageList &imgList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial)
{
	CBitmap bmp;
	if (!bmp.LoadBitmap(bmpID))
		return FALSE;

	if (!imgList.Create(cx, cy, ILC_COLOR24 | ILC_MASK, nInitial, 0))//nInitial The initial number
		return FALSE;//cx,cy Width of picture

	imgList.Add(&bmp, crMask);

	return TRUE;
}
