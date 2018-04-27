#pragma once
#include <string.h>
#include <vector>
#include "Shape.h"

class ParseMetaData{
public:
	char type;
	bool includes;
	std::string content;
};

class FileParser {
private:
	static Shape R(bool, std::ifstream&);
	static Shape N(bool, std::ifstream&);
	static double readNumber(std::ifstream&);
	static char readChar(std::ifstream&);
	static Shape readShape(std::ifstream&);
public:
	static std::vector<Shape> parse(std::string);
};