#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include "Point.h"
#include "Spiral.h"

int main()
{
	std::ifstream inputFile("Input.txt");
	std::string line;

	long long gridSize = 0;
	long long firstArgument = 0;
	long long secondArgument = 0;
	bool firstInput = false;
	while (std::getline(inputFile, line))
	{
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token.empty() || token == "//") continue;

		if (!firstInput)
		{
			gridSize = std::stoll(token);
			firstInput = true;
		}
		else
		{
			Spiral spiral(gridSize);
			std::cout << gridSize << std::endl;

			firstArgument = std::stoll(token);
			if (iss >> token)
			{
				secondArgument = std::stoll(token);

				std::cout << firstArgument << " " << secondArgument << std::endl;
				long long result = spiral.getNumberOfPoint(Point(firstArgument, secondArgument));
				std::cout << result << std::endl;
				std::cout << std::endl;
			}
			else
			{
				std::cout << firstArgument << std::endl;
				Point result = spiral.getPointOfNumber(firstArgument);
				std::cout << result.x << " " << result.y << std::endl;
				std::cout << std::endl;
			}
			firstInput = false;
		}

	}
	std::cin.get();
}