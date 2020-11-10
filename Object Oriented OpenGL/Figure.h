/*
	Max Calhoun
	Figure.h
*/

#pragma once
#include "Shape.h"
#define devMode false


class Figure
{
	public:
		Figure();
		Figure(const Vector3&, const Vector3&, const Vector3&);

		void setTranslation(const Vector3&);
		void setRotation(const Vector3&);
		void setScale(const Vector3&);

		void translate(const Vector3&);
		void rotate(const Vector3&);
		void scale(const Vector3&);

		Vector3 getTranslation();
		Vector3 getRotation();
		Vector3 getScale();

		virtual void draw() = 0;

	protected:
		Transformation figureTransformation_;
};

class Robot : public Figure
{
	public:
		Robot();
		Robot(const Vector3&, const Vector3&, const Vector3&);

		void draw() final;

		void makeSolid();
		void makeWireframe();

		void rotateLeftShoulder(const Vector3&);
		void rotateRightShoulder(const Vector3&);
		void rotateLeftElbow(const Vector3&);
		void rotateRightElbow(const Vector3&);
		void rotateLeftHip(const Vector3&);
		void rotateRightHip(const Vector3&);
		void rotateLeftKnee(const Vector3&);
		void rotateRightKnee(const Vector3&);

		void animateWalking();

	private:
		void debugDraw();

		Shape* head_;
		Shape* torso_;
		Shape* leftUpperArm_;
		Shape* leftLowerArm_;
		Shape* rightUpperArm_;
		Shape* rightLowerArm_;
		Shape* leftUpperLeg_;
		Shape* leftLowerLeg_;
		Shape* rightUpperLeg_;
		Shape* rightLowerLeg_;

		Transformation leftShoulder_;
		Transformation rightShoulder_;
		Transformation leftElbow_;
		Transformation rightElbow_;
		Transformation leftHip_;
		Transformation rightHip_;
		Transformation leftKnee_;
		Transformation rightKnee_;

		float leftShoulderVelocity_;
		float rightShoulderVelocity_;
		float leftElbowVelocity_;
		float rightElbowVelocity_;
		float leftHipVelocity_;
		float rightHipVelocity_;
		float leftKneeVelocity_;
		float rightKneeVelocity_;

		bool isSolid_;
};

class Axis : public Figure
{
	public:
		Axis();

		void draw() final;

	private:
		Shape* xAxis_, * yAxis_, * zAxis_;
};

class Tree : public Figure
{
	public:
		Tree();
		Tree(const Vector3&, const Vector3&, const Vector3&);

		void draw() final;

		void makeSolid();
		void makeWireframe();

	private:
		Shape* trunk_, * leaves_;
};
