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
	MCell& secondCell = m_field[i2 * n + j2];

	if (i1 == i2 && j1 + 1 == j2) {
		firstCell.m_right = true;
		return true;
	}
	else if (i1 == i2 && j1 == j2 + 1) {
		secondCell.m_right = true;
		return true;
	}

	if (i1 + 1 == i2 && j1 == j2) {
		firstCell.m_down = true;
		return true;
	}
	else if (i1 == i2 + 1 && j1 == j2) {
		secondCell.m_down = true;
		return true;
	}
	return false;
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2) const {
	MCell& firstCell = m_field[i1 * n + j1];
	MCell& secondCell = m_field[i2 * n + j2];
	if (i1 == i2 && j1 + 1 == j2) {
		firstCell.m_right = false;
		return false;
	}
	else if (i1 == i2 && j1 == j2 + 1) {
		secondCell.m_right = false;
		return false;
	}

	if (i1 + 1 == i2 && j1 == j2) {
		firstCell.m_down = false;
		return false;
	}
	else if (i1 == i2 + 1 && j1 == j2) {
		secondCell.m_down = false;
		return false;
	}
	return true;
}

void Maze::printMaze() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i == m - 1 || j == n - 1) && i != m - 2) {
                cout << '0'; continue;
            };
            auto fromLeft = hasConnection(i, j - 1, i, j);
            auto fromAbove = hasConnection(i - 1, j, i, j);
            auto toRight = hasConnection(i, j, i, j + 1);
            auto toDown = hasConnection(i, j, i + 1, j);
            if (fromLeft && fromAbove && toRight && toDown) // ┼
                cout << char(197);
            else {
                if (fromLeft && toRight && toDown) // ┬
                    cout << char(194);
                else {
                    if (fromAbove && toDown && toRight) // ├
                        cout << char(195);
                    else {
                        if (fromLeft && fromAbove && toRight) // ┴
                            cout << char(193);
                        else {
                            if (fromAbove && toRight)   //└
                                cout << char(192);
                            else {
                                if (fromLeft && toDown) //┐
                                    cout << char(191);
                                else {
                                    if (toRight && toDown)
                                        cout << char(218);
									else {
										if (fromAbove)  //  │
											cout << char(179);
										else {
											if (fromLeft) // ─
												cout << char(196);
											else cout << '0';
										}
									}
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << endl;
    }
}