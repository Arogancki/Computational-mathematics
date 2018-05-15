#pragma once
#include <string.h>
#include <vector>
#include "Shape.h"

class ParsedData {
public:
	char type;
	int value;
	std::vector<Shape> shapes;
	ParsedData(char, int, std::vector<Shape>);
};

class FileParser {
private:
	static Shape R(bool, std::ifstream&);
	static Shape N(bool, std::ifstream&);
	static double readNumber(std::ifstream&);
	static char readChar(std::ifstream&);
	static Shape readShape(std::ifstream&);
public:
	static ParsedData parse(std::string);
	static double getMax_size();
};