#include "Maze.h"
#include "MCell.h"
#include "MTreeNode.h"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

size_t mazeSize;

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<int> randomStep(-1, 1);
std::uniform_int_distribution<int> position(0, mazeSize);
std::uniform_int_distribution<int> spawnDirection(0, 3);

void buildFullMaze(Maze& iMaze, MTreeNode& tree)
{
	int** vertexWeight = new int*[mazeSize + 1];
	for (int i = 0; i < mazeSize; i++) {
		vertexWeight[i] = new int[mazeSize + 1];
	}
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
	int max = 0;
	for (auto i = 0; i < mazeSize; i++)
	{
		for (auto k = 0; k < mazeSize; k++)
		{
			if (vertexWeight[i][k] < 10)
				cout << vertexWeight[i][k] << "   ";
			else if (vertexWeight[i][k] > 99) {
				cout << vertexWeight[i][k] << " ";
			}
			else if (vertexWeight[i][k] < 100 || vertexWeight[i][k] > 9)
				cout << vertexWeight[i][k] << "  ";
			sum += vertexWeight[i][k];
			if (vertexWeight[i][k] >= max) {
				max = vertexWeight[i][k];
			}
		}
		cout << endl;
	}
	cout << "Average weight of vertices: " << sum / (mazeSize * mazeSize) << endl;
	cout << "Max weight of verices: " << max << endl;
}

int main()
{
	cout << "Enter the size of the maze: ";
	cin >> mazeSize;
	Maze maze(mazeSize, mazeSize);
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
		i = mazeSize;
		j = position(rng);
		break;
	case 2:
		j = 0;
		i = position(rng);
		break;
	case 3:
		j = mazeSize;
		i = position(rng);
		break;
	}
	MTreeNode* tree = MTreeNode::beginTree(i, j);
	buildFullMaze(maze, *tree);
	maze.printMaze();
}