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
	Grid(size_type nbRows, size_type nbCols, const T& val);
	Grid(const Grid<T>& grid);
	Grid(Grid<T>&& grid);
	~Grid();

	//Assignement operator overloading
	Grid<T>& operator=(const Grid<T>& grid);
	Grid<T>& operator=(Grid<T>&& grid);

	//Capacity related member functions
	Vector<size_type>& size();
	void resize(size_type nbRows, size_type nbCols);
	void resize(size_type nbRows, size_type nbCols, T& val);
	bool empty();

	//Element access methods
	T& operator()(size_type row, size_type col);
	const T& operator()(size_type row, size_type col) const;
	T& at(size_type row, size_type col);
	const T& at(size_type row, size_type col) const;
	Grid<T&> rows(size_type row, size_type n=1);
	const Grid<T&> rows(size_type row, size_type n = 1) const;
	Vector<T&> row(size_type row);
	const Vector<T&> row(size_type row) const;
	Grid<T&> cols(size_type col, size_type n = 1);
	const Grid<T&> cols(size_type col, size_type n = 1) const;
	Vector<T&> col(size_type col);
	const Vector<T&> col(size_type col) const;
	Grid<T&> firstRowGrid();
	const Grid<T&> firstRowGrid() const;
	Vector<T&> firstRowVector();
	const Vector<T&> firstRowVector() const;
	Grid<T&> lastRowGrid();
	const Grid<T&> lastRowGrid() const;
	Vector<T&> lastRowVector();
	const Vector<T&> lastRowVector() const;
	Grid<T&> firstColGrid();
	const Grid<T&> firstColGrid() const;
	Vector<T&> firstColVector();
	const Vector<T&> firstColVector() const;
	Grid<T&> lastColGrid();
	const Grid<T&> lastColGrid() const;
	Vector<T&> lastColVector();
	const Vector<T&> lastColVector() const;
	Vector<Vector<T>*>* data();
	const Vector<Vector<T>*>* data() const;

	//Modifiers
	void assign(size_type nbRows, size_type nbCols, const T& val);
	void insertRows(size_type row, const Grid<T>& elements);
	void insertRow(size_type row, const Vector<T>& elements);
	void insertCols(size_type col, const Grid<T>& elements);
	void insertCol(size_type col, const Vector<T>& elements);
	void removeRows(size_type row, size_type n = 1);
	void removeCols(size_type col, size_type n = 1);
	void swap(Grid<T>& grid);
	void clear();

private:
	Vector<Vector<T>*>* m_data;
	size_type m_nbRows;
	size_type m_nbCols;
};

#include"Grid.tpp"