/*
	Max Calhoun
	Figure.h
*/

#include "Figure.h"

Figure::Figure() { figureTransformation_ = Transformation(); }

Figure::Figure(const Vector3& t, const Vector3& r, const Vector3& s) { figureTransformation_ = Transformation(t, r, s); }

Robot::Robot() : Figure()
{
	// Body Parts
	head_ = new ToggleShape(Vector3(0, 3, 0), Vector3(0, 0, 0), Vector3(2, 2, 2), new Yellow(), new SphereMesh(), new WireSphereMesh());
	torso_ = new ToggleShape(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(2, 4, 1), new Red(), new CubeMesh(), new WireCubeMesh());
	leftUpperArm_ = new ToggleShape(Vector3(1, 0, 0), Vector3(0, 0, 0), Vector3(2, 0.5, 1), new Red(), new CubeMesh(), new WireCubeMesh());
	leftLowerArm_ = new ToggleShape(Vector3(1, 0, 0), Vector3(0, 0, 0), Vector3(2, 0.5, 1), new Red(), new CubeMesh(), new WireCubeMesh());
	rightUpperArm_ = new ToggleShape(Vector3(-1, 0, 0), Vector3(0, 0, 0), Vector3(2, 0.5, 1), new Red(), new CubeMesh(), new WireCubeMesh());
	rightLowerArm_ = new ToggleShape(Vector3(-1, 0, 0), Vector3(0, 0, 0), Vector3(2, 0.5, 1), new Red(), new CubeMesh(), new WireCubeMesh());
	leftUpperLeg_ = new ToggleShape(Vector3(0, -1, 0), Vector3(0, 0, 0), Vector3(1, 2, 0.5), new Blue(), new CubeMesh(), new WireCubeMesh());
	leftLowerLeg_ = new ToggleShape(Vector3(0, -1, 0), Vector3(0, 0, 0), Vector3(1, 2, 0.5), new Blue(), new CubeMesh(), new WireCubeMesh());
	rightUpperLeg_ = new ToggleShape(Vector3(0, -1, 0), Vector3(0, 0, 0), Vector3(1, 2, 0.5), new Blue(), new CubeMesh(), new WireCubeMesh());
	rightLowerLeg_ = new ToggleShape(Vector3(0, -1, 0), Vector3(0, 0, 0), Vector3(1, 2, 0.5), new Blue(), new CubeMesh(), new WireCubeMesh());

	// Joints
	leftShoulder_ = Transformation(Vector3(1, 1.75, 0), Vector3(0,0,0), Vector3(1, 1, 1));
	rightShoulder_ = Transformation(Vector3(-1, 1.75, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	leftElbow_ = Transformation(Vector3(2, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	rightElbow_ = Transformation(Vector3(-2, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	leftHip_ = Transformation(Vector3(0.5, -2, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	rightHip_ = Transformation(Vector3(-0.5, -2, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	leftKnee_ = Transformation(Vector3(0, -2, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	rightKnee_ = Transformation(Vector3(0, -2, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	isSolid_ = true;

	leftShoulderVelocity_ = 0;
	rightShoulderVelocity_ = 0;
	leftElbowVelocity_ = 0;
	rightElbowVelocity_ = 0;
	leftHipVelocity_ = 0;
	rightHipVelocity_ = 0;
	leftKneeVelocity_ = 0;
	rightKneeVelocity_ = 0;
}

Robot::Robot(const Vector3& t, const Vector3& r, const Vector3& s) : Robot() 
{
	figureTransformation_ = Transformation(t, r, s);
}

void Robot::draw()
{		
	glPushMatrix();
	{
		figureTransformation_.transform();
		glPushMatrix();
		{
			head_->draw();
			torso_->draw();

			// Left Arm
			glPushMatrix();
			{
				leftShoulder_.transform();
				debugDraw();
				leftUpperArm_->draw();
				glPushMatrix();
				{
					leftElbow_.transform();
					debugDraw();
					leftLowerArm_->draw();
				}
				glPopMatrix();
			}
			glPopMatrix();

			// Right Arm
			glPushMatrix();
			{
				rightShoulder_.transform();
				debugDraw();
				rightUpperArm_->draw();
				glPushMatrix();
				{
					rightElbow_.transform();
					debugDraw();
					rightLowerArm_->draw();
				}
				glPopMatrix();
			}
			glPopMatrix();

			// Left Leg
			glPushMatrix();
			{
				leftHip_.transform();
				debugDraw();
				leftUpperLeg_->draw();
				glPushMatrix();
				{
					leftKnee_.transform();
					debugDraw();
					leftLowerLeg_->draw();
				}
				glPopMatrix();
			}
			glPopMatrix();
			
			// Right Leg
			glPushMatrix();
			{
				rightHip_.transform();
				debugDraw();
				rightUpperLeg_->draw();
				glPushMatrix();
				{
					rightKnee_.transform();
					debugDraw();
					rightLowerLeg_->draw();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void Robot::debugDraw()
{
	Shape* joint = new Shape(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), new Green(), new WireCubeMesh());

	if (devMode == true)
		joint->draw();
}

void Robot::makeSolid()
{
	if (isSolid_ == false)
	{
		static_cast<ToggleShape*>(head_)->makeSolid();
		static_cast<ToggleShape*>(torso_)->makeSolid();
		static_cast<ToggleShape*>(leftUpperArm_)->makeSolid();
		static_cast<ToggleShape*>(leftLowerArm_)->makeSolid();
		static_cast<ToggleShape*>(rightUpperArm_)->makeSolid();
		static_cast<ToggleShape*>(rightLowerArm_)->makeSolid();
		static_cast<ToggleShape*>(leftUpperLeg_)->makeSolid();
		static_cast<ToggleShape*>(leftLowerLeg_)->makeSolid();
		static_cast<ToggleShape*>(rightUpperLeg_)->makeSolid();
		static_cast<ToggleShape*>(rightLowerLeg_)->makeSolid();

		head_->changeColor(new Yellow);
		torso_->changeColor(new Red());
		leftUpperArm_->changeColor(new Red());
		leftLowerArm_->changeColor(new Red());
		rightUpperArm_->changeColor(new Red());
		rightLowerArm_->changeColor(new Red());
		leftUpperLeg_->changeColor(new Blue());
		leftLowerLeg_->changeColor(new Blue());
		rightUpperLeg_->changeColor(new Blue());
		rightLowerLeg_->changeColor(new Blue());
		
		isSolid_ = true;
	}
}

void Robot::makeWireframe()
{
	if (isSolid_ == true)
	{
		static_cast<ToggleShape*>(head_)->makeWireframe();
		static_cast<ToggleShape*>(torso_)->makeWireframe();
		static_cast<ToggleShape*>(leftUpperArm_)->makeWireframe();
		static_cast<ToggleShape*>(leftLowerArm_)->makeWireframe();
		static_cast<ToggleShape*>(rightUpperArm_)->makeWireframe();
		static_cast<ToggleShape*>(rightLowerArm_)->makeWireframe();
		static_cast<ToggleShape*>(leftUpperLeg_)->makeWireframe();
		static_cast<ToggleShape*>(leftLowerLeg_)->makeWireframe();
		static_cast<ToggleShape*>(rightUpperLeg_)->makeWireframe();
		static_cast<ToggleShape*>(rightLowerLeg_)->makeWireframe();

		head_->changeColor(new White());
		torso_->changeColor(new White());
		leftUpperArm_->changeColor(new White());
		leftLowerArm_->changeColor(new White());
		rightUpperArm_->changeColor(new White());
		rightLowerArm_->changeColor(new White());
		leftUpperLeg_->changeColor(new White());
		leftLowerLeg_->changeColor(new White());
		rightUpperLeg_->changeColor(new White());
		rightLowerLeg_->changeColor(new White());

		isSolid_ = false;
	}
}

void Robot::rotateLeftShoulder(const Vector3& r) { leftShoulder_.rotate(r); }
void Robot::rotateRightShoulder(const Vector3& r) { rightShoulder_.rotate(r); }
void Robot::rotateLeftElbow(const Vector3& r) { leftElbow_.rotate(r); }
void Robot::rotateRightElbow(const Vector3& r) { rightElbow_.rotate(r); }
void Robot::rotateLeftHip(const Vector3& r) { leftHip_.rotate(r); }
void Robot::rotateRightHip(const Vector3& r) { rightHip_.rotate(r); }
void Robot::rotateLeftKnee(const Vector3& r) { leftKnee_.rotate(r); }
void Robot::rotateRightKnee(const Vector3& r) { rightKnee_.rotate(r); }

void Robot::animateWalking()
{
	if (leftHipVelocity_ == 0)
		leftHipVelocity_ = -1;

	std::cout << leftHip_.getRotation().getX() << "\t" << leftHipVelocity_ << std::endl;

	if (leftHip_.getRotation().getX() == 0 && leftHipVelocity_ == 1)
		leftHipVelocity_ = 1;
	if (leftHip_.getRotation().getX() == 315 && leftHipVelocity_ == -1)
		leftHipVelocity_ = -1;

	leftHip_.rotate(Vector3(leftHipVelocity_, 0, 0));

}

Axis::Axis()
{
	figureTransformation_ = Transformation(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(50, 50, 50));
	xAxis_ = new Shape(Vector3(0.5, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), new Red(), new LineMesh());
	yAxis_ = new Shape(Vector3(0, 0.5, 0), Vector3(0, 0, 90), Vector3(1, 1, 1), new Green(), new LineMesh());
	zAxis_ = new Shape(Vector3(0, 0, 0.5), Vector3(0, 90, 0), Vector3(1, 1, 1), new Blue(), new LineMesh());
}

void Axis::draw()
{
	glPushMatrix();
	{
		figureTransformation_.transform();
		xAxis_->draw();
		yAxis_->draw();
		zAxis_->draw();
	}
	glPopMatrix();
}