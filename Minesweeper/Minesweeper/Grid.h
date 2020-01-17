#pragma once

#include"Vector.h"

template <class T>
class Grid
{
public:
	//Type to indicate size of container
	typedef unsigned int size_type;

	Grid();
	Grid(size_type nbRows, size_type nbCols);
	Grid(size_type nbRows, size_type nbCols, T& val);
	Grid(const Grid<T>& grid);
	Grid(Grid<T>&& grid);
	~Grid();

	//Assignement operator overloading
	Grid<T>& operator=(const Grid<T>& grid);
	Grid<T>& operator=(Grid<T>&& grid);

	//Capacity related member functions
	Vector<size_type> size();
};

