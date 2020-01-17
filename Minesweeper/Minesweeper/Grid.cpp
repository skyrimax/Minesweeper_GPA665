#include "Grid.h"

#include<utility>

template<class T>
Grid<T>::Grid()
{
	m_nbRows = 1;
	m_nbRows = 1;
}

template<class T>
Grid<T>::Grid(size_type nbRows, size_type nbCols)
{
	m_nbRows = nbRows;
	m_nbCols = nbCols;
	m_data = Vector<T>(m_nbRows*m_nbCols);
}

template<class T>
Grid<T>::Grid(size_type nbRows, size_type nbCols, const T & val)
{
	m_nbRows = nbRows;
	m_nbCols = nbCols;
	m_data = Vector<T>(m_nbRows*m_nbCols, val);
}

template<class T>
Grid<T>::Grid(const Grid<T>& grid)
{
	m_nbRows = grid.m_nbRows;
	m_nbCols = grid.m_nbCols;
	m_data = grid.m_data;
}

template<class T>
Grid<T>::Grid(Grid<T>&& grid)
{
	m_nbRows = grid.m_nbRows;
	m_nbCols = grid.m_nbCols;
	m_data = std::move(grid.m_data);
}

template<class T>
Grid<T>::~Grid()
{
}

template<class T>
Grid<T>& Grid<T>::operator=(const Grid<T>& grid)
{
	m_nbRows = grid.m_nbRows;
	m_nbCols = grid.m_nbCols;
	m_data = grid.m_data;

	return *this;
}

template<class T>
Grid<T>& Grid<T>::operator=(Grid<T>&& grid)
{
	m_nbRows = grid.m_nbRows;
	m_nbCols = grid.m_nbCols;
	m_data = std::move(grid.m_data);

	return *this;
}

template<class T>
 Vector<typename Grid<T>::size_type>& Grid<T>::size()
{
	Vector<size_type> sizeToReturn(2);

	sizeToReturn[0] = m_nbRows;
	sizeToReturn[1] = m_nbCols;

	return sizeToReturn;
}

template<class T>
void Grid<T>::resize(size_type nbRows, size_type nbCols)
{
	Vector<T>newArray(nbRows*nbCols);

	for (int i = 0; i < m_nbRows && i < nbRows; ++i) {
		for (int j - 0; j < m_nbCols && j < nbCols; ++j) {
			newArray[i*nbCols + j] = this(i, j);
		}
	}

	m_data.swap(newArray);

	m_nbRows = nbRows;
	m_nbCols - nbCols;
}

template<class T>
void Grid<T>::resize(size_type nbRows, size_type nbCols, T & val)
{
	Vector<T>newArray(nbRows*nbCols, val);

	for (int i = 0; i < m_nbRows && i < nbRows; ++i) {
		for (int j - 0; j < m_nbCols && j < nbCols; ++j) {
			newArray[i*nbCols + j] = this(i, j);
		}
	}

	m_data.swap(newArray);

	m_nbRows = nbRows;
	m_nbCols - nbCols;
}

template<class T>
bool Grid<T>::empty()
{
	return m_data.empty();
}

template<class T>
T & Grid<T>::operator()(size_type row, size_type col)
{
	return m_data[row*m_nbCols + col];
}

template<class T>
const T & Grid<T>::operator()(size_type row, size_type col) const
{
	return m_data[row*m_nbCols + col];
}

template<class T>
T & Grid<T>::at(size_type row, size_type col)
{
	if (row < m_nbRows && col < m_nbCols) {
		return m_data[row*m_nbCols + col];
	}
	else {
		return T();
	}
}

template<class T>
const T & Grid<T>::at(size_type row, size_type col) const
{
	if (row < m_nbRows && col < m_nbCols) {
		return m_data[row*m_nbCols + col];
	}
	else {
		return T();
	}
}

template<class T>
Grid<T&> Grid<T>::rows(size_type row, size_type n)
{
	Grid<T&>rowsToReturn(n, m_nbCols);

	for (int i = row; i < n; ++i) {
		for (int j = 0; j < m_nbCols; ++j) {
			rowsToReturn.m_data[i*m_nbCols + j] = m_data[i*m_nbCols + j];
		}
	}

	return rowsToReturn;
}

