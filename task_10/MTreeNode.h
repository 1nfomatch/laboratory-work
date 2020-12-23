#pragma once
class MTreeNode
{
public:
	int i() const;
	int j() const;
	const MTreeNode* parent() const;
	const MTreeNode* child(int i) const;
	int distance() const;

	int childCount() const;
	bool addChild(int i, int j);
	MTreeNode* hasChild(int i, int j);
	static MTreeNode* beginTree(int i, int j);

	/*~MTreeNode() {
		delete[] m_children;
	}*/
private:
	int m_i;
	int m_j;

	MTreeNode* m_parent;
	MTreeNode* m_children[2];
	int m_distance;

	MTreeNode(MTreeNode* parent) {
		this->m_parent = parent;
	}
};