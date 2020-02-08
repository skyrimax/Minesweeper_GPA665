#include "Vector.h"

#pragma once

#include<cmath>
#include<utility>

template<class T>
Vector<T>::Vector()
{
	//Create an array on one element and initialize internal attributes
	m_data = new T[1];
	m_size = 0;
	m_capacity = 1;
}

template<class T>
Vector<T>::Vector(Vector<T>::size_type n)
{
	//Determining necessary capacity to store n elements
	m_capacity = pow(2, ceil(log2((double)n)));

	//Allocating the array of necessary capacity
	m_data = new T[m_capacity];

	//Setting the usable size of the object at n
	m_size = n;
}

template<class T>
Vector<T>::Vector(Vector<T>::size_type n, T& val)
{
	//Determining necessary capacity to store n elements
	m_capacity = pow(2, ceil(log2((double)n)));

	//Allocating the array of necessary capacity
	m_data = new T[m_capacity];

	//Setting the usable size of the object at n
	m_size = n;

	//Filling array with copies of specified val
	for (int i=0; i < n; ++1) {
		m_data[i] = T(val);
	}
}

template<class T>
Vector<T>::Vector(const Vector<T>& vector)
{
	//Copying internal attributes from other vector
	m_size = vector.m_size;
	m_capacity = vector.m_capacity;

	//Create arraw containing as many elements as the capacity specifies
	m_data = new T[m_capacity];

	//Filling array with copies of the elemenents present in the other array
	for (int i = 0; i < m_size; ++i) {
		m_data[i] = vector.m_data[i];
	}
}

template<class T>
Vector<T>::Vector(Vector<T>&& vector)
{
	//Transfert of the other vector's internal data to the new object
	m_data = vector.m_data;
	m_size = vector.m_size;
	m_capacity = vector.m_capacity;

	//Removing ownership of data from other object
	vector.m_data = nullptr;
	vector.m_size = 0;
	vector.m_capacity = 0;
}

template <class T>
Vector<T>::~Vector()
{
	//Deallocating the array
	delete[] m_data;
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& vector)
{
	if (this != &vector) {
		delete[] m_data;

		m_capacity = vector.m_capacity;
		m_size = vector.m_size;

		m_data = new T[m_capacity];

		for (int i; i < m_size; ++i) {
			m_data[i] = T(vector.m_data[i]);
		}
	}

	return this*;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& vector)
{
	if (this != &vector) {
		delete[] m_data;

		//Transfert of the other vector's internal data to the calling object
		m_size = vector.m_size;
		m_capacity = vector.m_capacity;
		m_data = vector.m_data;

		//Removing ownership of data from other object
		vector.m_data = nullptr;
		vector.m_size = 0;
		vector.m_capacity = 0;
	}

	return this*;
}

template<class T>
typename Vector<T>::size_type Vector<T>::size() const
{
	return m_size;
}

template<class T>
void Vector<T>::resize(size_type n)
{
	//For loop to remove elements past n if n is smaller than current size
	for (int i = n; i < m_size; ++i) {
		m_data[i] = T();
	}

	//Will allocate more memory top the array if n if bigger than current capacity
	reserve(n);

	//Expending accessible size to match n
	m_size = n;
}

template<class T>
void Vector<T>::resize(size_type n, const T & val)
{
	//For loop to remove elements past n if n is smaller than current size
	for (int i = n; i < m_size; ++i) {
		m_data[i] = T();
	}

	//Will allocate more memory top the array if n if bigger than current capacity
	reserve(n);

	//Filling new space with copies of specified val
	for (int i = m_size; i < n; ++i) {
		m_data[i] = T(val);
	}

	//Expending accessible size to match n
	m_size = n;
}

template<class T>
typename Vector<T>::size_type Vector<T>::capacity() const
{
	return m_capacity;
}

template<class T>
bool Vector<T>::empty() const
{
	//Object is considered empty if size (nb of elements) is 0
	return m_size==0;
}

