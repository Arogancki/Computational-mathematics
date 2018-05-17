#pragma once
#include <vector>

class rectangleMethodResults;
class monteCarloMethodResults;
class IntersectionInfo;


class Point2D {
public:
	double x, y;
	Point2D();
	Point2D(double, double);
	double getX();
	double getY();
	static bool areEqual(Point2D, Point2D);
	bool operator==(const Point2D& lhs);
};

class Point3D : public Point2D {
public:
	bool B = false, F = false, S=false;
	double z;
	Point3D();
	Point3D(double, double, double);
	Point3D(double, double, double, bool, bool, bool);
	double getZ();
	static bool areEqual(Point3D, Point3D);
};

class CubeBorder {
public:
	Point3D minimumPoint;
	Point3D maximumPoint;
	CubeBorder(Point3D _minimum, Point3D _maximum) : minimumPoint(_minimum), maximumPoint(_maximum) {};
};

class IntersectionInfo{
public:
	bool intersects;
	Point2D intersection;
	IntersectionInfo(bool _intersects) : intersects(_intersects), intersection(Point2D(-1, -1)) { ; };
	IntersectionInfo(Point2D point) : intersects(true), intersection(Point2D(point.getX(), point.getY())) { ; };
};

class Line {
private:
	Point2D start;
	Point2D end;
public:
	Line(Point2D, Point2D);
	IntersectionInfo intersect(Line);
	Point2D getStart();
	Point2D getEnd();
};

class Shape {
private:
	std::vector<std::vector<Point2D>> rectangleMethod2d(std::vector<Point2D>&, int);
	bool includes;
	std::vector<Point3D> points;
	std::vector<Point2D> base;
	std::vector<Point2D> side1;
	std::vector<Point2D> side2;
	bool isInside(std::vector<Point2D>, Line);
	static Shape getCube(double, double, double, double, double, double);
public:
	rectangleMethodResults rectangleMethod2(int);
	rectangleMethodResults rectangleMethod(int);
	monteCarloMethodResults monteCarloMethod(int);
	Shape(bool, std::vector<Point2D>, std::vector<Point2D>, std::vector<Point2D>, std::vector<Point3D>);
	bool getIncludes();
	std::vector<Point2D> getBase();
	std::vector<Point2D> getSide1();
	std::vector<Point2D> getSide2();
	std::vector<Point3D> getPoints();
	Shape getCubeAround();
	CubeBorder getCubeAroundPointRange();
	double getFieldOfCube();
	bool isInside(Point3D);
	static double getMax_size();
};

class ShapeBuilder {
private:
	void normalize(std::vector<Point3D>&);
	std::vector<Point2D> base;
	std::vector<Point2D> side1;
	std::vector<Point2D> side2;
	std::vector<Point3D> points;
	std::vector<std::vector<Point3D>> lines;
	bool doesLineExist(Point3D, Point3D);
	void addTo(double, double, std::vector<Point2D>&);
	bool contains(std::vector<Point2D>&, double, double);
public:
	double normalizeRatio = 1.0;
	Point2D getMinXBase();
	Point2D getMinYBase();
	Point2D getMinXSide1();
	Point2D getMinYSide1();
	Point2D getMinXSide2();
	Point2D getMinYSide2();
	Point3D getMinX();
	Point3D getMinY();
	Point3D getMinZ();
	Point2D getMaxXBase();
	Point2D getMaxYBase();
	Point2D getMaxXSide1();
	Point2D getMaxYSide1();
	Point2D getMaxXSide2();
	Point2D getMaxYSide2();
	Point3D getMaxX();
	Point3D getMaxY();
	Point3D getMaxZ();
	ShapeBuilder();
	void add(double, double, double, bool, bool, bool);
	void add(double, double, double);
	void addToBase(double, double);
	void addToSide1(double, double);
	void addToSide2(double, double);
	Shape getShape(bool, bool);
};

class rectangleMethodResults {
private:
	double volume;
	bool includes;
	std::vector<Shape> rectangles;
	std::vector<Shape> projections;
public:
	double getVolume();
	bool getIncludes();
	rectangleMethodResults(bool, double, std::vector<Shape>, std::vector<Shape>);
	rectangleMethodResults(double, std::vector<Shape>);
	std::vector<Shape> getRectangles();
	std::vector<Shape> getProjectins();
}; 

class monteCarloMethodResults {
private:
	bool include;
	double volume;
	std::vector<Point3D> pointsThatMissed;
	std::vector<Point3D> pointsThatHit;
public:
	double getVolume();
	bool getInclude();
	monteCarloMethodResults(std::vector<Point3D> _hitPoints, std::vector<Point3D> _missPoints, float _volume, bool _include) 
		: pointsThatHit(_hitPoints), pointsThatMissed(_missPoints), volume(_volume), include(_include) { ; };
	std::vector<Point3D> getMissedPoints();
	std::vector<Point3D> getHitPoints();
};
