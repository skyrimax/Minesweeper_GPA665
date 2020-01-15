#include "Vector.h"

#include<cmath>

template<class T>
Vector<T>::Vector()
{
	//Create an array on one element and initialize internal attributes
	m_data = new T[1];
	m_size = 1;
	m_capacity = 1;
}

template<class T>
Vector<T>::Vector(Vector<T>::size_type n)
{
	//Determining necessary capacity to store n elements
	size_type m_capacity = pow(2, ceil(log2((double)n)));

	//Allocating the array of necessary capacity
	m_data = new T[m_capacity];

	//Setting the usable size of the object at n
	m_size = n;
}

template<class T>
Vector<T>::Vector(Vector<T>::size_type n, T val)
{
	//Determining necessary capacity to store n elements
	size_type m_capacity = pow(2, ceil(log2((double)n)));

	//Allocating the array of necessary capacity
	m_data = new T[m_capacity];

	//Setting the usable size of the object at n
	m_size = n;

	//Filling array with copies of specified val
	for (int i=0; i < n; ++1) {
		m_data[i] = T(element);
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

template <class T>
Vector<T>::~Vector()
{
	//Deallocating the array
	delete[] m_data;
}

template<class T>
typename Vector<T>::size_type Vector<T>::size()
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
typename Vector<T>::size_type Vector<T>::capacity()
{
	return m_capacity;
}

template<class T>
bool Vector<T>::empty()
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
