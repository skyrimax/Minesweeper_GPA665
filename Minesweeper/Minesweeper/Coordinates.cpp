#include "Coordinates.h"


// Default cunstructor
Coordinates::Coordinates()
{
	// Initializing internal variables to coherent defaults values
	m_col = 0;
	m_row = 0;
}

// Cunstructor enabling the passing of internal values at declaration
Coordinates::Coordinates(size_type row, size_type col)
{
	// Assigning passed parameters to internal values
	m_col = col;
	m_row = row;
}


Coordinates::~Coordinates()
{
}

// Accessor returning a modifiable reference to the row component of coordinate
Coordinates::size_type & Coordinates::row()
{
	return m_row;
}

// Accessor returning a non-modifiable reference to the row component of coordinate
const Coordinates::size_type & Coordinates::row() const
{
	return m_row;
}

// Accessor returning a modifiable reference to the column component of coordinate
Coordinates::size_type & Coordinates::col()
{
	return m_col;
}

// Accessor returning a non-modifiable reference to the column component of coordinate
const Coordinates::size_type & Coordinates::col() const
{
	return m_col;
}
