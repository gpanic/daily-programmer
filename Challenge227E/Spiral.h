#pragma once
#include <cmath>
#include "Point.h"

typedef long long ll;

class Spiral
{

public:
	Spiral(ll gridSize);

	ll getNumberOfPoint(const Point& point);
	Point getPointOfNumber(ll pointNumber);

private:
	ll gridSize;

	ll getRingNumber(const ll& pointNumber);
	ll getRingPointNumber(const ll& ringNumber);
	Point getRingPoint(const ll& ringNum);
	ll getRingDimension(const ll& ringNumber);
	ll getRingNumberOfPoint(const Point& point);
	bool pointOnBottomLeftSideOfRing(const Point& point, const ll& ringNumber);
	ll manhattanDistance(const Point& a, const Point& b);
};
