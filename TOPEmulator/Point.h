#pragma once

struct Point
{
	long x;
	long y;
};

struct Square
{
	Point centre;
	long radius;
};

struct Rect
{
	Point ltop;
	Point rbtm;
	long width()const { return rbtm.x - ltop.x; }
	long height()const { return rbtm.y - ltop.y; }
};

inline bool operator==(const Point & P1,const Point & P2)
{
	return (P1.x == P2.x) && (P1.y == P2.y);
}

template <class T>
inline int operator!=(const T & T1,const T & T2)
{
	return !(T1 == T2);
}