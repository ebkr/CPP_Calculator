#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

class Calc {

public:
	Calc(std::string& eq);
	float getResult();

private:
	std::string equationString;
	// Scan equationString to generate parse-able structure.
	std::vector<std::string> separateElements(std::string scan);
	// Scan "scope" to generate answer.
	std::vector<std::string> unpackScope(std::string scope);

	// Vector containing {left, expression, right}
	float parseEquation(std::string calc);
	std::vector<std::string> findExpression(std::vector<std::string> str, std::string exp);

	
};