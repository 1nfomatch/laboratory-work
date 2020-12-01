#include <iostream>
#include "Maze.h"

using namespace std;

int main()
{
	Maze* maze = new Maze(5, 5);
	maze->makeConnection(0, 1, 0, 0);
	for (int i = 0; i < maze->n; i++) {
		for (int j = 0; j < maze->m; j++) {
			if (i == j) {
				maze->makeConnection(i, j, i, j + 1);
			}

			if (i + 1 == j) {
				maze->makeConnection(i, j, i + 1, j);
			}
		}
	}
	maze->printMaze();
}