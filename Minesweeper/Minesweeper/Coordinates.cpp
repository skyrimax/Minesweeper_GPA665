#include "Coordinates.h"



Coordinates::Coordinates()
{
	m_col = 0;
	m_row = 0;
}

Coordinates::Coordinates(size_type row, size_type col)
{
	m_col = col;
	m_row = row;
}


Coordinates::~Coordinates()
{
}

Coordinates::size_type & Coordinates::row()
{
	return m_row;
}

const Coordinates::size_type & Coordinates::row() const
{
	return m_row;
}

Coordinates::size_type & Coordinates::col()
{
	return m_col;
}

const Coordinates::size_type & Coordinates::col() const
{
	return m_col;
}
