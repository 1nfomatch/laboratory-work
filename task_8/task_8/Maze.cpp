#include "Maze.h"
#include <iostream>
using namespace std;

Maze::Maze(int n, int m) {
	m_field = new MCell[n * m];
	this->n = n;
	this->m = m;
}

const MCell& Maze::cell(int i, int j) const {
	if (i > n - 1 || i < 0 || j > m - 1 || j < 0) return *(new MCell);
	return m_field[i * n + j];
}

bool Maze::hasConnection(int i1, int j1, int i2, int j2) const {
	MCell firstCell = cell(i1, j1);
	if (i1 == i2 && j1 + 1 == j2 && firstCell.getRight()
		|| i1 + 1 == i2 && j1 == j2 && firstCell.getDown()) {
		return true;
	}
	return false;
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2) const {
	MCell& firstCell = m_field[i1 * n + j1];
	if (i1 == i2 && j1 + 1 == j2) {
		firstCell.m_right = true;
		return true;
	}

	if (i1 + 1 == i2 && j1 == j2) {
		firstCell.m_down = true;
		return true;
	}
	return false;
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2) const {
	MCell firstCell = m_field[i1 * n + j1];
	if (i1 == i2 && j1 + 1 == j2) {
		firstCell.m_right = false;
		return false;
	}

	if (i1 + 1 == i2 && j1 == j2) {
		firstCell.m_down = false;
		return false;
	}
	return true;
}

void Maze::printMaze() const {
	for (int i = 0; i < n; i++) {
		auto newMaze = new char[n];
		for (int i = 0; i < n; i++) {
			newMaze[i] = '0';
		}
		for (int j = 0; j < m; j++) {
			if (hasConnection(i - 1, j, i, j) || hasConnection(i, j, i, j + 1)) {
				if (cell(i - 1, j).m_down && cell(i, j).m_right) {
					*newMaze = char(192);
				}
				else {
					if (cell(i - 1, j).m_down && i == n - 1 && j == m - 1) {
						*newMaze = char(192);
					}
					else {
						if (cell(i - 1, j).m_down)
							*newMaze = char(179);
					}
				}

				if (cell(i, j).m_right && cell(i, j + 1).m_down) {
					*(newMaze + 1) = char(191);
				}

				if (cell(i, j).m_right && !cell(i, j + 1).m_down) {
					*(newMaze + 1) = char(196);
				}
			}

			if (*newMaze != '0') {
				cout << *newMaze;
			}
			else {
				cout << "0";
			}
			newMaze++;
		}
		cout << endl;
	}
}