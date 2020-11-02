/*
	Max Calhoun
	Vector3.h
*/

#pragma once
#include <iostream>

class Vector3
{
	public:
		Vector3();
		Vector3(float, float, float);

		void swap(Vector3&);
		Vector3& operator=(Vector3);
		
		Vector3 operator+(const Vector3&) const;
		Vector3& operator+=(const Vector3&);

		// Essentially Equal (not exact)
		bool operator==(const Vector3&) const;

		friend std::ostream& operator<<(std::ostream&, const Vector3&);

		// Shifts the x, y, and z values to be within the specified range
		void restrict(float, float);

		void setX(float);
		void setY(float);
		void setZ(float);

		float getX() const;
		float getY() const;
		float getZ() const;

	private:
		float x_;
		float y_;
		float z_;
};