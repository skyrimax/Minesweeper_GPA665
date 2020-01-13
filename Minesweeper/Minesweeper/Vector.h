#pragma once

template <class T>
class Vector
{
public:
	//Default constructor
	Vector();
	Vector(int n);
	Vector(int n, T element);
	Vector(T vector);
	~Vector();

private:
	T* m_data;
	int m_size;
	int m_maxSize;
};

