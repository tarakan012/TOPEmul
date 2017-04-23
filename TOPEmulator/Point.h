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