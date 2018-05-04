#include "stdafx.h"
#include "FileParser.h"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <stdlib.h>

char FileParser::readChar(std::ifstream& _file)
{
	char singleCharacter = EOF;
	do {
		_file.get(singleCharacter);
	}while (singleCharacter == '\n' 
		|| singleCharacter == ' '
		|| singleCharacter == '\r' 
		|| singleCharacter == '\r\n' 
		|| singleCharacter == '\n\r'
	);
	return singleCharacter;
}

double FileParser::readNumber(std::ifstream& _file)
{
	char singleCharacter = EOF;
	std::stringstream number;
	do {
		singleCharacter = readChar(_file);
		// has to be /d or . or -
		if (singleCharacter == EOF)
			throw std::runtime_error("Unexpected end of the file!");
		if (singleCharacter == ';' || singleCharacter == ',') {
			break;
		}
		if (!isdigit(singleCharacter) && singleCharacter != '.' && singleCharacter != '-') {
			throw std::runtime_error("Unexpected token: " + singleCharacter + '!');
		}
		number << singleCharacter;
	} while (true);
	return atof(number.str().c_str());
}

Shape FileParser::R(bool _includes, std::ifstream& _file)
{
	char singleCharacter;
	ShapeBuilder shapeBuilder = ShapeBuilder();
	double number1;
	double number2;

	// build base
	do {
		number1 = readNumber(_file);
		number2 = readNumber(_file);
		shapeBuilder.addToBase(number1, number2);
		singleCharacter = readChar(_file);
		if (singleCharacter == EOF) {
			throw std::runtime_error("Unexpected end of a file!");
		}
		_file.seekg(-1L, std::ifstream::cur);
	} while (singleCharacter != '&');

	singleCharacter = readChar(_file); // shift
	// build side1
	do {
		number1 = readNumber(_file);
		number2 = readNumber(_file);
		shapeBuilder.addToSide1(number1, number2);
		singleCharacter = readChar(_file);
		if (singleCharacter == EOF) {
			throw std::runtime_error("Unexpected end of a file!");
		}
		_file.seekg(-1L, std::ifstream::cur);
	} while (singleCharacter != '&');

	singleCharacter = readChar(_file); // shift
	// build side2
	do {
		number1 = readNumber(_file);
		number2 = readNumber(_file);
		shapeBuilder.addToSide2(number1, number2);
		singleCharacter = readChar(_file);
		if (singleCharacter == EOF) {
			throw std::runtime_error("Unexpected end of a file!");
		}
		_file.seekg(-1L, std::ifstream::cur);
	} while (singleCharacter != '#');

	singleCharacter = readChar(_file); // shift
	return shapeBuilder.getShape(_includes, true);
}

Shape FileParser::N(bool _includes, std::ifstream& _file)
{
	char singleCharacter;
	ShapeBuilder shapeBuilder = ShapeBuilder();
	double number1;
	double number2;
	double number3;

	// build base
	do {
		number1 = readNumber(_file);
		number2 = readNumber(_file);
		number3 = readNumber(_file);
		shapeBuilder.add(number1, number2, number3);
		singleCharacter = readChar(_file);
		if (singleCharacter == EOF) {
			throw std::runtime_error("Unexpected end of a file!");
		}
		_file.seekg(-1L, std::ifstream::cur);
	} while (singleCharacter != '#');

	singleCharacter = readChar(_file); // shift
	return shapeBuilder.getShape(_includes, true);
}

Shape FileParser::readShape(std::ifstream& _file)
{
	char singleCharacter;
	singleCharacter = readChar(_file);
	// the first has to be the R or N
	if (singleCharacter != 'R' && singleCharacter != 'N') {
		throw std::runtime_error("A shape must starts with R or N!");
	}
	bool isR = singleCharacter == 'R';

	singleCharacter = readChar(_file);
	// the second has to be the 1 or 0
	if (singleCharacter != '1' && singleCharacter != '0') {
		throw std::runtime_error("A shape must have exclusion (0) or concluding (1) defined after R or N!");
	}
	bool includes = singleCharacter == '1';

	if (isR) {
		return R(includes, _file);
	}
	else {
		return N(includes, _file);
	}
}

ParsedData FileParser::parse(std::string filePath)
{
	char singleCharacter;
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Nie mozna otworzyc pliku!");
	}
	std::vector<Shape> shapes = std::vector<Shape>();

	singleCharacter = readChar(file);
	// the first has to be the R or M
	if (singleCharacter != 'R' && singleCharacter != 'M') {
		throw std::runtime_error("File must starts with R (rectangles) or M (monte carlo)!");
	}
	char type = singleCharacter;

	int value = (int)readNumber(file);
	do {
		shapes.push_back(readShape(file));
		singleCharacter = readChar(file);
		file.seekg(-1L, std::ifstream::cur);
	} while (singleCharacter != EOF);
	file.close();
	return ParsedData(type, value, shapes);
}

ParsedData::ParsedData(char _type, int _value, std::vector<Shape> _shapes)
{
	type = _type;
	value = _value;
	shapes = _shapes;
}