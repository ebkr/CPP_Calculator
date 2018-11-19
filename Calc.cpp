#include "pch.h"
#include "Calc.h"

Calc::Calc(std::string& eq) {
	equationString = eq;
}

float Calc::getResult() {
	std::vector<std::string> packaged = unpackScope(equationString);
	equationString = packaged.at(1);
	return std::stof(equationString);
}

std::vector<std::string> Calc::unpackScope(std::string scan) {
	std::vector<std::string> vec = std::vector<std::string>();
	std::string builder = "";
	int i = 0;
	// Loop until finished
	while (i < scan.length()) {
		// If scope
		if (scan.substr(i, 1) == "(") {
			// Attempt to multiply by outer
			if (i > 0) {
				try {
					std::stoi(scan.substr(i - 1, 1));
					builder += "*";
				}
				catch (std::exception e) {
					// Do nothing
					// Scope is not multiplied
				}
			}
			// Recursive call to work inside loop
			std::vector<std::string> scope = unpackScope(scan.substr(i+1));
			// Perform arithmetic on scope
			// {IMPLEMENT}
			// Append scope to builder
			builder += scope.at(1);
			// Increment position by size of (initial scan size - scanned amount)
			i += scope.at(0).size()+1;
		}
		else if (scan.substr(i, 1) == ")") {
			return std::vector<std::string>{scan.substr(0, i), std::to_string(parseEquation(builder))};
		}
		else {
			builder += scan.substr(i, 1);
		}
		i++;
	}
	return std::vector<std::string>{scan.substr(0, i), std::to_string(parseEquation(builder))};
}

std::vector<std::string> Calc::separateElements(std::string str) {
	// Record built numbers and expressions
	std::vector<std::string> split = std::vector<std::string>();
	// Used to build numbers
	std::string append = "";
	for (int i = 0; i < str.length(); i++) {
		// Detect if number
		try {
			std::stoi(str.substr(i, 1));
			if (isalpha(*append.c_str())) {
				split.push_back(append);
				append = "";
			}
			append += str.substr(i, 1);
		}
		// If not a number
		catch (std::exception e) {
			if (str.substr(i, 1) == ".") {
				// Decimal
				if (isalpha(*append.c_str())) {
					split.push_back(append);
					append = "";
				}
				append += ".";
			}
			else if (str.substr(i, 1) == "-") {
				if (append.length() == 0) {
					// Start of a negative
					append = "-";
				}
				else {
					if (append == "-") {
						append = "";
					}
					else {
						split.push_back(append);
						append = "-";
					}
				}
			}
			else if (str.substr(i, 1) == "+") {
				// Do nothing unless requesting number addition
				if (append.length() > 0 && append != "-") {
					split.push_back(append);
					append = "";
				}
			}
			else if (str.substr(i, 1) == " ") {
				// Do nothing
			}
			else {
				if (isalpha(*str.substr(i, 1).c_str())) {
					if (isalpha(*(append + str.substr(i, 1)).c_str())) {
						append += str.substr(i, 1);
					}
					else {
						split.push_back(append);
						append = str.substr(i, 1);
					}
				}
				else {
					// Push valid number.
					split.push_back(append);
					// Push 
					split.push_back(str.substr(i, 1));
					append = "";
				}
			}
		}
	}
	if (append.length() > 0) {
		split.push_back(append);
	}
	return split;
}

float Calc::parseEquation(std::string calc) {
	std::vector<std::string> separated = separateElements(calc);
	// Perform BIDMAS/BODMAS operations (Power, Division, Multiplication):
		// Brackets are handled in scopes.
		// Addition/Subtraction are on the same level. All elements are added.
		// Subtractions work via negations.
	std::vector<std::string> stored = std::vector<std::string>();
	do {
		stored = separated;
		separated = findExpression(separated, "sqrt");
		separated = findExpression(separated, "^");
		separated = findExpression(separated, "/");
		separated = findExpression(separated, "*");
	} while (separated != stored);

	// Calculate total by adding final scope's values
	float total = 0;
	for (std::string str : separated) {
		std::cout << str << std::endl;
		total += std::stof(str);
	}
	return total;
}

std::vector<std::string> Calc::findExpression(std::vector<std::string> str, std::string exp) {
	float value = 0;
	// Find expressions
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == exp) {
			// Initialise values
			std::string left = std::string();
			bool leftIsEmpty = true;
			std::string right = str.at(i + 1);

			// Left hand value may be null. EG: (2)
			try {
				left = str.at(i - 1);
				if (!isdigit(*left.c_str())) {
					throw(std::exception("Does not support operator"));
				}
				leftIsEmpty = false;
			}
			catch (std::exception e) {
				if (exp == "*" || exp == "sqrt") {
					left = "1";
				}
				else {
					left = "0";
				}
			}
			// Perform expression matching call
			if (exp == "^") {
				value = pow(std::stof(left), std::stof(right));
			}
			else if (exp == "/") {
				value = std::stof(left) / std::stof(right);
			}
			else if (exp == "*") {
				value = std::stof(left) * std::stof(right);
			}
			else if (exp == "sqrt") {
				std::cout << left << ":" << right << std::endl;
				value = std::stof(left) * sqrt(std::stof(right));
			}
			else {
				value = std::stof(left) + std::stof(right);
			}
			// Replace values in array
			str.erase(str.begin() + i);
			str.erase(str.begin() + i);
			str.insert(str.begin() + i, std::to_string(value));
			if (!leftIsEmpty) {
				str.erase(str.begin() + i - 1);
			}
		}
	}
	return str;
}