#pragma once
class Coordinates
{
public:
	//Type to indicate size of container
	typedef unsigned int size_type;

	Coordinates();
	Coordinates(size_type row, size_type col);
	~Coordinates();

	size_type& row();
	const size_type& row() const;
	size_type& col();
	const size_type& col() const;

private:
	size_type m_row;
	size_type m_col;
};

