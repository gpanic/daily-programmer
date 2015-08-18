#include "ChainFinder.h"

ChainFinder::ChainFinder(std::vector<std::vector<bool>> grid) : grid(std::move(grid))
{
	gridHeight = this->grid.size();
	if (!this->grid.empty())
	{
		gridWidth = this->grid[0].size();
	}
}

// Processes the grid node by node. When it finds an 'x' it processes all the neighbours
// until the full chain has been marked as visited.
int ChainFinder::GetNumberOfChains()
{
	if (gridHeight <= 0) return -1;
	int chains = 0;
	for (int y = 0; y < gridHeight; ++y)
	{
		for (int x = 0; x < gridWidth; ++x)
		{
			std::vector<bool>::reference element = grid[y][x];
			if (!element) continue;
			element = false;

			++chains;
			// add the first node of a chain to the queue
			queue.push(std::make_pair(x, y));

			// keep processing neighbours until the queue is empty
			while (!queue.empty())
			{
				std::pair<int, int> node = queue.front();
				queue.pop();

				for (int i = -1; i <= 1; i += 2)
				{
					ProcessNeighbour(node.first + i, node.second);
					ProcessNeighbour(node.first, node.second + i);
				}
			}
		}
	}
	return chains;
}

void ChainFinder::ProcessNeighbour(const int& x, const int& y)
{
	if (y < 0 || y >= gridHeight || x < 0 || x >= gridWidth) return;
	std::vector<bool>::reference neighbour = grid[y][x];
	if (neighbour)
	{
		// mark neighbours as visited before adding to queue to prevent
		// the same nodes being processed multiple times
		neighbour = false;
		queue.push(std::make_pair(x, y));
	}
}