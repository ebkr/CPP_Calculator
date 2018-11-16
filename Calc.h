#pragma once
#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

class Calc {

public:
	Calc(std::string& eq);
	float getResult();

private:
	std::vector<std::string>* splitEquation(std::string& str);
	std::string equationString = "";

	/*
	* Used to generate numbers within brackets
	*/
	float resolveBrackets(int index);
	float resolveEquation(std::string& str);
};

#endif // !CALC_H