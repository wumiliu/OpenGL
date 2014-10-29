#pragma once
#include "htype.h"
#include "p3types.h"
#include "InputManager.h"

#define Rectangle CMyRect
class GRAPHIC_API ScrolRect
{
public:
	ScrolRect();
	~ScrolRect();
	ScrolRect(Rectangle _rect);
	void SetPageRect(Rectangle _rect);
	void SetRect(Rectangle _rect);
	void MouseEven(MouseType nType, MousePos pos);
	void Process();
	CMyRect m_Rectangle;
	CMyRect pageRect;
	CMyRectTracker showRect; 
	CMyRectTracker horizontalRect;  
	CMyRectTracker::TrackerHit m_hit;
	CMyRectTracker::TrackerHit m_hit1;
};

