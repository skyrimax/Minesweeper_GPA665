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
	void addNeighbors(Box* neighbor);

private:
	int m_value;
	bool m_exposed;

	Vector<Box*> m_neighbors;
};

