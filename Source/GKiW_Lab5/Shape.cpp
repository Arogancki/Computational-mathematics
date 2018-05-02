#include "stdafx.h"
#include "Shape.h"
#include <algorithm>

#define safe false
#define epsilon 0.01
#define ABS(x) ((x)<0?-(x):(x))
#define PointOutside Point2D(-1,-1)


#define max_size 5

double funMaximum(double a, double b, double c)
{
	if (a > b) {
		if (a > c) {
			return a;
		}
		else {
			return c;
		}
	}
	else {
		if (b > c) {
			return b;
		}
		return c;
	}
}

double funGetDistance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double funGetDistance(Point2D v1, Point2D v2) {
	return funGetDistance(v1.x, v1.y, v2.x, v2.y);
}

bool funAreEqual(double _x, double _y)
{
	return ABS(_x - _y) < epsilon;
}

Point2D funGetMinY2(std::vector<Point2D>& _v)
{
	if (_v.size() == 0)
		throw "Empty vector!";
	double min = _v[0].getY();
	int minIndex = 0;
	double current;
	for (int i = 1; i < _v.size(); i++) {
		current = _v[i].getY();
		if (current < min) {
			minIndex = i;
			min = current;
		}
	}
	return _v[minIndex];
}

Point2D funGetMinX2(std::vector<Point2D>& _v)
{
	if (_v.size() == 0)
		throw "Empty vector!";
	double min = _v[0].getX();
	int minIndex = 0;
	double current;
	for (int i = 1; i < _v.size(); i++) {
		current = _v[i].getX();
		if (current < min) {
			minIndex = i;
			min = current;
		}
	}
	return _v[minIndex];
}

Point3D funGetMinY3(std::vector<Point3D>& _v)
{
	if (_v.size() == 0)
		throw "Empty vector!";
	double min = _v[0].getY();
	int minIndex = 0;
	double current;
	for (int i = 1; i < _v.size(); i++) {
		current = _v[i].getY();
		if (current < min) {
			minIndex = i;
			min = current;
		}
	}
	return _v[minIndex];
}

Point3D funGetMinX3(std::vector<Point3D>& _v)
{
	if (_v.size() == 0)
		throw "Empty vector!";
	double min = _v[0].getX();
	int minIndex = 0;
	double current;
	for (int i = 1; i < _v.size(); i++) {
		current = _v[i].getX();
		if (current < min) {
			minIndex = i;
			min = current;
		}
	}
	return _v[minIndex];
}

Point3D funGetMinZ3(std::vector<Point3D>& _v)
{
	if (_v.size() == 0)
		throw "Empty vector!";
	double min = _v[0].getZ();
	int minIndex = 0;
	double current;
	for (int i = 1; i < _v.size(); i++) {
		current = _v[i].getZ();
		if (current < min) {
			minIndex = i;
			min = current;
		}
	}
	return _v[minIndex];
}

Point2D funGetMaxY2(std::vector<Point2D>& _v)
{
	if (_v.size() == 0)
		throw "Empty vector!";
	double max = _v[0].getY();
	int maxIndex = 0;
	double current;
	for (int i = 1; i < _v.size(); i++) {
		current = _v[i].getY();
		if (current > max) {
			maxIndex = i;
			max = current;
		}
	}
	return _v[maxIndex];
}

Point2D funGetMaxX2(std::vector<Point2D>& _v)
{
	if (_v.size() == 0)
		throw "Empty vector!";
	double max = _v[0].getX();
	int maxIndex = 0;
	double current;
	for (int i = 1; i < _v.size(); i++) {
		current = _v[i].getX();
		if (current > max) {
			maxIndex = i;
			max = current;
		}
	}
	return _v[maxIndex];
}

Point3D funGetMaxY3(std::vector<Point3D>& _v)
{
	if (_v.size() == 0)
		throw "Empty vector!";
	double max = _v[0].getY();
	int maxIndex = 0;
	double current;
	for (int i = 1; i < _v.size(); i++) {
		current = _v[i].getY();
		if (current > max) {
			maxIndex = i;
			max = current;
		}
	}
	return _v[maxIndex];
}

