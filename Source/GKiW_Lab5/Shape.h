#pragma once
#include <vector>

class Point2D {
private:
	double x, y;
public:
	Point2D(double, double);
	double getX();
	double getY();
};

class Point3D : public Point2D{
private:
	double z;
public:
	Point3D(double, double, double);
	double getZ();
};

class Shape{
private:
	bool includes;
	std::vector<Point3D> points;
	std::vector<Point2D> base;
	std::vector<Point2D> side1;
	std::vector<Point2D> side2;
public:
	Shape(bool, std::vector<Point2D>, std::vector<Point2D>, std::vector<Point2D>, std::vector<Point3D>);
	bool getIncludes();
	std::vector<Point2D> getBase();
	std::vector<Point2D> getSide1();
	std::vector<Point2D> getSide2();
	std::vector<Point3D> getPoints();
};

class ShapeBuilder{
private:
	std::vector<Point2D> base;
	std::vector<Point2D> side1;
	std::vector<Point2D> side2;
	std::vector<Point3D> points;
	void addTo(double, double, std::vector<Point2D>&);
	bool areEqual(double, double);
	bool contains(std::vector<Point2D>&, double, double);
public:
	ShapeBuilder();
	void add(double, double, double);
	void addToBase(double, double);
	void addToSide1(double, double);
	void addToSide2(double, double);
	Shape getShape(bool);
};