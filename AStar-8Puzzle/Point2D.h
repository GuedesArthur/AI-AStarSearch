#pragma once
#include <cmath>

struct Point2D
{
	static const Point2D Up, Down, Left, Right;
	static const Point2D Directions[4];

	int x, y;

	Point2D(int x, int y);
	static int ManehattanDist(Point2D* a, Point2D* b);
	inline int ManehattanDist(Point2D* other);
	inline int ManehattanDist(int x, int y);

	Point2D operator + (Point2D const& point);
	Point2D operator - (Point2D const& point);
	Point2D operator * (int const& k);
	bool operator ==(Point2D const& point);
};