Point3D funGetMaxX3(std::vector<Point3D>& _v)
{
	if (_v.size() == 0)
		throw "Empty vector!";
	double max = _v[0].getX();
	int maxIndex = 0;
	double current;
	for (int i = 1; i < _v.size(); i++) {
		current = _v[i].getX();
		if (current > max) {
			maxIndex = i;
			max = current;
		}
	}
	return _v[maxIndex];
}

Point3D funGetMaxZ3(std::vector<Point3D>& _v)
{
	if (_v.size() == 0)
		throw "Empty vector!";
	double max = _v[0].getZ();
	int maxIndex = 0;
	double current;
	for (int i = 1; i < _v.size(); i++) {
		current = _v[i].getZ();
		if (current > max) {
			maxIndex = i;
			max = current;
		}
	}
	return _v[maxIndex];
}

//Point2d

Point2D::Point2D()
{
	this->x = -1;
	this->y = -1;
}

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

bool Point2D::operator==(const Point2D & lhs)
{
	return lhs.areEqual(lhs, Point2D(x, y));
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

Shape Shape::getCubeAround()
{
	double minX = funGetMinX3(this->getPoints()).x;
	double minY = funGetMinY3(this->getPoints()).y;
	double minZ = funGetMinZ3(this->getPoints()).z;
	
	double maxX = funGetMaxX3(this->getPoints()).x;
	double maxY = funGetMaxY3(this->getPoints()).y;
	double maxZ = funGetMaxZ3(this->getPoints()).z;

	ShapeBuilder shapeBuilder = ShapeBuilder();
	shapeBuilder.add(minX, minY, minZ);
	shapeBuilder.add(maxX, minY, minZ);
	shapeBuilder.add(maxX, minY, maxZ);
	shapeBuilder.add(minX, minY, maxZ);
	shapeBuilder.add(minX, minY, minZ);

	shapeBuilder.add(minX, maxY, minZ);
	shapeBuilder.add(minX, minY, minZ);
	shapeBuilder.add(minX, maxY, minZ);

	shapeBuilder.add(maxX, maxY, minZ);
	shapeBuilder.add(maxX, minY, minZ);
	shapeBuilder.add(maxX, maxY, minZ);
	
	shapeBuilder.add(maxX, maxY, maxZ);
	shapeBuilder.add(maxX, minY, maxZ);
	shapeBuilder.add(maxX, maxY, maxZ);

	shapeBuilder.add(minX, maxY, maxZ);
	shapeBuilder.add(minX, minY, maxZ);
	shapeBuilder.add(minX, maxY, maxZ);

	shapeBuilder.add(minX, maxY, minZ);
	
	return shapeBuilder.getShape(true);
}

double Shape::getFieldOfCube(){
	double width = funGetDistance(this->base[0], this->base[1]);
	double length = funGetDistance(this->base[1], this->base[2]);
	double hight = funGetDistance(this->base[0], this->side1[2]);
	return width * length * hight;
}

bool Shape::isInside(Point3D _pointToCheck)
{
	auto pointOutOfRange = PointOutside;

	auto lineToCheck = Line(pointOutOfRange, Point2D(_pointToCheck.getX(), _pointToCheck.getZ()));
	auto isIsideBottom = isInside(getBase(), lineToCheck);

	lineToCheck = Line(pointOutOfRange, Point2D(_pointToCheck.getX(), _pointToCheck.getY()));
	auto isIsideSide1 = isInside(getSide1(), lineToCheck);

	lineToCheck = Line(pointOutOfRange, Point2D(_pointToCheck.getZ(), _pointToCheck.getY()));
	auto isIsideSide2 = isInside(getSide2(), lineToCheck);

	if (isIsideBottom && isIsideSide1 && isIsideSide2)
	{
		return true;
	}
	return false;
}

bool Shape::isInside(std::vector<Point2D> _shape, Line _lineToCheck)
{
	int intersections = 0;
	std::vector<Point2D> interPoints;
	IntersectionInfo interInfo = NULL;

	// There is possibility to extract this functionality into new method 
	//   but it would requirer passing multiple values by reference 

	// iterate through all points and check how many intersections we have
	for (long i = 1; i < _shape.size(); i++)
	{
		auto currentLine = Line(Point2D(_shape[i - 1].getX(), _shape[i - 1].getY()),
			Point2D(_shape[i].getX(), _shape[i].getY()));
		interInfo = currentLine.intersect(_lineToCheck);
		if (interInfo.intersects)
		{
			if (std::find(interPoints.begin(), interPoints.end(), interInfo.intersection) == interPoints.end()) {
				intersections++;
				if (interInfo.intersection.x >= 0 && interInfo.intersection.y >= 0) {
					interPoints.push_back(interInfo.intersection);
				}
			}
		}
	}
	// check last line from last point to the 1st point
	auto currentLine = Line(Point2D(_shape.front().getX(), _shape.front().getY()),
		Point2D(_shape.back().getX(), _shape.back().getY()));
	interInfo = currentLine.intersect(_lineToCheck);
	if (interInfo.intersects)
	{
		if (std::find(interPoints.begin(), interPoints.end(), interInfo.intersection) == interPoints.end()) {
			intersections++;
			if (interInfo.intersection.x >= 0 && interInfo.intersection.y >= 0) {
				interPoints.push_back(interInfo.intersection);
			}
		}
	}

	// if we have odd number of intersections then point is inside
	if (intersections % 2 == 1)
	{
		return true;
	}
	return false;
}

//Shape end

//ShapeBuilder

void ShapeBuilder::normalize(std::vector<Point3D>& _v)
{
	// przwesuniecie ze zaczynaja sie od 0
	Point3D minX = funGetMinX3(_v);
	Point3D minY = funGetMinY3(_v);
	Point3D minZ = funGetMinZ3(_v);

	for (Point3D &p : _v) {
		p.x += abs(minX.x);
		p.y += abs(minY.y);
		p.z += abs(minZ.z);
	}
	
	minX = funGetMinX3(_v);
	minY = funGetMinY3(_v);
	minZ = funGetMinZ3(_v);

	for (Point3D &p : _v) {
		p.x -= abs(minX.x);
		p.y -= abs(minY.y);
		p.z -= abs(minZ.z);
	}

	// normalizacja rozmiaru

	Point3D maxX = funGetMaxX3(_v);
	Point3D maxY = funGetMaxY3(_v);
	Point3D maxZ = funGetMaxZ3(_v);
	
	double ratio = funMaximum(maxX.x, maxY.y, maxZ.z) / max_size;

	for (Point3D &p : _v) {
		p.x /= ratio;
		p.y /= ratio;
		p.z /= ratio;
	}
}


ShapeBuilder::ShapeBuilder()
{
}

Shape ShapeBuilder::getShape(bool _includes)
{
	normalize(this->points);
	for (Point3D &p : this->points) {
		// check ./shapeBuilderSheme.png for an explaination
		if (!this->contains(base, p.x, p.z))
			this->base.push_back(Point2D(p.x, p.z));
		if (!this->contains(side1, p.x, p.y))
			this->side1.push_back(Point2D(p.x, p.y));
		if (!this->contains(side2, p.z, p.y))
			this->side2.push_back(Point2D(p.z, p.y));
	}
	if (safe) {
		if (this->base.size() < 3 || this->side1.size() < 3 || this->side2.size() < 3)
			throw std::runtime_error("Every side of a shape has to have at least 3 coordinates!");
		//TODO sprawdzic czy kazdy !wezel! ma 3 sasiadow
		// quick and dirty solution - O(n*n)
		for (Point3D &p : this->points) {
			int i = 0;
			for (Point3D &pp : this->points) {
				if (funAreEqual(p.x, pp.x) && funAreEqual(p.y, pp.y) && funAreEqual(p.z, pp.z))
					i++;
			}
			if (i<3)
				throw std::runtime_error("Every point needs to be connected to at least 3 points!");
		}
	}
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

Point2D ShapeBuilder::getMinXBase()
{
	return funGetMinX2(this->base);
}

Point2D ShapeBuilder::getMinXSide1()
{
	return funGetMinX2(this->side1);
}

Point2D ShapeBuilder::getMinXSide2()
{
	return funGetMinX2(this->side2);
}

Point2D ShapeBuilder::getMinYBase()
{
	return funGetMinY2(this->base);
}

Point2D ShapeBuilder::getMinYSide1()
{
	return funGetMinY2(this->side1);
}

Point2D ShapeBuilder::getMinYSide2()
{
	return funGetMinY2(this->side2);
}

Point3D ShapeBuilder::getMinY()
{
	return funGetMinY3(this->points);
}

Point3D ShapeBuilder::getMinX()
{
	return funGetMinX3(this->points);
}

Point3D ShapeBuilder::getMinZ()
{
	return funGetMinZ3(this->points);
}

Point2D ShapeBuilder::getMaxXBase()
{
	return funGetMaxX2(this->base);
}

Point2D ShapeBuilder::getMaxXSide1()
{
	return funGetMaxX2(this->side1);
}

Point2D ShapeBuilder::getMaxXSide2()
{
	return funGetMaxX2(this->side2);
}

Point2D ShapeBuilder::getMaxYBase()
{
	return funGetMaxY2(this->base);
}

Point2D ShapeBuilder::getMaxYSide1()
{
	return funGetMaxY2(this->side1);
}

Point2D ShapeBuilder::getMaxYSide2()
{
	return funGetMaxY2(this->side2);
}

Point3D ShapeBuilder::getMaxY()
{
	return funGetMaxY3(this->points);
}

Point3D ShapeBuilder::getMaxX()
{
	return funGetMaxX3(this->points);
}

Point3D ShapeBuilder::getMaxZ()
{
	return funGetMaxZ3(this->points);
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

Line::Line(Point2D _start, Point2D _end)
{
	start = _start;
	end = _end;
}

// Source: https://github.com/gregsidelnikov/mosaic.js/blob/master/segment.js
IntersectionInfo Line::intersect(Line _lineToCheck)
{
	// a
	double x1 = start.getX();
	double y1 = start.getY();
	double x2 = end.getX();
	double y2 = end.getY();

	// b
	double x3 = _lineToCheck.getStart().getX();
	double y3 = _lineToCheck.getStart().getY();
	double x4 = _lineToCheck.getEnd().getX();
	double y4 = _lineToCheck.getEnd().getY();

	double a1, a2, b1, b2, c1, c2;
	double r1, r2, r3, r4;
	double denom, offset, num;

	a1 = y2 - y1;
	b1 = x1 - x2;
	c1 = (x2 * y1) - (x1 * y2);

	r3 = ((a1 * x3) + (b1 * y3) + c1);
	r4 = ((a1 * x4) + (b1 * y4) + c1);

	if ((r3 != 0) && (r4 != 0) && ((r3 * r4) >= 0))
		return IntersectionInfo(false);

	a2 = y4 - y3; // Compute a2, b2, c2
	b2 = x3 - x4;
	c2 = (x4 * y3) - (x3 * y4);
	r1 = (a2 * x1) + (b2 * y1) + c2; // Compute r1 and r2
	r2 = (a2 * x2) + (b2 * y2) + c2;

	if ((r1 != 0) && (r2 != 0) && ((r1 * r2) >= 0))
		return IntersectionInfo(false);

	denom = (a1 * b2) - (a2 * b1); //Line segments intersect: compute intersection point.

	// równoleg³e co z tym ?
	if (denom == 0)
		return IntersectionInfo(true);

	if (denom < 0) offset = -denom / 2; else offset = denom / 2;

	int x, y;
	num = (b1 * c2) - (b2 * c1);
	if (num < 0) 
		x = (num - offset) / denom; 
	else 
		x = (num + offset) / denom;

	num = (a2 * c1) - (a1 * c2);

	if (num < 0)  
		y = (num - offset) / denom; 
	else 
		y = (num + offset) / denom;

	return IntersectionInfo(Point2D(x, y));
}

Point2D Line::getStart()
{
	return this->start;
}

Point2D Line::getEnd()
{
	return this->end;
}
