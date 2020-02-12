#pragma once
class Coordinates
{
public:
	//Type to indicate possible values of coordinate
	typedef unsigned int size_type;

	// Constructors and destructor
	Coordinates();
	Coordinates(size_type row, size_type col);
	~Coordinates();

	// Accessors
	size_type& row();
	const size_type& row() const;
	size_type& col();
	const size_type& col() const;

private:
	size_type m_row;
	size_type m_col;
};

