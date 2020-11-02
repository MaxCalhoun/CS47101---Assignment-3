/*
	Max Calhoun
	Vector3.cpp
*/

#include "Vector3.h"

Vector3::Vector3()
{
	x_ = 0.0;
	y_ = 0.0;
	z_ = 0.0;
}

Vector3::Vector3(float x, float y, float z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}

void Vector3::swap(Vector3& rhs)
{
	float temp;

	temp = x_;
	x_ = rhs.x_;
	rhs.x_ = temp;

	temp = y_;
	y_ = rhs.y_;
	rhs.y_ = temp;

	temp = z_;
	z_ = rhs.z_;
	rhs.z_ = temp;
}

Vector3& Vector3::operator=(Vector3 rhs)
{
	swap(rhs);
	return *this;
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x_ += rhs.x_;
	y_ += rhs.y_;
	z_ += rhs.z_;

	return *this;
}

bool Vector3::operator==(const Vector3& rhs) const
{
	return (x_ == rhs.x_) && (y_ == rhs.y_) && (z_ == rhs.z_);
}

std::ostream& operator<<(std::ostream& out, const Vector3& rhs)
{
	out << "<" << rhs.x_ << ", " << rhs.y_ << ", " << rhs.z_ << ">";
	return out;
}

void Vector3::restrict(float lowerBound, float upperBound)
{
	if (lowerBound == upperBound)
	{
		x_ = lowerBound;
		y_ = lowerBound;
		z_ = lowerBound;

		return;
	}

	if (lowerBound > upperBound)
		std::swap(lowerBound, upperBound);

	while (x_ < lowerBound || x_ >= upperBound)
	{
		if (x_ < lowerBound)
			x_ += upperBound;

		if (x_ >= upperBound)
			x_ -= upperBound;
	}

	while (y_ < lowerBound || y_ >= upperBound)
	{
		if (y_ < lowerBound)
			y_ += upperBound;

		if (y_ >= upperBound)
			y_ -= upperBound;
	}

	while (z_ < lowerBound || z_ >= upperBound)
	{
		if (z_ < lowerBound)
			z_ += upperBound;

		if (z_ >= upperBound)
			z_ -= upperBound;
	}
}

float Vector3::getX() const { return x_; } 
float Vector3::getY() const { return y_; }
float Vector3::getZ() const { return z_; }

void Vector3::setX(float x) { x_ = x; }
void Vector3::setY(float y) { y_ = y; }
void Vector3::setZ(float z) { z_ = z; }