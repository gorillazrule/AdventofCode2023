#pragma once
#include <vector>
#include <iostream>

template <typename T> class matrix
{
private:
	std::vector<T> data;
	int height;
	int width;

public:
	matrix() : height(0), width(0) {}
	matrix(int w) : width(w), height(0) {}
	matrix(int w, int h, T initial) : width(w), height(h), data(w*h, initial) {}
	void addElements(std::vector<T> &elem);
	T at(int x, int y);
	void setWidth(int w);
	int getWidth();
	int getHeight();
	void set(int x, int y, T value);
};

template <typename T>
void matrix<T>::addElements(std::vector<T>& elem)
{
	try
	{
		if (elem.size() == width)
		{
			++height;
			data.insert(data.end(), elem.begin(), elem.end());
		}
		else
		{
			throw elem.size();
		}
	}
	catch (int size)
	{
		std::cout << "Error occured in addElements. vector size: " << size << " when size expected: " << width << std::endl;
	}
}

template <typename T>
T matrix<T>::at(int x, int y)
{
	try
	{
		if (x < 0 || x >= width)
		{
			throw "Error invalid x value: " + x;
		}
		if (y < 0 || y >= height)
		{
			throw "Error invalid y value: " + y;
		}

		return data.at(y * width + x);

	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
	}
}

template<typename T>
void matrix<T>::setWidth(int w)
{
	width = w;
}

template<typename T>
int matrix<T>::getWidth()
{
	return width;
}

template<typename T>
int matrix<T>::getHeight()
{
	return height;
}

template<typename T>
void matrix<T>::set(int x, int y, T value)
{
	try
	{
		if (x < 0 || x >= width)
		{
			throw "Error invalid x value: " + x;
		}
		if (y < 0 || y >= height)
		{
			throw "Error invalid y value: " + y;
		}
		data.at(width * y + x) = value;
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
	}
}

