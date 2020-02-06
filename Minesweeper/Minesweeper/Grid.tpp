#include "Grid.h"

#pragma once

#include<utility>
#include<stdexcept>

template<class T>
Grid<T>::Grid()
{
	m_nbRows = 1;
	m_nbRows = 1;

	m_data = new Vector<Vector<T>*>;
	m_data->at(0) = new Vector<T>;
}

template<class T>
Grid<T>::Grid(size_type nbRows, size_type nbCols)
{
	m_nbRows = nbRows;
	m_nbCols = nbCols;

	m_data=new Vector<Vector<T>*>(nbRows);

	for (int i = 0; i < nbRows; ++i) {
		m_data->at(i) = new Vector<T>(nbCols);
	}
}

template<class T>
Grid<T>::Grid(size_type nbRows, size_type nbCols, const T & val)
{
	m_nbRows = nbRows;
	m_nbCols = nbCols;

	m_data = new Vector<Vector<T*>>(nbRows);

	for (int i = 0; i < nbRows; ++i) {
		m_data->at(i) = new Vector<T*>(nbCols, val);
	}
}

template<class T>
Grid<T>::Grid(const Grid<T>& grid)
{
	m_nbRows = grid.m_nbRows;
	m_nbCols = grid.m_nbCols;

	m_data = new Vector<Vector<T*>>(m_nbRows);

	for (int i = 0; i < m_nbRows; ++i) {
		m_data->at(i) = new Vector<T>;

		for (int i; i < m_nbCols; ++i) {
			at(i, j) = grid.at(i, j);
		}
	}
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
	for (int i = 0; i < m_data->size(); ++i) {
		delete m_data->at(i);
	}

	delete m_data;
}

