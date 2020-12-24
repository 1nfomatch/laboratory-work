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
	if (this->hasChild(i, j) == nullptr) {
		auto node = new MTreeNode(this);
		node->m_i = i;
		node->m_j = j;
		node->m_distance = this->distance() + 1;
		this->m_children[this->childCount()] = node;
		return true;
	}
	return false;
}

MTreeNode* MTreeNode::hasChild(int i, int j) {
	for (int x = 0; x < 2; x++) {
		if (this->m_children[x] != NULL) {
			auto m_i = m_children[x]->m_i;
			auto m_j = m_children[x]->m_j;
			if (m_i == i && m_j == j)
				return m_children[x];
		}
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