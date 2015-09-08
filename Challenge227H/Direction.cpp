#include "Direction.h"

Direction::Direction(Name name, int moveX, int moveY) : name(name), moveX(moveX), moveY(moveY) {}

const Direction Direction::all[8] = {
	{ N, 0 , -1 },
	{ NE, 1, -1 },
	{ E, 1 , 0 },
	{ SE, 1 , 1 },
	{ S, 0 , 1 },
	{ SW, -1 , 1 },
	{ W, -1 , 0 },
	{ NW, -1 , -1 },
};

bool Direction::Opposite(const Direction& dir1, const Direction& dir2)
{
	return dir1.moveX + dir2.moveX == 0 && dir1.moveY + dir2.moveY == 0;
}