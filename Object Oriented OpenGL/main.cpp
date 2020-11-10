/*
	Max Calhoun
	CS47101 - Computer Graphics
	Assignment 3
	main.cpp
*/

#include <GL/glut.h>
#include <iostream>
#include "Figure.h"
#include <math.h>

#define PI 3.141592

using std::cout;
using std::endl;

static int windowWidth = 640;
static int windowHeight = 480;
static float aspectRatio;

// Camera Positioning
GLint leftMouseButton, rightMouseButton; //status of the mouse buttons
int mouseX = 0, mouseY = 0; //last known X and Y of the mouse
float cameraTheta, cameraPhi, cameraRadius; //camera position in spherical coordinates
float x, y, z; //camera position in cartesian coordinates

bool axisEnabled = true;
bool animate = false;
bool drawPath = false;
int path = 0;

const float walkVelocity = 0.01f;
float xVelocity = walkVelocity;
float zVelocity = 0;

Shape* ground = new ToggleShape(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(10, 1, 10), new Color(191, 255, 128), new PlaneMesh(), new WirePlaneMesh());
Figure* robot = new Robot(Vector3(0, 1.2f, 0), Vector3(0, 0, 0), Vector3(0.2f, 0.2f, 0.2f));
Figure* axis = new Axis();
Shape* linePath = new Shape(Vector3(0, 0, -2), Vector3(0, 0, 0), Vector3(4, 4, 4), new Purple(), new LineMesh());
Shape* squarePath = new Shape(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(4, 4, 4), new Purple(), new WirePlaneMesh());
Figure* tree = new Tree(Vector3(-4, 0, -4), Vector3(0, 0, 0), Vector3(3, 3, 3));

void recomputeOrientation()
{
	x = cameraRadius * sinf(cameraTheta) * sinf(cameraPhi);
	z = cameraRadius * cosf(cameraTheta) * sinf(cameraPhi);
	y = cameraRadius * cosf(cameraPhi);
	glutPostRedisplay();
}

void mouseCallback(int button, int state, int thisX, int thisY)
{
	//update the left and right mouse button states, if applicable
	if (button == GLUT_LEFT_BUTTON)
		leftMouseButton = state;
	else if (button == GLUT_RIGHT_BUTTON)
		rightMouseButton = state;
	//and update the last seen X and Y coordinates of the mouse
	mouseX = thisX;
	mouseY = thisY;
}

void mouseMotion(int x, int y)
{
	if (leftMouseButton == GLUT_DOWN)
	{
		cameraTheta += (mouseX - x) * 0.005;
		cameraPhi += (mouseY - y) * 0.005;
		// make sure that phi stays within the range (0, PI)
		if (cameraPhi <= 0)
			cameraPhi = 0 + 0.001;
		if (cameraPhi >= PI)
			cameraPhi = PI - 0.001;
		recomputeOrientation(); //update camera (x,y,z)
	}
	// camera zoom in/out
	else if (rightMouseButton == GLUT_DOWN) {
		double totalChangeSq = (x - mouseX) + (y - mouseY);
		cameraRadius += totalChangeSq * 0.01;
		//limit the camera radius to some reasonable values so the user can't get lost
		if (cameraRadius < 2.0)
			cameraRadius = 2.0;
		if (cameraRadius > 10.0)
			cameraRadius = 10.0;
		recomputeOrientation();     //update camera (x,y,z) based on (radius,theta,phi)
	}
	mouseX = x;
	mouseY = y;
}

void resetRobotPosition()
{
	robot->setTranslation(Vector3(0, 1.2f, -2));
	robot->setRotation(Vector3(0, 90, 0));
	xVelocity = walkVelocity;
	zVelocity = 0;
}

