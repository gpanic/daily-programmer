#pragma once
#include <vector>
#include <iostream>
#include <queue>


// Counts the number of continuous 'x' chains in the input file.
class ChainFinder
{
public:
	ChainFinder(std::vector<std::vector<bool>> grid);
	int GetNumberOfChains();
private:
	std::vector<bool>::size_type gridHeight = 0;
	std::vector<bool>::size_type gridWidth = 0;
	std::vector<std::vector<bool>> grid;
	std::queue<std::pair<int, int>> queue;

	void ProcessNeighbour(const int& x, const int& y);
};