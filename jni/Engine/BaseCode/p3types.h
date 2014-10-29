#ifndef _P3_TYPES_H
#define _P3_TYPES_H

#include "P3Primitive.h"
#include <stdlib.h>
//����(CUIRect(left,top,right,bottom))
class CMyRect: public P3_RECT
{
public:
	CMyRect();
	CMyRect(int l, int t, int r, int b);

	CMyRect(const P3_RECT& rc);
	CMyRect(const CMyRect& src);
	CMyRect& operator=(const CMyRect& src);


	//��ȡ���
	int Width() const;

	//��ȡ�߶�
	int Height() const;

	//CRectתP3_RECT
	operator P3_RECT*();

	//CRectתconst P3_RECT
	operator const P3_RECT*();

	//��������
	void SetRect(int iLeft, int iTop, int iRight, int iBottom);

	bool EqualRect(CMyRect* r2);

	void NormalizeRect();

	//�������ε��ཻ����(�����ཻ����false,��ǰ�����ÿ�;���ཻ�����������ε��ཻ����)
	bool IntersectRect(const CMyRect *lprcSrc1, const CMyRect *lprcSrc2 );

	bool UnionRect(CMyRect*  lprc1, const CMyRect* lprc2);

	//ƫ�ƴ�С(����X����ͬʱ�����ƶ�,����Y����ͬʱ�����ƶ�)
	void OffsetRect(int x/*ƫ��X����*/, int y/*ƫ��Y����*/);

	//ƫ�ƴ�С(OffsetRect(point.x, point.y))
	void OffsetRect(P3_POS point/*ƫ�Ƶ�����*/);

	//ƫ�ƴ�С
	void OffsetRect(P3_SIZE size/*��С*/);

	//��ȵľ���ֵ
	int GetAbsWidth();

	//�߶ȵľ���ֵ
	int GetAbsHeight();

	//����߶�(top-bottom)
	int RevokeHeight();

	//�ÿ�����(top=left=bottom=right=0)
	void SetRectEmpty();

	//�����Ƿ�Ϊ��((left == right )  && (top == bottom))
	bool IsRectEmpty() const;

	//�����Ƿ񲻴���(top,left,right,bottom��Ϊ0ʱ������)
	bool IsRectNull();

	//�����Ƿ��ڱ�������(���ұ�:��rect.left<=point.x<rect.right �� rect.top<=point.y<rect.bottom ��point��rect��)
	bool PtInRect(P3_POS pt/*����*/);

	/*������Сָ�����εĿ�͸ߡ�(InflateRect�����ھ��ε����������dx,�ھ��ε���������dy�� dx��dy�������з���ֵ���������ӿ�͸ߣ�������С��) */
	void InflateRect( int dx, int dy);

	void InflateRect(const CMyRect* lpRect);	

	void InflateRect(int l, int t, int r, int b) ;	

	void DeflateRect(const CMyRect* lpRect) ;

	//��С���εı߳�
	void DeflateRect(int l, int t, int r, int b) ;

	//��С���εı߳�
	void DeflateRect(int x/*���ҵĴ�С����С*/, int y/*���µĴ�С����С*/);
};

class CMyRectTracker :public CMyRect
{
public:
	// Style Flags
	enum StyleFlags
	{
		solidLine = 1, dottedLine = 2, hatchedBorder = 4,
		resizeInside = 8, resizeOutside = 16, hatchInside = 32,
	};

	// Hit-Test codes
	enum TrackerHit
	{
		hitNothing = -1,
		hitTopLeft = 0, hitTopRight = 1, hitBottomRight = 2, hitBottomLeft = 3,
		hitTop = 4, hitRight = 5, hitBottom = 6, hitLeft = 7, hitMiddle = 8
	};
	CMyRectTracker();
	int HitTest(P3_POS point);

public:
	CMyRect	m_Rect;
	// Attributes
	int m_nStyle;      // current state
	int m_nHandleSize;
};

#endif