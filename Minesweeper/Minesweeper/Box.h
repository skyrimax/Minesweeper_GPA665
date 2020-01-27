#pragma once

#include "Vector.h"

class Box
{
public:
	Box();
	Box(int value);
	~Box();

	bool exposed();
	int value();

	void expose();
	void mark();
	void addNeighbors(Box* neighbor);

private:
	int m_value;
	bool m_exposed;
	bool m_marked;

	Vector<Box*> m_neighbors;
};