template<class T>
const Grid<T&> Grid<T>::rows(size_type row, size_type n) const
{
	Grid<T&>rowsToReturn(n, m_nbCols);

	for (int i = row; i < n; ++i) {
		for (int j = 0; j < m_nbCols; ++j) {
			rowsToReturn.m_data[i*m_nbCols + j] = m_data[i*m_nbCols + j];
		}
	}

	return rowsToReturn;
}

template<class T>
Vector<T&> Grid<T>::row(size_type row)
{
	Vector<T&>rowToReturn(m_nbCols);

	for (int i = 0; i < m_nbCols; ++i) {
		rowToReturn[i] = m_data[row*m_nbCols + i];
	}

	return rowToReturn;
}

template<class T>
const Vector<T&> Grid<T>::row(size_type row) const
{
	Vector<T&>rowToReturn(m_nbCols);

	for (int i = 0; i < m_nbCols; ++i) {
		rowToReturn[i] = m_data[row*m_nbCols + i];
	}

	return rowToReturn;
}

template<class T>
Grid<T&> Grid<T>::cols(size_type col, size_type n)
{
	Grid<T&>colsToReturn(m_nbRows, n);

	for (int i = 0; i < m_nbRows; ++i) {
		for (int i = 0; i < n; i++) {
			colsToReturn.m_data[i*m_nbRows + j] = m_data[i*m_nbRows + j];
		}
	}

	return colsToReturn;
}

template<class T>
const Grid<T&> Grid<T>::cols(size_type col, size_type n) const
{
	Grid<T&>colsToReturn(m_nbRows, n);

	for (int i = 0; i < m_nbRows; ++i) {
		for (int i = 0; i < n; i++) {
			colsToReturn.m_data[i*m_nbRows + j] = m_data[i*m_nbRows + j];
		}
	}

	return colsToReturn;
}

template<class T>
Vector<T&> Grid<T>::col(size_type col)
{
	Vector<T&> colToReturn(m_nbRows);

	for (int i = 0; i < m_nbRows; ++i) {
		colToReturn[i] = m_data[i*m_nbCols + col];
	}

	return colToReturn;
}

template<class T>
const Vector<T&> Grid<T>::col(size_type col) const
{
	Vector<T&> colToReturn(m_nbRows);

	for (int i = 0; i < m_nbRows; ++i) {
		colToReturn[i] = m_data[i*m_nbCols + col];
	}

	return colToReturn;
}

template<class T>
Grid<T&> Grid<T>::firstRowGrid()
{
	return rows(0);
}

template<class T>
const Grid<T&> Grid<T>::firstRowGrid() const
{
	return rows(0);
}

template<class T>
Vector<T&> Grid<T>::firstRowVector()
{
	return row(0);
}

template<class T>
const Vector<T&> Grid<T>::firstRowVector() const
{
	return row(0);
}

template<class T>
Grid<T&> Grid<T>::lastRowGrid()
{
	return rows(m_nbRows - 1);
}

template<class T>
const Grid<T&> Grid<T>::lastRowGrid() const
{
	return rows(m_nbRows - 1);
}

template<class T>
Vector<T&> Grid<T>::lastRowVector()
{
	return row(m_nbRows - 1);
}

template<class T>
const Vector<T&> Grid<T>::lastRowVector() const
{
	return row(m_nbRows - 1);
}

template<class T>
Grid<T&> Grid<T>::firstColGrid()
{
	return cols(0);
}

template<class T>
const Grid<T&> Grid<T>::firstColGrid() const
{
	return cols(0);
}

template<class T>
Vector<T&> Grid<T>::firstColVector()
{
	return col(0);
}

template<class T>
const Vector<T&> Grid<T>::firstColVector() const
{
	return col(0);
}

template<class T>
Grid<T&> Grid<T>::lastColGrid()
{
	return cols(m_nbCols-1);
}

template<class T>
const Grid<T&> Grid<T>::lastColGrid() const
{
	return cols(m_nbCols - 1);
}

template<class T>
Vector<T&> Grid<T>::lastColVector()
{
	return col(m_nbCols - 1);
}

template<class T>
const Vector<T&> Grid<T>::lastColVector() const
{
	return col(m_nbCols - 1);
}

template<class T>
Vector<T> Grid<T>::data()
{
	return m_data;
}

template<class T>
const Vector<T> Grid<T>::data() const
{
	return m_data;
}
