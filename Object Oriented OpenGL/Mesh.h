/*
	Max Calhoun
	Mesh.h
*/

#pragma once
#include <GL/glut.h>

class Mesh
{
	public:
		virtual void drawMesh() = 0;
};

class CubeMesh : public Mesh
{
	public:
		CubeMesh() : size_(1) {};
		CubeMesh(double s) : size_(s) {};

		virtual void drawMesh() override;

	protected:
		double size_;
};

class WireCubeMesh : public CubeMesh
{
	public:
		WireCubeMesh() : CubeMesh() {};
		WireCubeMesh(double s) : CubeMesh(s) {};

		void drawMesh() final;
};

class SphereMesh : public Mesh
{
	public: 
		SphereMesh() : radius_(0.5), slices_(20), stacks_(20) {};
		SphereMesh(double r, int s1, int s2) : radius_(r), slices_(s1), stacks_(s2) {};

		virtual void drawMesh() override;

	protected:
		double radius_;
		int slices_;
		int stacks_;
};

class WireSphereMesh : public SphereMesh
{
	public:
		WireSphereMesh() : SphereMesh() {};
		WireSphereMesh(double r, int s1, int s2) : SphereMesh(r, s1, s2) {};

		void drawMesh() final;
};

class ConeMesh : public Mesh
{
	public: 
		ConeMesh() : radius_(0.5), height_(1), slices_(20), stacks_(20) {};
		ConeMesh(double r, double h, int s1, int s2) : radius_(r), height_(h), slices_(s1), stacks_(s2) {};

		virtual void drawMesh() override;

	protected:
		double radius_;
		double height_;
		int slices_;
		int stacks_;
};

class WireConeMesh : public ConeMesh
{
	public:
		WireConeMesh() : ConeMesh() {};
		WireConeMesh(double r, double h, int s1, int s2) : ConeMesh(r, h, s1, s2) {};

		void drawMesh() final;
};

class LineMesh : public Mesh
{
	public:
		LineMesh() {};

		void drawMesh() final;
};

class PlaneMesh : public Mesh
{
	public:
		PlaneMesh() {};

		void drawMesh() override;
};

class WirePlaneMesh : public PlaneMesh
{
	public:
		WirePlaneMesh() : PlaneMesh() {};

		void drawMesh() final;
};