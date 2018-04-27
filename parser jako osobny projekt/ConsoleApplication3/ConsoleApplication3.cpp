#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include "FileParser.h"

using namespace std;

int main()
{
	try {
		FileParser::parse("./fileExample.txt");
	}
	catch (const std::exception exceptional_result) {
		std::cout << exceptional_result.what() << '\n';
	}
	return 0;
}

