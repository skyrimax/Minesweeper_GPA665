#pragma once

#include "Vector.h"

class Minefield;

class Box
{
public:
	enum class Marking {
		Blank,
		Flag,
		QuestionMark
	};

	Box();
	Box(Minefield* minefield, int value = 0, bool exposed = false, Marking marked = Marking::Blank);
	~Box();

	bool exposed();
	int value();
	void setValue(int value);
	Marking marked();

	void expose();
	void mark();

	void addNeighbors(Box* neighbor);
	void clearNeighbors();

	void initialiseMines();

private:
	int m_value;
	bool m_exposed;
	Marking m_marked;

	Minefield* m_minefield;

	Vector<Box*> m_neighbors;
};

