#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <set>

#include "Node.h"
#include "Direction.h"


// Generates an adjacency matrix for a graph.
// Nodes are marked with a-z, edges (paths) with -, \ and |, connectors with #.
class AdjMatrixGenerator
{
public:
	AdjMatrixGenerator(std::vector<std::vector<char>> diagram);
	std::vector<std::vector<bool>> GetAdjMatrix();
private:
	std::vector<std::vector<char>> diagram;
	std::vector<std::vector<bool>> matrix;
	int diagramWidth = 0;
	int diagramHeight = 0;
	std::queue<std::pair<Node, Direction>> queue;
	std::set<char> explored;

	void ExploreNeightbours(const Node&, const Direction&);
	std::vector<std::vector<bool>> ExtractSubMatrix(int);
	bool IsVertex(const Node&);
	bool IsConnector(const Node&);
	bool IsPath(const Node&, const Node&);
	bool IsInBounds(const Node&);
	bool HasBeenExplored(const Node&);
	bool EdgeAdded(const Node&, const Node&);
};

Node operator+(const Node&, const Direction&);