void animateRobot()
{
	static_cast<Robot*>(robot)->animateWalking();

	if (path == 0)
	{
		// Left Point
		if (robot->getTranslation().getX() <= -1.95f && robot->getTranslation().getX() > -2.05f)
		{
			robot->rotate(Vector3(0, 180, 0));
			xVelocity = walkVelocity;
			zVelocity = 0;
		}

		// Right Point
		if (robot->getTranslation().getX() >= 1.95f && robot->getTranslation().getX() < 2.05f)
		{
			robot->rotate(Vector3(0, 180, 0));
			xVelocity = -walkVelocity;
			zVelocity = 0;
		}
	}
	else if (path == 1)
	{
		// Back Left Point
		if ((robot->getTranslation().getX() <= -1.95f && robot->getTranslation().getX() > -2.05f) && (robot->getTranslation().getZ() <= -1.95f && robot->getTranslation().getZ() > -2.05f))
		{
			robot->setRotation(Vector3(0, 90, 0));
			xVelocity = walkVelocity;
			zVelocity = 0;
		}

		// Back Right Point
		if ((robot->getTranslation().getX() >= 1.95f && robot->getTranslation().getX() < 2.05f) && (robot->getTranslation().getZ() <= -1.95f && robot->getTranslation().getZ() > -2.05f))
		{
			robot->setRotation(Vector3(0, 0, 0));
			xVelocity = 0;
			zVelocity = walkVelocity;
		}

		// Front Left Point
		if ((robot->getTranslation().getX() <= -1.95f && robot->getTranslation().getX() > -2.05f) && (robot->getTranslation().getZ() >= 1.95f && robot->getTranslation().getZ() < 2.05f))
		{
			robot->setRotation(Vector3(0, 180, 0));
			xVelocity = 0;
			zVelocity = -walkVelocity;
		}

		// Front Right Point
		if ((robot->getTranslation().getX() >= 1.95f && robot->getTranslation().getX() < 2.05f) && (robot->getTranslation().getZ() >= 1.95f && robot->getTranslation().getZ() < 2.05f))
		{
			robot->setRotation(Vector3(0, 270, 0));
			xVelocity = -walkVelocity;
			zVelocity = 0;
		}
	}

	robot->translate(Vector3(xVelocity, 0, zVelocity));
}

void processInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '1': // Make Wireframe
			static_cast<Robot*>(robot)->makeWireframe();
			static_cast<ToggleShape*>(ground)->makeWireframe();
			static_cast<Tree*>(tree)->makeWireframe();
			ground->changeColor(new White);
			break;
		case '2': // Make Solid
			static_cast<Robot*>(robot)->makeSolid();
			static_cast<ToggleShape*>(ground)->makeSolid();
			static_cast<Tree*>(tree)->makeSolid();
			ground->changeColor(new Color(191, 255, 128));
			break;
		case '3': // Toggle Axis
			axisEnabled = !axisEnabled;
			break;
		case '4': // Toggle Path Visibility
			drawPath = !drawPath;
			break;
		case 'r': // Reset Robot Position
			resetRobotPosition();
			break;
		case 'a': // Toggle Robot Animation
			animate = !animate;
			break;
		case 'p': // Cycle Path Options
			++path;
			if (path == 2)
				path = 0;
			resetRobotPosition();
			break;
		case 27: // Exit Program
			exit(0);
	}
}

void displayFunction()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera Setup
	glLoadIdentity();

	gluLookAt(x, y, z, 0, 0, 0, 0.0f, 1.0f, 0.0f);

	if (axisEnabled)
		axis->draw();
	
	if (drawPath == true)
	{
		if (path == 0)
			linePath->draw();
		else if (path == 1)
			squarePath->draw();
	}

	if (animate == true)
		animateRobot();
	
	robot->draw();
	ground->draw();
	tree->draw();

	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0f / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void printDirections()
{
	cout << "MODEL CONTROLS" << endl;
	cout << "\t1 - Wireframe Mode\n"
			"\t2 - Solid Mode\n"
			"\t3 - Toggle Axis\n"
			"\t4 - Toggle Path Visibility\n"
			"\tr - Reset Robot Position\n"
			"\ta - Toggle Robot Animation\n"
			"\tp - Cycle Path Options\n"
			"\tEsc - Terminate Program\n"
		<< endl;

	cout << "MOUSE CONTROLS" << endl;
	cout << "\tRotate Model - Left Mouse Button + Mouse Movement\n"
			"\tScale Model - Right Mouse Button + Mouse Movement\n"
		<< endl;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Maxwell Patrick Calhoun - 811007606");

	printDirections();
	resetRobotPosition();

	//give the camera a 'pretty' starting point!
	cameraRadius = 7.0f;
	cameraTheta = 2.80;
	cameraPhi = 2.0;
	recomputeOrientation();

	// Callbacks
	glutDisplayFunc(displayFunction);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processInput);
	glutIdleFunc(displayFunction);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseMotion);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 1;
}