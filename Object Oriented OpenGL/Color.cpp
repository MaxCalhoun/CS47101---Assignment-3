/*
	Max Calhoun
	Color.cpp
*/

#include "Color.h"

Color::Color(int red, int green, int blue)
{
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
	if (blue < 0)
		blue = 0;

	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;

	red_ = red;
	green_ = green;
	blue_ = blue;
}

void Color::color()
{
	const float divisor = 255;

	float r = red_ / divisor;
	float g = green_ / divisor;
	float b = blue_ / divisor;

	glColor3f(r, g, b);
}