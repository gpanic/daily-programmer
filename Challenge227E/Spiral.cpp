#include "Spiral.h"

// example:
// 5-4-3
// |   |
// 6 1-2
// |
// 7-8-9
//
// ring point - the bottom right point in a ring, an odd perfect square
// ring number - the vertical and horizontal distance from the center of
//               the grid to the ring starting at 0

Spiral::Spiral(ll gridSize) : gridSize(gridSize) {};

ll Spiral::getRingNumber(const ll& pointNumber)
{
	// truncating the sqrt gives the previous ring point number
	ll lowerSqrt = static_cast<ll>(std::sqrt(pointNumber));

	// if a perfect square and odd then it's already a ring point
	ll square = lowerSqrt * lowerSqrt;
	if (square != pointNumber || square % 2 == 0)
	{
		// get the next odd sqrt which is then a ring point
		lowerSqrt += lowerSqrt % 2 == 0 ? 1 : 2;
	}

	// get the ring number
	return lowerSqrt /= 2;
}

// map sequence of ring numbers (0, 1, 2, ...) to ring point numbers
// (1, 9, 25, ...)
ll Spiral::getRingPointNumber(const ll& ringNumber)
{
	return (ringNumber + ringNumber + 1) * (ringNumber + ringNumber + 1);
}

Point Spiral::getRingPoint(const ll& ringNum)
{
	return Point(ringNum, ringNum);
}

ll Spiral::getRingDimension(const ll& ringNumber)
{
	return ringNumber * 2 + 1;
}

// one of the coordinates of a ring point is the ring number, the other is
// then in range of -ringNumber to +ringNumber
ll Spiral::getRingNumberOfPoint(const Point& point)
{
	ll firstCoord = std::abs(point.x);
	if (point.y <= firstCoord && point.y >= -firstCoord)
	{
		return firstCoord;
	}

	ll secondCoord = std::abs(point.y);
	if (point.x <= secondCoord && point.x >= -secondCoord)
	{
		return secondCoord;
	}
	return 0;
}

bool Spiral::pointOnBottomLeftSideOfRing(const Point& point, const ll& ringNumber)
{
	return point.y == ringNumber || point.x == -ringNumber;
}

ll Spiral::manhattanDistance(const Point& a, const Point& b)
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

// start at the next ring point and go backwards
ll Spiral::getNumberOfPoint(const Point& point)
{
	Point targetPoint = point;
	targetPoint.toZeroSpace(gridSize);

	// get the next ring point
	ll ringNumber = getRingNumberOfPoint(targetPoint);
	Point ringPoint = getRingPoint(ringNumber);

	// start at the number of the next ring point as it is easily calculated
	ll number = getRingPointNumber(ringNumber);

	// deduct the distance to the point going counter clockwise using manhattan distance
	if (pointOnBottomLeftSideOfRing(targetPoint, ringNumber))
	{
		number -= manhattanDistance(ringPoint, targetPoint);
	}
	else
	{
		ll manhattanCross = manhattanDistance(ringPoint, Point(-ringPoint.x, -ringPoint.y));
		number -= manhattanCross + (manhattanCross - manhattanDistance(ringPoint, targetPoint));
	}
	return number;
}

// start at the next ring point and go backwards
Point Spiral::getPointOfNumber(ll pointNumber)
{
	// get next ring point and its number as its number is easily calculated
	ll ringNumber = getRingNumber(pointNumber);
	Point ringPoint = getRingPoint(ringNumber);
	ll ringPointNumber = getRingPointNumber(ringNumber);
	ll ringDimension = getRingDimension(ringNumber);

	// how far back the given point number is from the next ring point
	ll difference = ringPointNumber - pointNumber;

	// contains the movement for each axis to reach the given point number
	ll moves[4] = { 0 };

	// distribute the distance along the 4 directions in counter clock wise
	// order: -x, -y, +x, +y
	ll fullMoves = difference / (ringDimension - 1);
	int i = 0;
	for (; i < fullMoves; ++i)
	{
		moves[i] = ringDimension - 1;
	}
	moves[i] = difference % (ringDimension - 1);
	
	// apply the movement to the ring point to get the requested point
	ringPoint.x -= moves[0];
	ringPoint.y -= moves[1];
	ringPoint.x += moves[2];
	ringPoint.y += moves[3];

	ringPoint.toNormalSpace(gridSize);
	return ringPoint;
}