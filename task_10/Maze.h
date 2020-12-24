#pragma once
#include "MCell.h"

class Maze
{
public:
	int n = 0;
	int m = 0;

	Maze(int n, int m);
	const MCell& cell(int i, int j) const;
	bool hasConnection(int i1, int j1, int i2, int j2) const;
	bool makeConnection(int i1, int j1, int i2, int j2) const;
	bool removeConnection(int i1, int j1, int i2, int j2) const;
	void printMaze() const;

	~Maze() {
		delete[] m_field;
	}
private:
	MCell* m_field;
};