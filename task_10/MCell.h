#pragma once
class MCell
{
public:
	bool getDown() const;
	bool getRight() const;
private:
	bool m_down = 0;
	bool m_right = 0;
	MCell() {}
	friend class Maze;
};