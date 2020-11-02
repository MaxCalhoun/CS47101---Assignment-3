/*
	Max Calhoun
	Color.h
*/

#pragma once
#include <GL/glut.h>

class Color
{
	public:
		Color() : red_(0), green_(0), blue_(0) {};
		Color(int, int, int);

		void color();

	private:
		int red_, green_, blue_;
};

class Red : public Color
{
	public:
		Red() : Color(255, 0, 0) {};
};

class Green : public Color
{
	public:
		Green() : Color(0, 255, 0) {};
};

class Blue : public Color
{
	public:
		Blue() : Color(0, 0, 255) {};
};

class White : public Color
{
	public:
		White() : Color(255, 255, 255) {};
};

class Black : public Color
{
	public:
		Black() : Color(0, 0, 0) {};
};

class Orange : public Color
{
	public:
		Orange() : Color(255, 128, 0) {};
};

class Yellow : public Color
{
	public:
		Yellow() : Color(255, 255, 0) {};
};

class Purple : public Color
{
	public:
		Purple() : Color(128, 0, 255) {};
};