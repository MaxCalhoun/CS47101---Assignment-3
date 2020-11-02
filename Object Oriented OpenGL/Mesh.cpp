/*
	Max Calhoun
	Mesh.cpp
*/

#include "Mesh.h"

void CubeMesh::drawMesh() { glutSolidCube(size_); }
void WireCubeMesh::drawMesh() { glutWireCube(size_); }
void SphereMesh::drawMesh() { glutSolidSphere(radius_, slices_, stacks_); }
void WireSphereMesh::drawMesh() { glutWireSphere(radius_, slices_, stacks_); }
void ConeMesh::drawMesh() { glutSolidCone(radius_, height_, slices_, stacks_); }
void WireConeMesh::drawMesh() { glutWireCone(radius_, height_, slices_, stacks_); }

void LineMesh::drawMesh()
{
	glBegin(GL_LINES);
	{
		glVertex3f(-0.5f, 0, 0);
		glVertex3f(0.5f, 0, 0);
	}
	glEnd();
}

void PlaneMesh::drawMesh()
{
	glBegin(GL_QUADS);
	{
		glVertex3f(-0.5f, 0, -0.5f);
		glVertex3f(0.5f, 0, -0.5f);
		glVertex3f(0.5f, 0, 0.5f);
		glVertex3f(-0.5f, 0, 0.5f);
	}
	glEnd();
}

void WirePlaneMesh::drawMesh()
{
	glBegin(GL_LINE_STRIP);
	{
		glVertex3f(-0.5f, 0, -0.5f);
		glVertex3f(0.5f, 0, -0.5f);
		glVertex3f(0.5f, 0, 0.5f);
		glVertex3f(-0.5f, 0, 0.5f);
		glVertex3f(-0.5f, 0, -0.5f);
	}
	glEnd();
}