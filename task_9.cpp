#include <iostream>
#include "Maze.h"
#include "MTreeNode.h"

using namespace std;

int main()
{
	Maze* maze = new Maze(5, 5);

	int result[6][6];
	auto tree = MTreeNode::beginTree(0, 0);
	auto iterate = tree;

	maze->makeConnection(0, 0, 0, 1);
	for (int i = 0; i < maze->n; i++) {
		for (int j = 0; j < maze->m; j++) {
			if (i == j) {
				for (int n = i; n < maze->n - 1; n++) {
					maze->makeConnection(n, j, n + 1, j);
				}
				for (int m = j; m < maze->m - 1; m++) {
					maze->makeConnection(i, m, i, m + 1);
				}
				maze->makeConnection(i - 1, j, i, j);
			}
		}
	}
	maze->makeConnection(maze->n - 2, maze->m - 1, maze->n - 1, maze->m - 1);
	maze->printMaze();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == j) {
				auto prev = iterate;
				result[i][j] = iterate->distance();
				for (int m = j + 1; m < 6; m++) {
					iterate->addChild(i, m);
					iterate = iterate->hasChild(i, m);
					result[i][m] = iterate->distance();
				}
				iterate = prev;
				for (int n = i + 1; n < 6; n++) {
					iterate->addChild(n, j);
					iterate = iterate->hasChild(n, j);
					result[n][j] = iterate->distance();
				}
				iterate = prev;
				iterate = iterate->hasChild(i, j + 1);
				iterate->addChild(i + 1, j + 1);
				result[i + 1][j + 1] = iterate->distance();
				iterate = iterate->hasChild(i + 1, j + 1);
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++) {
			cout << result[i][k] << " ";
		}
		cout << endl;
	}
}