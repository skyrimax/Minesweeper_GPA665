#include "Box.h"
#include "Minefield.h"


Box::Box()
{
	m_value = 0;
	m_exposed = false;
	m_marked = Marking::Blank;
	m_minefield = nullptr;
}

Box::Box(Minefield* minefield, int value, bool exposed, Marking marked)
{
	m_value = value;
	m_exposed = exposed;
	m_marked = marked;
	m_minefield = minefield;
}


Box::~Box()
{
}

bool Box::exposed()
{
	return m_exposed;
}

int Box::value()
{
	return m_value;
}

void Box::setValue(int value)
{
	m_value = value;
}

Box::Marking Box::marked()
{
	return m_marked;
}

void Box::expose()
{
	if (!m_exposed && m_marked == Marking::Blank) {
		m_exposed = true;
		m_minefield->boxExplored();

		if (m_value == 0) {
			for (int i; i < m_neighbors.size(); ++i) {
				m_neighbors[i]->expose();
			}
		}
	}
}

void Box::mark()
{
	if (m_marked == Marking::Blank) {
		m_marked = Marking::Flag;
	}
	else if (m_marked == Marking::Flag) {
		m_marked = Marking::QuestionMark;
	}
	else {
		m_marked = Marking::Blank;
	}
}

void Box::addNeighbors(Box * neighbor)
{
	m_neighbors.push_back(neighbor);
}

void Box::clearNeighbors()
{
	m_neighbors.clear();
}

void Box::initialiseMines()
{
	m_value = 0;

	for (int i = 0; i < m_neighbors.size(); ++i) {
		if (m_neighbors[i]->m_value = -1) {
			++m_value;
		}
	}
}