template<class T>
void Vector<T>::reserve(size_type n)
{
	//Operation will only be executed if desired capacity n is smaller then current capacity
	if (n > m_capacity) {
		//Determining necessary capacity
		size_type newCapacity = pow(2, ceil(log2((double)n)));

		//Allocating new array of determined capacity
		T* newArray = new T[newCapacity];

		//Copy of elements from previous array to new array
		for (int i = 0; i < m_size; ++i) {
			newArray[i] = m_data[i];
		}

		//Deallocation of previous array
		delete[] m_data;

		//New array is assigned as the object's internal arraw
		m_data = newArray;
		//The internal capacity is set to the determined capacity
		m_capacity = newCapacity;
	}
}

template<class T>
void Vector<T>::shrink_to_fit()
{
	//Operation will only be executed if reducing the size of the array will allow it to still contain all of it's elements
	if (m_capacity / 2 >= m_size) {
		//Determining necessary capacity
		size_type newCapacity = pow(2, ceil(log2((double)n)));

		//Allocating new array of determined capacity
		T* newArray = new T[newCapacity];

		//Copy of elements from previous array to new array
		for (int i = 0; i < m_size) {
			newArray[i] = m_data[i];
		}

		//Deallocation of previous array
		delete[] m_data;

		//New array is assigned as the object's internal arraw
		m_data = newArray;
		//The internal capacity is set to the determined capacity
		m_capacity = newCapacity;
	}
}

template<class T>
T & Vector<T>::operator[](size_type n)
{
	return m_data[n];
}

template<class T>
const T & Vector<T>::operator[](size_type n) const
{
	return m_data[n];
}

template<class T>
T & Vector<T>::at(size_type n)
{
	if (n < m_size) {
		return m_data[n];
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
const T & Vector<T>::at(size_type n) const
{
	if (n < m_size) {
		return m_data[n];
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
T & Vector<T>::front()
{
	if (m_size != 0) {
		return m_data[0];
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
const T & Vector<T>::front() const
{
	if (m_size != 0) {
		return m_data[0];
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
T & Vector<T>::back()
{
	if (m_size != 0) {
		return m_data[m_size - 1];
	}
	else {
		throw std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
const T & Vector<T>::back() const
{
	/ if (m_size != 0) {
		return m_data[m_size - 1];
	}
	else {
		rthrow std::out_of_range("vector::_M_range_check");
	}
}

template<class T>
T * Vector<T>::data()
{
	return m_data;
}

template<class T>
const T * Vector<T>::data() const
{
	return m_data;
}

template<class T>
void Vector<T>::assign(size_type n, const T & val)
{
	delete[] m_data;

	m_capacity = pow(2, ceil(log2((double)n)));
	m_size = n;

	m_data = new[m_capacity];

	for (int i = 0; i < m_size; ++i) {
		m_data[i] = T(val);
	}
}

template<class T>
void Vector<T>::push_back(const T & val)
{
	reserve(m_size + 1);

	m_data[m_size] = val;

	++m_size;
}

template<class T>
void Vector<T>::push_back(T && val)
{
	reserve(m_size + 1);

	m_data[m_size] = std::move(val);

	++m_size;
}

template<class T>
void Vector<T>::pop_back()
{
	--m_size;

	m_data[m_size] = T();
}

template<class T>
void Vector<T>::erase(size_type pos, size_type n)
{
	int i;

	for (i = pos; i < pos + n && i + n < m_size; ++i) {
		m_data[i] = m_data[i + n];
	}

	for (; i < m_size, ++i) {
		m_data[i] = T();
	}

	m_size -= n;
}

template<class T>
void Vector<T>::swap(Vector<T>& vector)
{
	size_type holdSize = m_size;
	size_type holdCapacity = m_capacity;
	T* holdArray = m_data;

	m_size = vector.m_size;
	m_capacity = vector.m_capacity;
	m_data = vector.m_data;

	vector.m_size = holdSize;
	vector.m_capacity = holdCapacity;
	vector.m_data = holdArray;
}

template<class T>
void Vector<T>::clear()
{
	for (int i = 0; i < m_size; ++i) {
		m_data[i] = T();
	}

	m_size = 0;
}

template<class T>
inline void swap(Vector<T>& x, Vector<T>& y)
{
	x.swap(y);
}