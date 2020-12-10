#include "MTreeNode.h"
#include <iostream>
using namespace std;

int MTreeNode::i() const {
	return this->m_i;
}

int MTreeNode::j() const {
	return this->m_j;
}

const MTreeNode* MTreeNode::parent() const {
	return this->m_parent;
}

const MTreeNode* MTreeNode::child(int i) const {
	return this->m_children[i];
}

int MTreeNode::distance() const {
	return this->m_distance;
}

int MTreeNode::childCount() const {
	int count = 0;
	for (int i = 0; i < 2; i++) {
		if (this->m_children[i] != nullptr) {
			count++;
		}
	}
	return count;
}

bool MTreeNode::addChild(int i, int j) {
	if (this->i() == i && this->j() + 1 == j || this->i() + 1 == i && this->j() == j) {
		auto new_children = new MTreeNode(this);
		new_children->m_i = i;
		new_children->m_j = j;
		new_children->m_distance = this->distance() + 1;
		if (this->m_children[0] != nullptr) {
			this->m_children[1] = new_children;
		}
		else {
			this->m_children[0] = new_children;
		}
		return true;
	}
	return false;
}

MTreeNode* MTreeNode::hasChild(int i, int j) {
	for (auto k = this->m_children; k; k++) {
		int m = 0;
		if (k[m]->i() == i && k[m]->j() == j) {
			return k[m];
		}
		m++;
	}
	return nullptr;
}

MTreeNode* MTreeNode::beginTree(int i, int j) {
	auto tree = new MTreeNode(nullptr);
	tree->m_i = i;
	tree->m_j = j;
	tree->m_distance = 0;
	return tree;
}