template<class T>
Grid<T>& Grid<T>::operator=(const Grid<T>& grid)
{
	for (int i = grid.m_nbRows; i < m_nbRows; ++i) {
		delete m_data->at(i);
	}

	m_data->resize(grid.m_nbRows);
	m_nbRows = grid.m_nbRows;

	m_nbCols = grid.m_nbCols;

	for (int i = 0; i < m_nbRows; ++i) {
		m_data->at(i)->resize(m_nbCols);

		for (int j = 0; i < m_nbCols; ++i) {
			at(i, j) = grid.at(i, j);
		}
	}
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
 Vector<typename Grid<T>::size_type> Grid<T>::size()
{
	Vector<size_type> sizeToReturn=Vector<size_type>(2);

	sizeToReturn[0] = m_nbRows;
	sizeToReturn[1] = m_nbCols;

	return sizeToReturn;
}

template<class T>
void Grid<T>::resize(size_type nbRows, size_type nbCols)
{
	for (int i = grid.m_nbRows; i < m_nbRows; ++i) {
		delete m_data->at(i);
	}

	m_data->resize(nbRows);
	m_nbRows = nbRows;

	m_nbCols = nbCols;

	for (int i = 0; i < m_nbCols; ++i) {
		m_data->at(i)->resize(m_nbCols);
	}
}

template<class T>
void Grid<T>::resize(size_type nbRows, size_type nbCols, T & val)
{
	for (int i = grid.m_nbRows; i < m_nbRows; ++i) {
		delete m_data->at(i);
	}

	m_data->resize(nbRows);
	m_nbRows = nbRows;

	m_nbCols = nbCols;

	for (int i = 0; i < m_nbCols; ++i) {
		m_data->at(i)->resize(m_nbCols, val);
	}
}

template<class T>
bool Grid<T>::empty()
{
	if (!m_data->empty()) {
		for (int i = 0; i < m_nbRows; ++i) {
			if (!m_data->at(i)->empty()) {
				return false;
			}
		}
	}
	else {
		return false;
	}

	return true;
}

template<class T>
T & Grid<T>::operator()(size_type row, size_type col)
{
	return (*m_data)[row][col];
}

template<class T>
const T & Grid<T>::operator()(size_type row, size_type col) const
{
	return (*m_data)[row][col];
}

template<class T>
T & Grid<T>::at(size_type row, size_type col)
{
	if (row < m_nbRows && col < m_nbCols) {
		return m_data->at(row)->at(col);
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
const T & Grid<T>::at(size_type row, size_type col) const
{
	if (row < m_nbRows && col < m_nbCols) {
		return (*m_data)[row][col];
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
Grid<T&> Grid<T>::rows(size_type row, size_type n)
{
	Grid<T&>rowsToReturn(n, m_nbCols);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m_nbCols; ++j) {
			rowsToReturn(i, j) = (*m_data)[i+row][j];
		}
	}

	return rowsToReturn;
}

template<class T>
const Grid<T&> Grid<T>::rows(size_type row, size_type n) const
{
	Grid<T&>rowsToReturn(n, m_nbCols);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m_nbCols; ++j) {
			rowsToReturn(i, j) = (*m_data)[i+row][j];
		}
	}

	return rowsToReturn;
}

template<class T>
Vector<T&> Grid<T>::row(size_type row)
{
	Vector<T&>rowToReturn(m_nbCols);

	for (int i = 0; i < m_nbCols; ++i) {
		rowToReturn[i] = (*m_data)[row][i];
	}

	return rowToReturn;
}

template<class T>
const Vector<T&> Grid<T>::row(size_type row) const
{
	Vector<T&>rowToReturn(m_nbCols);

	for (int i = 0; i < m_nbCols; ++i) {
		rowToReturn[i] = (*m_data)[row][i];
	}

	return rowToReturn;
}

template<class T>
Grid<T&> Grid<T>::cols(size_type col, size_type n)
{
	Grid<T&>colsToReturn(m_nbRows, n);

	for (int i = 0; i < m_nbRows; ++i) {
		for (int j = 0; j < n; ++j) {
			colsToReturn(i, j) = (*m_data)[i][j+col];
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
			colsToReturn(i, j) = (*m_data)[i][j + col];
		}
	}

	return colsToReturn;
}

template<class T>
Vector<T&> Grid<T>::col(size_type col)
{
	Vector<T&> colToReturn(m_nbRows);

	for (int i = 0; i < m_nbRows; ++i) {
		colToReturn[i] = (*m_data)[i][col];
	}

	return colToReturn;
}

template<class T>
const Vector<T&> Grid<T>::col(size_type col) const
{
	Vector<T&> colToReturn(m_nbRows);

	for (int i = 0; i < m_nbRows; ++i) {
		colToReturn[i] = (*m_data)[i][col];
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
Vector<Vector<T>*>* Grid<T>::data()
{
	return m_data;
}

template<class T>
const Vector<Vector<T>*>* Grid<T>::data() const
{
	return m_data;
}

template<class T>
void Grid<T>::assign(size_type nbRows, size_type nbCols, const T & val)
{
	resize(nbRows, nbRows);

	for (int i = 0; i < nbRows; ++i) {
		for (int j = 0; j < nbCols; ++j) {
			at(i, j) = val;
		}
	}

	m_nbRows = nbRows;
	m_nbCols = nbCols;
}

template<class T>
void Grid<T>::insertRows(size_type row, const Grid<T>& elements)
{
	if (elements.m_nbCols != m_nbCols) {
		throw std::length_error("grid::_M_number_of_columns_differs");
	}

	m_data->resize(m_nbRows + elements.m_nbRows);

	for (int i = m_nbRows - 1; i > row -1; --i) {
		m_data->at(i + elements.m_nbRows) = m_data->at(i);
	}

	for (int i = 0; i < elements.m_nbRows; ++i) {
		m_data->at(i + row) = new Vector<T>(*(m_data->at(i)));
	}

	m_nbRows += elements.m_nbRows;
}

template<class T>
void Grid<T>::insertRow(size_type row, const Vector<T>& elements)
{
	if (elements.size() != m_nbCols) {
		throw std::length_error("grid::_M_number_of_columns_differs");
	}

	m_data->resize(m_nbRows + 1);

	for (int i = m_nbRows - 1; i > row - 1; --i) {
		m_data->at(i + 1) = m_data->at(i);
	}

	m_data->at(row) = new Vector<T>(elements);

	m_nbRows += 1;
}

template<class T>
void Grid<T>::insertCols(size_type col, const Grid<T>& elements)
{
	if (elements.m_nbCols != m_nbCols) {
		throw std::length_error("grid::_M_number_of_rows_differs");
	}

	for (int i = 0; i < m_nbRows; i++) {
		m_data->at(i).resise(m_nbCols + elements.m_nbCols);

		for (int j = m_nbCols - 1; j > col - 1; --j) {
			at(i, j + elements.m_nbCols) = at(i, j);
		}

		for (int j = 0; j < elements.m_nbCols; --j) {
			at(i, j + col) = elements.at(i, j);
		}
	}

	m_nbCols += elements.m_nbCols;
}

template<class T>
void Grid<T>::insertCol(size_type col, const Vector<T>& elements)
{
	if (elements.m_nbCols != m_nbCols) {
		throw std::length_error("grid::_M_number_of_rows_differs");
	}

	for (int i = 0; i < m_nbRows; i++) {
		m_data->at(i).resise(m_nbCols + 1);

		for (int j = m_nbCols - 1; j > col - 1; --j) {
			at(i, j + elements.m_nbCols) = at(i, j);
		}

		at(i, j + 1) = elements.at(i, j);
	}
}

template<class T>
void Grid<T>::removeRows(size_type row, size_type n)
{
	for (int i = row, i < row + n; ++i) {
		delete m_data->at(i);
	}

	m_nbRows -= n;

	m_data->erase(row, n);
}

template<class T>
void Grid<T>::removeCols(size_type col, size_type n)
{
	for (int i = 0; i < m_nbRows; ++i) {
		m_data->at(i).erase(col, n);
	}

	m_nbCols -= n;
}

template<class T>
void Grid<T>::swap(Grid<T>& grid)
{
	int holdNbRows = m_nbRows;
	int holdNbCols = m_nbCols;
	Vector<Vector<T>*>* holdData = m_data;

	m_nbRows = grid.m_nbRows;
	m_nbCols = grid.m_nbCols;
	m_data = grid.m_data;

	grid.m_nbRows = holdNbRows;
	grid.m_nbCols = holdNbCols;
	grid.m_data = holdData;
}

template<class T>
void Grid<T>::clear()
{
	for (int i = 1; i < m_nbRows; ++i) {
		delete m_data->at(i);
	}

	m_data->at(0)->clear();

	m_data->resize(1);

	m_nbCols = 0;
	m_nbRows = 0;
}
