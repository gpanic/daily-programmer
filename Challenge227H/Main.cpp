#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "AdjMatrixGenerator.h"

int main()
{
	std::ifstream inputFile("Input.txt");
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::istringstream iss(line);

		int lines = 0;
		iss >> lines;

		int width = 0;
		std::vector<std::vector<char>> diagram;
		while (std::getline(inputFile, line) && !line.empty())
		{
			std::vector<char> diagramLine(line.begin(), line.end());
			width = std::max(width, static_cast<int>(diagramLine.size()));
			diagram.push_back(diagramLine);

			std::cout << line  << std::endl;
		}

		for (std::vector<char>& diagramLine : diagram)
		{
			diagramLine.insert(diagramLine.end(), width - diagramLine.size(), ' ');
		}

		AdjMatrixGenerator generator(std::move(diagram));
		std::vector<std::vector<bool>> matrix = generator.GetAdjMatrix();

		std::cout << std::endl;
		for (auto i : matrix)
		{
			for (auto j : i)
			{
				std::cout << j;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::cin.get();
}