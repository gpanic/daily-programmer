#pragma once

class Direction
{
public:
	enum Name { N, NE, E, SE, S, SW, W, NW };
	const static Direction all[8];

	static bool Opposite(const Direction&, const Direction&);

	Name name;
	int moveX;
	int moveY;

	Direction(Name, int, int);
	
};