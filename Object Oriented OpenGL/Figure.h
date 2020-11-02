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

		int leftShoulderVelocity_;
		int rightShoulderVelocity_;
		int leftElbowVelocity_;
		int rightElbowVelocity_;
		int leftHipVelocity_;
		int rightHipVelocity_;
		int leftKneeVelocity_;
		int rightKneeVelocity_;

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