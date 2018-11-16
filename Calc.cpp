#include "pch.h"
#include "Calc.h"

Calc::Calc(std::string& eq) {
	equationString = eq;
};

float Calc::resolveBrackets(int index) {
	int startIndex = index;
	while (index < equationString.length()) {
		if (equationString.substr(index, 1) == "(") {
			if (index > 0) {
				try {
					std::stoi(equationString.substr(index - 1, 1));
					std::string start = equationString.substr(0, index);
					std::string finish = equationString.substr(index + 1);

					equationString = start + "*" + finish;

					std::cout << "Str: " << equationString << std::endl;
				}
				catch (std::exception) {
					// Nothing to do
				}
			}
			index += 1;
			resolveBrackets(index);
		}
		else if (equationString.substr(index, 1) == ")") {
			std::string start = equationString.substr(0, startIndex);
			std::cout << "Start: " << start << std::endl;
			std::string finish = "";
			try {
				finish = equationString.substr(index + 1);
			}
			catch (std::exception e) {
				// also does nothing
			}
			std::string mid = equationString.substr(startIndex, (index - startIndex));
			std::cout << "Mid: " << mid << std::endl;
			int follow = index + 1;
			equationString = start + (std::to_string(resolveEquation(mid))) + finish;
		}
		index++;
	}
	std::cout << "Result: " << equationString << std::endl;
	std::string eq = equationString.substr(startIndex, (index - startIndex));
	return resolveEquation(eq);
}


float Calc::getResult() {
	int index = 0;

	resolveBrackets(index);
	std::cout << ">> " << equationString << std::endl;
	return 0;
};

float Calc::resolveEquation(std::string& str) {
	std::cout << "Eq: " << str << std::endl;
	std::vector<std::string>* vec = splitEquation(str);
	return std::stof(str);
}

std::vector<std::string>* Calc::splitEquation(std::string& str) {
	return NULL;
}