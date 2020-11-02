/*
	Max Calhoun
	CS47101 - Computer Graphics
	Assignment 2
	main.cpp
*/

#include <GL/glut.h>
#include <iostream>
#include "Figure.h"

using std::cout;
using std::endl;

// Camera Positioning
float lx = 0.0f, lz = -1.0f; // actual vector representing the camera's direction
float x = 0.0f, z = 5.0f; // XZ position of the camera
float angle = 0.0f; // angle for rotating triangle

bool axisEnabled = true;

Figure* robot = new Robot();
Figure* axis = new Axis();

void processSpecialInput(int key, int xx, int yy)
{
	float fraction = 0.1f;

	switch (key)
	{
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}

void processInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '1':
			static_cast<Robot*>(robot)->makeWireframe();
			break;
		case '2':
			static_cast<Robot*>(robot)->makeSolid();
			break;
		case '3':
			axisEnabled = !axisEnabled;
			break;
		case '4':
			break;
		case 'r':
			break;
		case 'a':
			break;
		case 'p':
			break;
		case 27:
			exit(0);
	}
}

void displayFunction()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera Setup
	glLoadIdentity();
	gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);

	if (axisEnabled)
		axis->draw();

	robot->draw();
	static_cast<Robot*>(robot)->animateWalking();

	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

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

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Maxwell Patrick Calhoun - 811007606");

	// Callbacks
	glutDisplayFunc(displayFunction);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processInput);
	glutSpecialFunc(processSpecialInput);
	glutIdleFunc(displayFunction);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 1;
}