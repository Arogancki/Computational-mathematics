#include "stdafx.h"
#include "Shape.h"
#include <algorithm>
#include <math.h> 

#define safe false
#define epsilon 0.01
#define ABS(x) ((x)<0?-(x):(x))
#define PointOutside Point2D(-1,-1)
#define M_PI 3.14159265358979323846

#define max_size 4
extern float GetRandomFloat(float min = 0, float max = 1);

double funGetDistance(double, double, double, double);


Shape funMakeRectangle(double minX, double maxX, double minY, double maxY, double minZ, double maxZ) {
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

	return shapeBuilder.getShape(true, false);
}

double funGetYfromPoints(double x1, double y1, double x2, double y2, double x) {
	return ((y2 - y1)*(x - x1)) / (x2 - x1) + y1;
}

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

Point2D funGetPointAway(double x1, double y1, double x2, double y2, double distance) {
	Point2D w = Point2D(x2 - x1, y2 - y1);
	double a = distance / sqrt(pow(w.x, 2) + pow(w.y, 2));
	return Point2D(x1 + (w.x*a), y1 + (w.y*a));
}

Point2D funGetPointAway(Point2D v1, Point2D v2, double distance) {
	return funGetPointAway(v1.x, v1.y, v2.x, v2.y, distance);
}

double radToDeg(double x) {
	return x * 57.2957795130;
}

double degToRad(double x) {
	return (x * (M_PI / 180.0));
}

double funGetAngle(double x0, double y0, double x1, double y1, double x2, double y2) {
	x1 -= x0;
	x2 -= x0;
	y1 -= y0;
	y2 -= y0;
	double d = (x1*x2) + (y1*y2);
	double l1 = sqrt(pow(x1, 2) + pow(y1, 2));
	double l2 = sqrt(pow(x2, 2) + pow(y2, 2));
	return acos(d / (l1*l2));
}

Point2D funSpinPoint(double x, double y, double angleRad) {
	double s = sin(angleRad);
	double c = cos(angleRad);
	Point2D er = Point2D((x*c) + (y*s), (y*c) - (s*x));
	return er;
}

