#pragma once
class MCell
{
public:
	bool getDown() const {
		return m_down;
	}

	bool getRight() const {
		return m_right;
	}
private:
	bool m_down = 0;
	bool m_right = 0;
	MCell() {}
	friend class Maze;
};