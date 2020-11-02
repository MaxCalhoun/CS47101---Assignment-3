/*
	Max Calhoun
	Shape.h
*/

#pragma once
#include "Transformation.h"
#include "Color.h"
#include "Mesh.h"

class Shape
{
	public:
		Shape();
		Shape(const Vector3&, const Vector3&, const Vector3&, Color*, Mesh*);

		void setTranslation(const Vector3&);
		void setRotation(const Vector3&);
		void setScale(const Vector3&);

		Vector3 getTranslation() const;
		Vector3 getRotation() const;
		Vector3 getScale() const;

		void translate(const Vector3&);
		void rotate(const Vector3&);
		void scale(const Vector3&);

		// Make sure parameter is not used elsewhere in program
		void changeColor(Color*);

		virtual void draw();

	protected:
		Mesh* mesh_;
		Transformation transformation_;
		Color* color_;
};

// A shape that can be drawn as a solid or wire mesh
class ToggleShape : public Shape
{
	public:
		ToggleShape();
		ToggleShape(const Vector3&, const Vector3&, const Vector3&, Color*, Mesh*, Mesh*);

		void draw() final;
		void makeSolid();
		void makeWireframe();

	private:
		bool isSolid_;
		Mesh* wiremesh_;
};
