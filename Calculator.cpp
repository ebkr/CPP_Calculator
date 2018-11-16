#include "pch.h"
#include "Calc.h"

std::vector<std::string>* splitEquation(std::string & str) {
	std::vector<std::string> * split = new std::vector<std::string>();
	std::string numericalAdder = "";
	int count = 0;
	for (int i = 0; i < str.size(); i++) {
		try {
			std::stoi(str.substr(i, 1));
			numericalAdder += str.substr(i, 1);
		}
		catch(std::exception e) {
			if (str.substr(i, 1) != ".") {
				split->push_back(numericalAdder);
				split->push_back(str.substr(i, 1));
				numericalAdder = "";
			}
			else {
				numericalAdder += ".";
			}
		}
	}
	split->push_back(numericalAdder);
	return split;
}

int breakApartScope(std::vector<std::string>* scope, int& index) {
	int start = index;
	int end = scope->size();
	int i = 0;
	while (i < scope->size() && (i++)) {
		
	}
	return 0;
}

float calculateFromVector(std::vector<std::string>* vec) {
	float total = 0;
	char expression = '+';
	for (int i = 0; i < vec->size(); i++) {
		try {
			float num = std::stof(vec->at(i));
			switch (expression) {
			case '+':
				total += num;
				break;
			case '-':
				total -= num;
				break;
			case '/':
				total /= num;
				break;
			case '*':
				total *= num;
				break;
			}
		}
		catch (std::exception e) {
			expression = *(vec->at(i).c_str());
		}
	}
	return total;
}

int main()
{
	/*
	std::string str;
	std::cout << "Enter an equation" << std::endl;
	std::getline(std::cin, str);
	std::vector<std::string>* vec = splitEquation(str);
	std::cout << "Answer: " << calculateFromVector(vec) << std::endl;
	*/

	
	std::string str;
	std::cout << "Enter an equation" << std::endl;
	std::getline(std::cin, str);

	Calc * calculator = new Calc(str);
	calculator->getResult();
	
	return 0;
}