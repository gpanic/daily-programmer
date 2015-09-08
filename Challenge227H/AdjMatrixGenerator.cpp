#include "AdjMatrixGenerator.h"

AdjMatrixGenerator::AdjMatrixGenerator(std::vector<std::vector<char>> diagram) : diagram(std::move(diagram)), matrix(26, std::vector<bool>(26, 0))
{
	diagramHeight = this->diagram.size();
	if (diagramHeight > 0)
	{
		diagramWidth = this->diagram[0].size();
	}
}

// Uses a queue to explore the graph
std::vector<std::vector<bool>> AdjMatrixGenerator::GetAdjMatrix()
{
	for (int y = 0; y < diagramHeight; ++y)
	{
		for (int x = 0; x < diagramWidth; ++x)
		{
			Node node(x, y, diagram[y][x]);
			if (!IsVertex(node) || HasBeenExplored(node)) continue;
			queue.push(std::make_pair(node, Direction::all[4]));

			while (!queue.empty())
			{
				Node currentNode = queue.front().first;
				Direction fromDirection = queue.front().second;
				queue.pop();
				ExploreNeightbours(currentNode, fromDirection);
			}
		}
	}
	return ExtractSubMatrix(explored.size());
}


// Explores all connected nodes and adds them to the queue.
void AdjMatrixGenerator::ExploreNeightbours(const Node& node, const Direction& fromDirection)
{
	// check all 8 directions
	for (Direction direction : Direction::all)
	{
		Node next = node + direction;
		if (IsInBounds(next)) continue;
		next.value = diagram[next.y][next.x];

		// only follow paths, don't backtrack
		if (!IsPath(next, node) || Direction::Opposite(direction, fromDirection)) continue;

		// follow path until a vertex or connector is found
		while (!IsVertex(next) && !IsConnector(next))
		{
			next = next + direction;
			next.value = diagram[next.y][next.x];
		}

		if (IsVertex(next))
		{
			if (EdgeAdded(node, next)) continue;

			// mark edge on the adjacency matrix
			matrix[next.value - 'a'][node.value - 'a'] = true;
			matrix[node.value - 'a'][next.value - 'a'] = true;
		}
		else if (IsConnector(next))
		{
			// rename the connector with the name of the previous node,
			// so that an edge can be added
			next.value = node.value;
		}
		queue.push(std::make_pair(next, direction));
	}

	// mark node as explored
	explored.insert(node.value);
}

std::vector<std::vector<bool>> AdjMatrixGenerator::ExtractSubMatrix(int subDimension)
{
	std::vector<std::vector<bool>> subMatrix;
	for (int i = 0; i < subDimension; ++i)
	{
		std::vector<bool> line(matrix[i].begin(), matrix[i].begin() + subDimension);
		subMatrix.push_back(line);
	}
	return subMatrix;
}

bool AdjMatrixGenerator::IsVertex(const Node& node)
{
	return node.value >= 'a' && node.value <= 'z';
}

bool AdjMatrixGenerator::IsConnector(const Node& node)
{
	return node.value == '#';
}

// Checks if the node is a path and if the direction of the character is correct.
bool AdjMatrixGenerator::IsPath(const Node& node, const Node& fromNode)
{
	int deltaX = node.x - fromNode.x;
	int deltaY = node.y - fromNode.y;
	for (Direction d : Direction::all)
	{
		if (d.moveX == deltaX && d.moveY == deltaY)
		{
			return (node.value == '|' && (d.name == Direction::N || d.name == Direction::S)) ||
				(node.value == '/' && (d.name == Direction::NE || d.name == Direction::SW)) ||
				(node.value == '-' && (d.name == Direction::E || d.name == Direction::W)) ||
				(node.value == '\\' && (d.name == Direction::NW || d.name == Direction::SE));
		}
	}
	return false;
}

bool AdjMatrixGenerator::IsInBounds(const Node& node)
{
	return node.x < 0 || node.x >= diagramWidth || node.y < 0 || node.y >= diagramHeight;
}

bool AdjMatrixGenerator::HasBeenExplored(const Node& node)
{
	return explored.find(node.value) != explored.end();
}

bool AdjMatrixGenerator::EdgeAdded(const Node& fromNode, const Node& toNode)
{
	return matrix[fromNode.value - 'a'][toNode.value - 'a'];
}


Node operator+(const Node& node, const Direction& dir)
{
	Node next = node;
	next.x += dir.moveX;
	next.y += dir.moveY;
	return next;
}