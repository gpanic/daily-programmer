#pragma once

typedef long long ll;

class Point
{
public:
	Point(ll x, ll y);
	ll x;
	ll y;

	// used to convert from the normal grid which starts at (1,1) at the top
	// left corner to a zero grid where the center is (0,0) for easier math
	void toZeroSpace(ll gridSize);
	void toNormalSpace(ll gridSize);
};


