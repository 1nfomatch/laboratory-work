#include "Maze.h"
#include "MCell.h"
#include "MTreeNode.h"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

const int n = 15;
const int m = 15;

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<int> randomStep(-1, 1);
std::uniform_int_distribution<int> position(0, n);
std::uniform_int_distribution<int> spawnDirection(0, 3);

void buildFullMaze(Maze& iMaze, MTreeNode& tree) 
{
	int vertexWeight[n+1][m+1];
	int i = tree.i();
	int j = tree.j();
	auto cellsPassed = 0;

	vector<MTreeNode*> stack;
	MTreeNode& cell = tree;

	vertexWeight[i][j] = 0;
	int stepX = randomStep(rng);
	int stepY = randomStep(rng);
	stack.push_back(&tree);
	auto emptyAttempts = 0;

	while (true) {
		int attempts = 0;
		while (true) {
			if (attempts > 40) {
				if (emptyAttempts == 1500 || cellsPassed >= stack.size())
					break;
				i = stack[cellsPassed]->i();
				j = stack[cellsPassed]->j();
				cell = *stack[cellsPassed];
				attempts = 0;
				cellsPassed++;
				emptyAttempts++;

			}
			stepX = randomStep(rng);
			stepY = randomStep(rng);
			if (stepX + stepY == 1 || stepX + stepY == -1) {
				if (stepX + i >= 0 && stepY + j >= 0 && stepX + i < iMaze.n && stepY + j < iMaze.m)
				{
					auto permission = false;
					for (auto elem : stack) {
						if (elem->i() == stepX + i && elem->j() == stepY + j) {
							permission = true;
							break;
						}
					}
					if (!permission)
						break;
				}
				attempts++;
			}
		}
		if (emptyAttempts == 1500 || cellsPassed >= stack.size()) break;
		iMaze.makeConnection(i, j, i + stepX, j + stepY);
		i = i + stepX;
		j = j + stepY;
		cell.addChild(i, j);
		vertexWeight[i][j] = cell.distance();
		stack.push_back(cell.hasChild(i, j));
		cell = *cell.hasChild(i, j);
	}

	int sum = 0;
	for (auto i = 0; i < n; i++)
	{
		for (auto k = 0; k < m; k++)
		{
			if (vertexWeight[i][k] < 10)
				cout << vertexWeight[i][k] << "   ";
			else if (vertexWeight[i][k] > 99) {
				cout << vertexWeight[i][k] << " ";
			}
			else if (vertexWeight[i][k] < 100 || vertexWeight[i][k] > 9)
				cout << vertexWeight[i][k] << "  ";
			sum += vertexWeight[i][k];
		}
		cout << endl;
	}
	cout << "Average weight of vertices: " << sum / (n * m) << endl;
}

int main()
{
	Maze maze(n, m);
	int i = 0;
	int j = 0;
	int startDirection = spawnDirection(rng);
	switch (startDirection)
	{
	case 0:
		i = 0;
		j = position(rng);
		break;
	case 1:
		i = n;
		j = position(rng);
		break;
	case 2:
		j = 0;
		i = position(rng);
		break;
	case 3:
		j = m;
		i = position(rng);
		break;
	}
	MTreeNode* tree = MTreeNode::beginTree(i, j);
	buildFullMaze(maze, *tree);
	maze.printMaze();
}