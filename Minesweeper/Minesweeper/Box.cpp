#include "Box.h"



Box::Box()
{
	m_value = 0;
	m_exposed = false;
}

Box::Box(int value)
{
	m_value = value;
	m_exposed = false;
}


Box::~Box()
{
}

bool Box::exposed()
{
	return exposed();
}

int Box::value()
{
	return m_value;
}

void Box::expose()
{
	if (m_exposed == false) {
		m_exposed = true;

		for (int i; i < m_neighbors.size(); ++i) {
			m_neighbors[i]->expose();
		}
	}
}

void Box::addNeighbors(Box * neighbor)
{
	m_neighbors.push_back(neighbor);
}
