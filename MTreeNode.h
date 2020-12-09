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

	~MTreeNode() {
		delete[] m_children;
	}
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

//Опишите класс вершины дерева MTreeNode :
//-поля координаты клетки поля лабиринта int m_i, m_j
//- поле указателя на родителя вершины MTreeNode * m_parent
//- поле массива указателей на потомков вершины MTreeNode * m_children
//- поле int m_distance расстояния
//- геттер int i() const
//- геттер int j() const
//- геттер const MTreeNode * parent() const
//- геттер const MTreeNode * child(int i) const
//- геттер int distance() const
//- метод int childCount() const
//- метод bool addChild(int i, int j)
//- метод MTreeNode * hasChild(int i, int j) //Так и задумано.
//- статический метод MTreeNode * beginTree(int i, int j)
//- приватный конструктор MTreeNode(MTreeNode * parent)
//- память потомков обслуживает родитель