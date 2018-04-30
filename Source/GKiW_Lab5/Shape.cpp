#include "stdafx.h"
#include "Shape.h"

#define safe false
#define epsilon 0.01

bool funAreEqual(double _x, double _y)
{
	return fabs(_x - _y) < epsilon;
}

//Point2d

Point2D::Point2D(double _x, double _y)
{
	this->x = _x;
	this->y = _y;
}

double Point2D::getX()
{
	return this->x;
}

double Point2D::getY()
{
	return this->y;
}

bool Point2D::areEqual(Point2D v1, Point2D v2)
{
	return funAreEqual(v1.getX(), v2.getX()) && funAreEqual(v1.getY(), v2.getY());
}

//Point2d end

//Point3d

Point3D::Point3D(double _x, double _y, double _z) : Point2D(_x, _y)
{
	this->z = _z;
}

double Point3D::getZ()
{
	return this->z;
}

bool Point3D::areEqual(Point3D v1, Point3D v2)
{
	return Point2D::areEqual(v1, v2) && funAreEqual(v1.getZ(), v2.getZ());
}

//Point3d end

//Shape

Shape::Shape(bool _includes, std::vector<Point2D> _base, std::vector<Point2D> _side1, 
	std::vector<Point2D> _side2, std::vector<Point3D> _points)
{
	this->includes = _includes;
	this->points = _points;
	this->base = _base;
	this->side1 = _side1;
	this->side2 = _side2;
}

bool Shape::getIncludes()
{
	return this->includes;
}

std::vector<Point2D> Shape::getBase()
{
	return this->base;
}

std::vector<Point2D> Shape::getSide1()
{
	return this->side1;
}

std::vector<Point2D> Shape::getSide2()
{
	return this->side2;
}

std::vector<Point3D> Shape::getPoints()
{
	return this->points;
}

//Shape end

//ShapeBuilder

ShapeBuilder::ShapeBuilder()
{
}

Shape ShapeBuilder::getShape(bool _includes)
{
	if (safe)
		if (this->base.size() < 3 || this->side1.size() < 3 || this->side2.size() < 3)
			throw std::runtime_error("Every side of a shape has to have at least 3 coordinates!");
	return Shape(_includes, this->base, this->side1, this->side2, this->points);
}

void ShapeBuilder::add(double _x, double _y, double _z)
{
	// check if user meant to drawn or just go above (skip) the line
	Point3D point3D = Point3D(_x, _y, _z);
	if (this->points.size() == 0) {
		//this->points.push_back(point3D);
	}
	else {
		Point3D lastPoint3D = this->points[points.size() - 1];
		if (!this->doesLineExist(point3D, lastPoint3D)) {
			this->lines.push_back({ point3D, lastPoint3D });
			this->points.push_back(point3D);
		}
	}
	this->points.push_back(point3D);
	// check ./shapeBuilderSheme.png for an explaination
	if (!this->contains(base, _x, _z))
		this->base.push_back(Point2D(_x, _z));
	if (!this->contains(side1, _x, _y))
		this->side1.push_back(Point2D(_x, _y));
	if (!this->contains(side2, _z, _y))
		this->side2.push_back(Point2D(_z, _y));
}

bool ShapeBuilder::doesLineExist(Point3D p1, Point3D p2)
{
	for (int i = 0; i < this->lines.size(); i++) {
		Point3D l1 = this->lines[i][0];
		Point3D l2= this->lines[i][1];
		if (Point3D::areEqual(l1, p1) && Point3D::areEqual(l2, p2)
			|| Point3D::areEqual(l2, p1) && Point3D::areEqual(l1, p2))
		return true;
	}
	return false;
}

void ShapeBuilder::addTo(double _x, double _y, std::vector<Point2D>& _v)
{
	_v.push_back(Point2D(_x, _y));
}

bool ShapeBuilder::contains(std::vector<Point2D>& _v, double _x, double _y)
{
	for (Point2D e : _v) {
		if (funAreEqual(e.getX(), _x)
			&& funAreEqual(e.getY(), _y))
			return true;
	}
	return false;
}

void ShapeBuilder::addToBase(double _x, double _y)
{
	addTo(_x, _y, this->base);
}

void ShapeBuilder::addToSide1(double _x, double _y)
{
	addTo(_x, _y, this->side1);
}

void ShapeBuilder::addToSide2(double _x, double _y)
{
	addTo(_x, _y, this->side2);
}

//ShapeBuilder end