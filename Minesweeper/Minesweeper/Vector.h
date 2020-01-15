#pragma once

template <class T>
class Vector
{
public:
	//Type to indicate size of container
	typedef unsigned int size_type;

	//Default constructor
	Vector();
	Vector(size_type n);
	Vector(size_type n, T val);
	Vector(const Vector<T>& vector);
	~Vector();

	//Capacity related member functions
	size_type size();
	void resize(size_type n);
	void resize(size_type n, const T& val);
	size_type capacity();
	bool empty();
	void reserve(size_type n);
	void shrink_to_fit();

private:
	T* m_data;
	size_type m_size;
	size_type m_capacity;
};

