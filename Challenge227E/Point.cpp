#include "Point.h"

Point::Point(ll x, ll y) : x(x), y(y) {};

void Point::toZeroSpace(ll gridSize)
{
	ll delta = (gridSize / 2 + 1);
	x -= delta;
	y -= delta;
}

void Point::toNormalSpace(ll gridSize)
{
	ll delta = (gridSize / 2 + 1);
	x += delta;
	y += delta;
}