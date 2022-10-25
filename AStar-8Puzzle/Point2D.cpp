#include "Point2D.h"

Point2D::Point2D(int x, int y) : x(x), y(y) {}

int Point2D::ManehattanDist(Point2D* a, Point2D* b)
{
	return std::abs(b->x - a->x) + std::abs(b->y - a->y);
}

inline int Point2D::ManehattanDist(Point2D* other)
{
	return ManehattanDist(this, other);
}

inline int Point2D::ManehattanDist(int x, int y)
{
	return std::abs(x - this->x) + std::abs(y - this->y);
}

Point2D Point2D::operator+(Point2D const& point)
{
	return Point2D(x + point.x, y + point.y);
}

Point2D Point2D::operator-(Point2D const& point)
{
	return Point2D(x - point.x, y - point.y);
}

Point2D Point2D::operator*(int const& k)
{
	return Point2D(k * x, k * y);
}

bool Point2D::operator==(Point2D const& point)
{
	return x == point.x && y == point.y;
}

Point2D const Point2D::Up = { -1, 0 };
Point2D const Point2D::Down = { 1, 0 };
Point2D const Point2D::Left = { 0, -1 };
Point2D const Point2D::Right = { 0, 1 };
Point2D const Point2D::Directions[4] = {Point2D::Up, Point2D::Down, Point2D::Left, Point2D::Right};