double funGetAngle(Point2D v0, Point2D v1, Point2D v2) {
	return funGetAngle(v0.x, v0.y, v1.x, v1.y, v2.x, v2.y);
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

Point3D::Point3D(double _x, double _y, double _z, bool _B, bool _F, bool _S) : Point2D(_x, _y)
{
	this->B = _B;
	this->F = _F;
	this->S = _S;
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
bool funDoesContain(std::vector<Point3D> _v, Point3D _p) {
	for (Point3D p : _v) {
		if (Point3D::areEqual(p, _p))
			return true;
	}
	return false;
}

rectangleMethodResults Shape::rectangleMethod(int n) {
	std::vector<std::vector<Point2D>> rB = rectangleMethod2d(this->base, n);
	std::vector<std::vector<Point2D>> rS1 = rectangleMethod2d(this->side1, n);
	std::vector<std::vector<Point2D>> rS2 = rectangleMethod2d(this->side2, n);
	std::vector<Shape> rectangles = std::vector<Shape>();
	std::vector<Shape> projections = std::vector<Shape>();

	double field = 0.0;

	for (int i = 0; i < rB.size(); i++) {
		double baseLenght = funGetDistance(Point2D(rB[i][1].x, rB[i][1].y), Point2D(rB[i][2].x, rB[i][2].y));
		double side2Lenght = funGetDistance(Point2D(rS2[i][0].x, rS2[i][0].y), Point2D(rS2[i][1].x, rS2[i][1].y));
		int amonth = (int)(baseLenght / side2Lenght);
		
		double distance = baseLenght / amonth;

		for (int j = 0; j < amonth; j++) {
			ShapeBuilder shapeBuilder = ShapeBuilder();
			
			Point2D floor1 = funGetPointAway(rS1[i][0].x, rS1[i][0].y, rB[i][3].x, rB[i][3].y, distance*j);
			Point2D floor2 = funGetPointAway(rS1[i][1].x, rS1[i][1].y, rB[i][2].x, rB[i][2].y, distance*j);
			Point2D floor3 = funGetPointAway(rS1[i][1].x, rS1[i][1].y, rB[i][2].x, rB[i][2].y, distance*(j + 1));
			Point2D floor4 = funGetPointAway(rS1[i][0].x, rS1[i][0].y, rB[i][3].x, rB[i][3].y, distance*(j + 1));

			double heightS1 = funGetDistance(rS1[i][1], rS1[i][2]);
			double heightS2 = funGetDistance(rS2[j][1], rS2[j][2]);
			double floorYStart, floorYEnd;
			if (heightS1 < heightS2) {
				floorYStart = rS1[i][1].y;
				floorYEnd = rS1[i][2].y;
			}
			else {
				floorYStart = rS2[j][1].y;
				floorYEnd = rS2[j][2].y;
			}

			shapeBuilder.add(floor1.x, floorYStart, floor1.y);
			shapeBuilder.add(floor2.x, floorYStart, floor2.y);
			shapeBuilder.add(floor3.x, floorYStart, floor3.y);
			shapeBuilder.add(floor4.x, floorYStart, floor4.y);
			shapeBuilder.add(floor1.x, floorYStart, floor1.y);

			shapeBuilder.add(floor1.x, floorYEnd, floor1.y);
			shapeBuilder.add(floor2.x, floorYEnd, floor2.y); 
			shapeBuilder.add(floor2.x, floorYStart, floor2.y);
			shapeBuilder.add(floor2.x, floorYEnd, floor2.y);
									   
			shapeBuilder.add(floor3.x, floorYEnd, floor3.y);
			shapeBuilder.add(floor3.x, floorYStart, floor3.y);
			shapeBuilder.add(floor3.x, floorYEnd, floor3.y);
			shapeBuilder.add(floor4.x, floorYEnd, floor4.y); 
			shapeBuilder.add(floor4.x, floorYStart, floor4.y);
			shapeBuilder.add(floor4.x, floorYEnd, floor4.y);
			shapeBuilder.add(floor1.x, floorYEnd, floor1.y);

			Shape s = shapeBuilder.getShape(true, false);
			field += s.getFieldOfCube();
			rectangles.push_back(s);
		}
		
		if (true) {
			// cienie rzutow
			// podstawa
			ShapeBuilder shapeBuilder1 = ShapeBuilder();
			shapeBuilder1.add(rB[i][0].x, 0, rB[i][0].y);
			shapeBuilder1.add(rB[i][1].x, 0, rB[i][1].y);
			shapeBuilder1.add(rB[i][2].x, 0, rB[i][2].y);
			shapeBuilder1.add(rB[i][3].x, 0, rB[i][3].y);
			shapeBuilder1.add(rB[i][0].x, 0, rB[i][0].y);
			Shape s1 = shapeBuilder1.getShape(true, false);

			// side1
			ShapeBuilder shapeBuilder2 = ShapeBuilder();
			shapeBuilder2.add(rS1[i][0].x, rS1[i][0].y, 0.0);
			shapeBuilder2.add(rS1[i][1].x, rS1[i][1].y, 0.0);
			shapeBuilder2.add(rS1[i][2].x, rS1[i][2].y, 0.0);
			shapeBuilder2.add(rS1[i][3].x, rS1[i][3].y, 0.0);
			shapeBuilder2.add(rS1[i][0].x, rS1[i][0].y, 0.0);
			shapeBuilder2.add(rS1[i][0].x, rS1[i][0].y, 0.0);
			Shape s2 = shapeBuilder2.getShape(true, false);

			// side2
			ShapeBuilder shapeBuilder3 = ShapeBuilder();
			shapeBuilder3.add(0, rS2[i][0].y, rS2[i][0].x);
			shapeBuilder3.add(0, rS2[i][1].y, rS2[i][1].x);
			shapeBuilder3.add(0, rS2[i][2].y, rS2[i][2].x);
			shapeBuilder3.add(0, rS2[i][3].y, rS2[i][3].x);
			shapeBuilder3.add(0, rS2[i][0].y, rS2[i][0].x);
			Shape s3 = shapeBuilder3.getShape(true, false);

			projections.push_back(s1);
			projections.push_back(s2);
			projections.push_back(s3);
		}
		
	}

	return rectangleMethodResults(field, rectangles, projections);
}

monteCarloMethodResults Shape::monteCarloMethod(int _numberOfPoints)
{
	std::vector<Point3D> hitPoints;
	std::vector<Point3D> missPoints;

	auto borderShape = getCubeAround();
	CubeBorder border = borderShape.getCubeAroundPointRange();

	for (int i = 0; i < _numberOfPoints; i++)
	{
		auto point = Point3D(GetRandomFloat(border.minimumPoint.getX(), border.maximumPoint.getX()),
			GetRandomFloat(border.minimumPoint.getY(), border.maximumPoint.getY()),
			GetRandomFloat(border.minimumPoint.getZ(), border.maximumPoint.getZ()));
		if (isInside(point))
		{
			hitPoints.push_back(point);
		}
		else
		{
			missPoints.push_back(point);
		}
	}

	auto x = border.maximumPoint.x - border.minimumPoint.x;
	auto y = border.maximumPoint.y - border.minimumPoint.y;
	auto z = border.maximumPoint.z - border.minimumPoint.z;
	auto volueOfCubeAroundShape = x * y * z;
	auto size = hitPoints.size();
	float volueOfShape = volueOfCubeAroundShape * ((float)size / (float)_numberOfPoints);

	return monteCarloMethodResults(hitPoints, missPoints, volueOfShape / volueOfCubeAroundShape, includes);
}

rectangleMethodResults Shape::rectangleMethod2(int n)
{
	// ten sposob nie zadziala dla bardziej skomplikowanych figur
	// trzeba robic to dla rzutow z wykorzystaniem funGetYfromPoints

	Point3D main = this->points[0];
	std::vector<Point3D> connectedToMain = std::vector<Point3D>();
	bool nextIsConnectedToMain = false;
	int previousIndex = -1;
	for (Point3D p : this->points) {
		if (Point3D::areEqual(main, p)) {
			// the current is a main so the next and the previous is connected
			nextIsConnectedToMain = true;
			if (previousIndex != -1 && !Point3D::areEqual(main, this->points[previousIndex]) && !funDoesContain(connectedToMain, this->points[previousIndex])) {
				connectedToMain.push_back(this->points[previousIndex]);
			}
		}
		else {
			if (nextIsConnectedToMain) {
				// the current is connected to main because main was previous
				if (!funDoesContain(connectedToMain, p)) {
					connectedToMain.push_back(p);
				}
			}
			nextIsConnectedToMain = false;
		}
		previousIndex++;
	}
	if (connectedToMain.size() > 3) {
		throw "To many point connected to main node to use rectangle method!";
	}
	if (connectedToMain.size() < 3) {
		throw "To less point connected to main node to use rectangle method!";
	}

	// check with connected is x,y,z different
	std::vector<int> xDifferent = std::vector<int>();
	std::vector<int> yDifferent = std::vector<int>();
	std::vector<int> zDifferent = std::vector<int>();
	for (int i = 0; i < connectedToMain.size(); i++) {
		bool isInserted = false;
		if (!funAreEqual(connectedToMain[i].x, main.x)) {
			isInserted = true;
			xDifferent.push_back(i);
		}
		if (!funAreEqual(connectedToMain[i].y, main.y)) {
			isInserted = true;
			yDifferent.push_back(i);
		}
		if (!funAreEqual(connectedToMain[i].z, main.z)) {
			isInserted = true;
			zDifferent.push_back(i);
		}
		if (!isInserted) {
			throw "(0) Shape volume cannot be calculated with rectangle method!";
		}
	}

	// select with one is going to be xnode ynode znode
	if (xDifferent.size() < 1) {
		throw "(1) Shape volume cannot be calculated with rectangle method!";
	}
	if (yDifferent.size() < 1) {
		throw "(2) Shape volume cannot be calculated with rectangle method!";
	}
	if (zDifferent.size() < 1) {
		throw "(3) Shape volume cannot be calculated with rectangle method!";
	}
	Point3D *xNode = NULL;
	Point3D *yNode = NULL;
	Point3D *zNode = NULL;
	int i = 0;
	while (true) {
		// safe error 
		if (i++ == 100) {
			throw "(x) Shape volume cannot be calculated with rectangle method!";
		}
		// check if any has one left
		if (xDifferent.size() == 1) {
			int index = xDifferent[0];
			xNode = &(connectedToMain[index]);
			// remove from others
			xDifferent.clear();
			std::vector<int>::iterator positionY = std::find(yDifferent.begin(), yDifferent.end(), index);
			if (positionY != yDifferent.end())
				yDifferent.erase(positionY);
			std::vector<int>::iterator positionZ = std::find(zDifferent.begin(), zDifferent.end(), index);
			if (positionZ != zDifferent.end())
				zDifferent.erase(positionZ);
			// end remove from others
		}
		if (yDifferent.size() == 1) {
			int index = yDifferent[0];
			yNode = &(connectedToMain[index]);
			// remove from others
			std::vector<int>::iterator positionX = std::find(xDifferent.begin(), xDifferent.end(), index);
			if (positionX != xDifferent.end())
				xDifferent.erase(positionX);
			yDifferent.clear();
			std::vector<int>::iterator positionZ = std::find(zDifferent.begin(), zDifferent.end(), index);
			if (positionZ != zDifferent.end())
				zDifferent.erase(positionZ);
			// end remove from others
		}
		if (zDifferent.size() == 1) {
			int index = zDifferent[0];
			zNode = &(connectedToMain[index]);
			// remove from others
			std::vector<int>::iterator positionX = std::find(xDifferent.begin(), xDifferent.end(), index);
			if (positionX != xDifferent.end())
				xDifferent.erase(positionX);
			std::vector<int>::iterator positionY = std::find(yDifferent.begin(), yDifferent.end(), index);
			if (positionY != yDifferent.end())
				yDifferent.erase(positionY);
			zDifferent.clear();
			// end remove from others
		}
		// check if has something unique
		for (int index : xDifferent) {
			std::vector<int>::iterator positionY = std::find(yDifferent.begin(), yDifferent.end(), index);
			std::vector<int>::iterator positionZ = std::find(zDifferent.begin(), zDifferent.end(), index);
			if (positionY == yDifferent.end() && positionZ == zDifferent.end())
			{
				xNode = &(connectedToMain[index]);
				// remove from others
				xDifferent.clear();
				std::vector<int>::iterator positionY = std::find(yDifferent.begin(), yDifferent.end(), index);
				if (positionY != yDifferent.end())
					yDifferent.erase(positionY);
				std::vector<int>::iterator positionZ = std::find(zDifferent.begin(), zDifferent.end(), index);
				if (positionZ != zDifferent.end())
					zDifferent.erase(positionZ);
				// end remove from others
				break;
			}
		}
		for (int index : yDifferent) {
			std::vector<int>::iterator positionX = std::find(xDifferent.begin(), xDifferent.end(), index);
			std::vector<int>::iterator positionZ = std::find(zDifferent.begin(), zDifferent.end(), index);
			if (positionX == xDifferent.end() && positionZ == zDifferent.end())
			{
				yNode = &(connectedToMain[index]);
				// remove from others
				std::vector<int>::iterator positionX = std::find(xDifferent.begin(), xDifferent.end(), index);
				if (positionX != xDifferent.end())
					xDifferent.erase(positionX);
				yDifferent.clear();
				std::vector<int>::iterator positionZ = std::find(zDifferent.begin(), zDifferent.end(), index);
				if (positionZ != zDifferent.end())
					zDifferent.erase(positionZ);
				// end remove from others
				break;
			}
		}
		for (int index : zDifferent) {
			std::vector<int>::iterator positionX = std::find(xDifferent.begin(), xDifferent.end(), index);
			std::vector<int>::iterator positionY = std::find(yDifferent.begin(), yDifferent.end(), index);
			if (positionX == xDifferent.end() && positionY == yDifferent.end())
			{
				zNode = &(connectedToMain[index]);
				// remove from others
				std::vector<int>::iterator positionX = std::find(xDifferent.begin(), xDifferent.end(), index);
				if (positionX != xDifferent.end())
					xDifferent.erase(positionX);
				std::vector<int>::iterator positionY = std::find(yDifferent.begin(), yDifferent.end(), index);
				if (positionY != yDifferent.end())
					yDifferent.erase(positionY);
				zDifferent.clear();
				// end remove from others
				break;
			}
		}
		// take from one randomly (first)
		if (xDifferent.size() > 0) {
			int index = xDifferent[0];
			xNode = &(connectedToMain[index]);
			// remove from others
			xDifferent.clear();
			std::vector<int>::iterator positionY = std::find(yDifferent.begin(), yDifferent.end(), index);
			if (positionY != yDifferent.end())
				yDifferent.erase(positionY);
			std::vector<int>::iterator positionZ = std::find(zDifferent.begin(), zDifferent.end(), index);
			if (positionZ != zDifferent.end())
				zDifferent.erase(positionZ);
			// end remove from others
		}
		else if (yDifferent.size() > 0) {
			int index = yDifferent[0];
			yNode = &(connectedToMain[index]);
			// remove from others
			std::vector<int>::iterator positionX = std::find(xDifferent.begin(), xDifferent.end(), index);
			if (positionX != xDifferent.end())
				xDifferent.erase(positionX);
			yDifferent.clear();
			std::vector<int>::iterator positionZ = std::find(zDifferent.begin(), zDifferent.end(), index);
			if (positionZ != zDifferent.end())
				zDifferent.erase(positionZ);
			// end remove from others
		}
		else if (zDifferent.size() > 0) {
			int index = zDifferent[0];
			zNode = &(connectedToMain[index]);
			// remove from others
			std::vector<int>::iterator positionX = std::find(xDifferent.begin(), xDifferent.end(), index);
			if (positionX != xDifferent.end())
				xDifferent.erase(positionX);
			std::vector<int>::iterator positionY = std::find(yDifferent.begin(), yDifferent.end(), index);
			if (positionY != yDifferent.end())
				yDifferent.erase(positionY);
			zDifferent.clear();
		}
		// if all y x z nodes != null leave the loop
		if (xNode != NULL && yNode != NULL && zNode != NULL) {
			break;
		}
	}
	// end select with one is going to be xnode ynode znod

	// get points on lines
	std::vector<double> x = std::vector<double>();
	std::vector<double> y = std::vector<double>();
	std::vector<double> z = std::vector<double>();
	double xLength = funGetDistance(main.x, xNode->x, main.y, main.y);
	double yLength = funGetDistance(main.x, main.x, main.y, yNode->y);
	double zLength = funGetDistance(main.x, main.x, main.z, zNode->z);
	for (int i = 1; i <= n; i++) {
		x.push_back((xLength / n)*i);
	}
	for (int i = 1; i <= n; i++) {
		y.push_back((yLength / n)*i);
	}
	for (int i = 1; i <= n; i++) {
		z.push_back((zLength / n)*i);
	}
	double cubeVolume = (xLength / n) * (yLength / n) * (zLength / n);
	double shapeVolume = cubeVolume * x.size() * y.size() * z.size();

	std::vector<Shape> rectangles = std::vector<Shape>();
	for (int xi = 0; xi < x.size(); xi++) {
		for (int yi = 0; yi < y.size(); yi++) {
			for (int zi = 0; zi < z.size(); zi++) {
				double startX = xi > 0 ? main.x + x[xi - 1] : main.x;
				double startY = yi > 0 ? main.y + y[yi - 1] : main.y;
				double startZ = zi > 0 ? main.z + z[zi - 1] : main.z;
				double endX = main.x + x[xi];
				double endY = main.y + y[yi];
				double endZ = main.z + z[zi];
				rectangles.push_back(funMakeRectangle(startX, endX, startY, endY, startZ, endZ));
			}
		}
	}

	return rectangleMethodResults(shapeVolume, rectangles);
}

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

	return shapeBuilder.getShape(true, false);
}

CubeBorder Shape::getCubeAroundPointRange()
{
	double minX = funGetMinX3(this->getPoints()).x;
	double minY = funGetMinY3(this->getPoints()).y;
	double minZ = funGetMinZ3(this->getPoints()).z;

	double maxX = funGetMaxX3(this->getPoints()).x;
	double maxY = funGetMaxY3(this->getPoints()).y;
	double maxZ = funGetMaxZ3(this->getPoints()).z;

	CubeBorder border = CubeBorder(Point3D(minX, minY, minZ), Point3D(maxX, maxY, maxZ));
	return border;
}

double Shape::getFieldOfCube() {
	if (this->base.size() < 3 || this->side1.size() < 3)
		return 0.0;
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

double Shape::getMax_size()
{
	return max_size;
}

std::vector<std::vector<Point2D>> Shape::rectangleMethod2d(std::vector<Point2D>& _v, int n)
{
	std::vector<std::vector<Point2D>> rectangles = std::vector<std::vector<Point2D>>();
	// znajdz najdlasze punkty ktore beda wziete jako podstawa
	for (int i = 0; i < _v.size(); i++) {
		for (int j = 0; j < _v.size(); j++) {
			if (i == j)
				continue;
			if (Point2D::areEqual(_v[i], _v[j]))
				throw "Rectangle method - projection cannot have a point connected more then once!";
		}
	}

	int index1 = -1;
	double max = 0.0;
	int index2 = -1;
	bool breakflag = false;
	for (int i = 0; i < _v.size(); i++) {
		int j = i + 1;
		if (j >= _v.size()){
			j = 0;
			breakflag = true;
		}
		double distance = funGetDistance(_v[i], _v[j]);
		if (distance > max) {
			index2 = j;
			max = distance;
			index1 = i;
		}
		if (breakflag)
			break;
	}
	if (funAreEqual(0.0, max)) {
		throw "Rectangle method - not enought points!";
	}
	
	// TODO narazie wyniki najdluzszej podstwy sa olewane i brany jest Pierwszy rozmiar
	index1 = 0;
	index2 = 1;

	Point2D first = _v[index1];
	Point2D last = _v[index2];
	Point2D firstGlobal = first;
	Point2D lastGlobal = last;

	// przesuniecie punktów wedlug first do 0,0 0,0
	double shiftX = first.x;
	double shiftY = first.y;
	first.x = 0.0;
	first.y = 0.0;
	last.x -= shiftX;
	last.y -= shiftY;
	double distance = funGetDistance(first, last);
	Point2D tempLast = funGetPointAway(first, Point2D(1.0, 0.0), distance);
	double angle = funGetAngle(first, last, tempLast);

	// take ffirst line and devide it into n pieces
	double step = distance / ((double)n);
	double currentStep = step;
	int currentIndex = index1 - 1;
	int poprzedniIndex = index1;
	do {
		if (currentIndex < 0) {
			currentIndex = _v.size() - 1;
		}
		if (currentIndex == index1) {
			break;
		}

		// logika 
		// znalezienie odpowiednio odleglego punktu na podstawie
		// przesuniecie punktów wedlug first do 0,0 0,0
		Point2D currentPoint = _v[currentIndex];
		currentPoint.x -= shiftX; 
		currentPoint.y -= shiftY;

		//double fk = radToDeg(funGetAngle(first, last, currentPoint));
		//double lk = radToDeg(funGetAngle(last, first, currentPoint));
		//double ck = radToDeg(funGetAngle(currentPoint, first, last));

		currentPoint = funSpinPoint(currentPoint.x, currentPoint.y, angle);

		//double fk2 = radToDeg(funGetAngle(first, tempLast, currentPoint));
		//double lk2 = radToDeg(funGetAngle(tempLast, first, currentPoint));
		//double ck2 = radToDeg(funGetAngle(currentPoint, first, tempLast));
		// po tych doublaach mozna sprawdzic czy wykonany obrot jest ok

		Point2D prevPoint = _v[poprzedniIndex];
		prevPoint.x -= shiftX;
		prevPoint.y -= shiftY;
		prevPoint = funSpinPoint(prevPoint.x, prevPoint.y, angle);

		// punkty sa znormalizowane tu
		do {
			Point2D basePoint = funGetPointAway(first, tempLast, currentStep);
			Point2D highPoint = basePoint;

			highPoint.y = funGetYfromPoints(prevPoint.x, prevPoint.y, currentPoint.x, currentPoint.y, highPoint.x);

			double distanceToHigh = funGetDistance(prevPoint, highPoint);
			double distanceToCurent = funGetDistance(prevPoint, currentPoint);
			if (distanceToHigh > distanceToCurent) {
				// should be next point already
				break;
			}

			// policzyc odleglosci od punktow bazowych
			double fromFirst = funGetDistance(first, basePoint);
			double fromCurrent = funGetDistance(currentPoint, highPoint);
			
			Point2D realfloor1 = funGetPointAway(firstGlobal, lastGlobal, fromFirst - step);
			Point2D realfloor2 = funGetPointAway(firstGlobal, lastGlobal, fromFirst);
			Point2D realCeil2 = funGetPointAway(_v[currentIndex], _v[poprzedniIndex], fromCurrent);

			double midleLenght = funGetDistance(realfloor1, realCeil2);
			Point2D middle = funGetPointAway(realfloor1, realCeil2, midleLenght/2.0);
			midleLenght = funGetDistance(realfloor2, middle);
			Point2D realCeil1 = funGetPointAway(realfloor2, middle, midleLenght*2);

			std::vector<Point2D> rectangle = std::vector<Point2D>();
			rectangle.push_back(realfloor1);
			rectangle.push_back(realfloor2);
			rectangle.push_back(realCeil2);
			rectangle.push_back(realCeil1);

			rectangles.push_back(rectangle);

			currentStep += step;
		} while(true) ;

		poprzedniIndex = currentIndex;
		currentIndex--;
	} while (true);
	return rectangles;
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

	this->normalizeRatio = funMaximum(maxX.x, maxY.y, maxZ.z) / max_size;

	for (Point3D &p : _v) {
		p.x /= this->normalizeRatio;
		p.y /= this->normalizeRatio;
		p.z /= this->normalizeRatio;
	}
}

ShapeBuilder::ShapeBuilder()
{
}

Shape ShapeBuilder::getShape(bool _includes, bool doNormalize)
{
	if (doNormalize) {
		normalize(this->points);
	}
	for (Point3D &p : this->points) {
		// check ./shapeBuilderSheme.png for an explaination
		if (!p.B && !this->contains(base, p.x, p.z))
			this->base.push_back(Point2D(p.x, p.z));
		if (!p.F && !this->contains(side1, p.x, p.y))
			this->side1.push_back(Point2D(p.x, p.y));
		if (!p.S && !this->contains(side2, p.z, p.y))
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
			if (i < 3)
				throw std::runtime_error("Every point needs to be connected to at least 3 points!");
		}
	}
	return Shape(_includes, this->base, this->side1, this->side2, this->points);
}

void ShapeBuilder::add(double _x, double _y, double _z, bool B, bool F, bool S)
{
	this->points.push_back(Point3D(_x, _y, _z, B, F, S));
}

void ShapeBuilder::add(double _x, double _y, double _z)
{
	this->points.push_back(Point3D(_x, _y, _z, false, false, false));
}

bool ShapeBuilder::doesLineExist(Point3D p1, Point3D p2)
{
	for (int i = 0; i < this->lines.size(); i++) {
		Point3D l1 = this->lines[i][0];
		Point3D l2 = this->lines[i][1];
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

double rectangleMethodResults::getVolume()
{
	return this->volume;
}

rectangleMethodResults::rectangleMethodResults(double _volume, std::vector<Shape> _rectangles)
{
	this->volume = _volume;
	this->rectangles = _rectangles;
}

rectangleMethodResults::rectangleMethodResults(double _volume, std::vector<Shape> _rectangles, std::vector<Shape> _projections)
{
	this->volume = _volume;
	this->rectangles = _rectangles;
	this->projections = _projections;
}

std::vector<Shape> rectangleMethodResults::getRectangles()
{
	return this->rectangles;
}

std::vector<Shape> rectangleMethodResults::getProjectins()
{
	return this->projections;
}

double monteCarloMethodResults::getVolume()
{
	return this->volume;
}

bool monteCarloMethodResults::getInclude()
{
	return this->include;
}

std::vector<Point3D> monteCarloMethodResults::getMissedPoints()
{
	return this->pointsThatMissed;
}

std::vector<Point3D> monteCarloMethodResults::getHitPoints()
{
	return this->pointsThatHit;
}
