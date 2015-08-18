#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "ChainFinder.h"

int main()
{
	std::ifstream inputFile("Input.txt");
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::istringstream iss(line);

		int gridHeight = 0;
		iss >> gridHeight;

		int gridWidth = 0;
		iss >> gridWidth;

		std::vector<std::vector<bool>> grid;
		while (std::getline(inputFile, line) && !line.empty())
		{
			std::vector<bool> gridLine;
			for (char& c : line)
			{
				gridLine.push_back(c == 'x');
			}
			grid.push_back(gridLine);
		}
		ChainFinder cd(std::move(grid));
		std::cout << cd.GetNumberOfChains() << std::endl;
	}
	std::cin.get();
}