/*
	Max Calhoun
	Tranformation.cpp
*/

#include "Transformation.h"

Transformation::Transformation()
{
	translation_ = Vector3();
	rotation_ = Vector3();
	scale_ = Vector3(1, 1, 1);
}

Transformation::Transformation(const Vector3& t, const Vector3& r, const Vector3& s)
{
	translation_ = t;
	(rotation_ = r).restrict(0, 360);
	scale_ = s;
}

void Transformation::setTranslation(const Vector3& p) { translation_ = p; }
void Transformation::setRotation(const Vector3& r) { (rotation_ = r).restrict(0, 360); }
void Transformation::setScale(const Vector3& s) { scale_ = s; }

Vector3 Transformation::getTranslation() const { return translation_; }
Vector3 Transformation::getRotation() const { return rotation_; }
Vector3 Transformation::getScale() const { return scale_; }

void Transformation::translate(const Vector3& t) { translation_ += t; }
void Transformation::rotate(const Vector3& r) { (rotation_ += r).restrict(0, 360); }
void Transformation::scale(const Vector3& s) { scale_ += s; }

void Transformation::transform() const
{
	glTranslatef(translation_.getX(), translation_.getY(), translation_.getZ());

	glScalef(scale_.getX(), scale_.getY(), scale_.getZ());

	glRotatef(rotation_.getZ(), 0, 0, 1);
	glRotatef(rotation_.getY(), 0, 1, 0);
	glRotatef(rotation_.getX(), 1, 0, 0);
}