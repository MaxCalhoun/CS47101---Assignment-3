/*
	Max Calhoun
	Tranformation.h
*/

#pragma once
#include "Vector3.h"
#include <GL/glut.h>
#include <iostream>

class Transformation
{
	public:
		Transformation();
		Transformation(const Vector3&, const Vector3&, const Vector3&);

		void setTranslation(const Vector3&);
		void setRotation(const Vector3&);
		void setScale(const Vector3&);

		Vector3 getTranslation() const;
		Vector3 getRotation() const;
		Vector3 getScale() const;

		void translate(const Vector3&);
		void rotate(const Vector3&);
		void scale(const Vector3&);

		void transform() const;

	private:
		Vector3 translation_, rotation_, scale_;
};
