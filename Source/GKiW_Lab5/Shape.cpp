#include "stdafx.h"
#include "Shape.h"

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

//Shape end

//ShapeBuilder

ShapeBuilder::ShapeBuilder()
{
}

Shape ShapeBuilder::getShape(bool _includes)
{
	if (this->base.size() < 3 || this->side1.size() < 3 || this->side2.size() < 3)
		throw std::runtime_error("Every side of a shape has to have at least 3 coordinates!");
	return Shape(_includes, this->base, this->side1, this->side2, this->points);
}

void ShapeBuilder::add(double _x, double _y, double _z)
{
	points.push_back(Point3D(_x, _y, _z));
	// check ./shapeBuilderSheme.png for an explaination
	if (!this->contains(base, _x, _z))
		this->base.push_back(Point2D(_x, _z));
	if (!this->contains(side1, _x, _y))
		this->side1.push_back(Point2D(_x, _y));
	if (!this->contains(side2, _z, _y))
		this->side2.push_back(Point2D(_z, _y));
}

void ShapeBuilder::addTo(double _x, double _y, std::vector<Point2D>& _v)
{
	_v.push_back(Point2D(_x, _y));
}

bool ShapeBuilder::areEqual(double _x, double _y)
{
	return fabs(_x - _y) < 0.1;
}

bool ShapeBuilder::contains(std::vector<Point2D>& _v, double _x, double _y)
{
	for (Point2D e : _v) {
		if (areEqual(e.getX(), _x) 
			&& areEqual(e.getY(), _y))
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