#include "stdafx.h"
#include "Shape.h"

#define safe false
#define epsilon 0.01
#define ABS(x) ((x)<0?-(x):(x))

#define max_x 10
#define max_y 10
#define max_z 10

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

double funNormalize(double val, double min, double max) {
	return (val - min) / (max - min);
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

void ShapeBuilder::normalize(std::vector<Point2D>& _v)
{
	Point2D minX = funGetMinX2(_v);
	Point2D minY = funGetMinY2(_v);
	for (Point2D p : _v){
		p.x += minX.x;
		p.y += minY.y;
	}
	minX = funGetMinX2(_v);
	minY = funGetMinY2(_v);
	Point2D maxX = funGetMaxX2(_v);
	Point2D maxY = funGetMaxY2(_v);

	double d_minX = minX.x < 0 ? 0 : minX.x;
	double d_minY = minY.y < 0 ? 0 : minY.y;
	double d_maxX = maxX.x > max_x ? max_x : maxX.x;
	double d_maxY = maxY.y > max_y ? max_y : maxY.y;

	for (Point2D p : _v) {
		p.x = funNormalize(p.x, d_minX, d_maxX);
		p.y = funNormalize(p.y, d_minY, d_maxY);
	}
}

void ShapeBuilder::normalize(std::vector<Point3D>& _v)
{
	Point3D minX = funGetMinX3(_v);
	Point3D minY = funGetMinY3(_v);
	Point3D minZ = funGetMinZ3(_v);
	for (Point3D p : _v) {
		p.x += minX.x;
		p.y += minY.y;
		p.z += minZ.z;
	}
	minX = funGetMinX3(_v);
	minY = funGetMinY3(_v);
	minZ = funGetMinZ3(_v);
	Point3D maxX = funGetMaxX3(_v);
	Point3D maxY = funGetMaxY3(_v);
	Point3D maxZ = funGetMaxZ3(_v);

	double d_minX = minX.x < 0 ? 0 : minX.x;
	double d_minY = minY.y < 0 ? 0 : minY.y;
	double d_minZ = minZ.z < 0 ? 0 : minZ.z;
	double d_maxX = maxX.x > max_x ? max_x : maxX.x;
	double d_maxY = maxY.y > max_y ? max_y : maxY.y;
	double d_maxZ = maxZ.z > max_z ? max_z : maxZ.z;

	for (Point3D p : _v) {
		p.x = funNormalize(p.x, d_minX, d_maxX);
		p.y = funNormalize(p.y, d_minY, d_maxY);
		p.z = funNormalize(p.z, d_minZ, d_maxZ);
	}
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
	normalize(this->base);
	normalize(this->side1);
	normalize(this->side2);
	normalize(this->points);
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