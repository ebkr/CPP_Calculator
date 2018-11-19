#include "pch.h"
#include "Calc.h"

int main()
{

	std::string str;
	std::cout << "Enter an equation" << std::endl;
	std::getline(std::cin, str);

	Calc calculator = Calc(str);
	float result = calculator.getResult();
	std::cout << std::endl;
	std::cout << "Ans: " << result << std::endl;
	return 0;
}