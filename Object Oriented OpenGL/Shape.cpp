/*
	Max Calhoun
	Shape.cpp
*/

#include "Shape.h"

Shape::Shape()
{
	transformation_ = Transformation();
	color_ = new White();
	mesh_ = new CubeMesh();
}

Shape::Shape(const Vector3& t, const Vector3& r, const Vector3& s, Color* c, Mesh* m)
{
	transformation_ = Transformation(t, r, s);
	color_ = c;
	mesh_ = m;
}

void Shape::setTranslation(const Vector3& t) { transformation_.setTranslation(t); }
void Shape::setRotation(const Vector3& r) { transformation_.setRotation(r); }
void Shape::setScale(const Vector3& s) { transformation_.setScale(s); }

Vector3 Shape::getTranslation() const { return transformation_.getTranslation(); }
Vector3 Shape::getRotation() const { return transformation_.getRotation(); }
Vector3 Shape::getScale() const { return transformation_.getScale(); }

void Shape::translate(const Vector3& t) { transformation_.translate(t); }
void Shape::rotate(const Vector3& r) { transformation_.rotate(r); }
void Shape::scale(const Vector3& s) { transformation_.scale(s); }

void Shape::changeColor(Color* c)
{
	delete color_;
	color_ = c;
}

void Shape::draw()
{
	glPushMatrix();
	{
		transformation_.transform();
		color_->color();
		mesh_->drawMesh();
	}
	glPopMatrix();
}

ToggleShape::ToggleShape() : Shape()
{
	wiremesh_ = new WireCubeMesh();
	isSolid_ = true;
}

ToggleShape::ToggleShape(const Vector3& t, const Vector3& r, const Vector3& s, Color* c, Mesh* m1, Mesh* m2) : Shape(t, r, s, c, m1)
{
	wiremesh_ = m2;
	isSolid_ = true;
}

void ToggleShape::draw()
{
	glPushMatrix();
	{
		transformation_.transform();
		color_->color();
		isSolid_ ? mesh_->drawMesh() : wiremesh_->drawMesh();
	}
	glPopMatrix();
}

void ToggleShape::makeSolid() { isSolid_ = true; }
void ToggleShape::makeWireframe() { isSolid_ = false; }