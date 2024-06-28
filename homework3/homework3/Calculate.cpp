#include "Calculate.h"
#include "Factory.h"

Calculate::Calculate(const char* fileName) {
	try {
		f = Factory::createFromFile(fileName);
	} 
	catch(const std::exception& e){
		std::cout << e.what();
		f = nullptr;
	}
}

Calculate::~Calculate() {
	delete f;
}

void Calculate::IntervalCalculation(int a, int b) const {
	for (size_t x = a; x <= b; x++) {
		if (f->isDefined(x)) {
			std::cout << "f(" << x << ") = " << f->getResult(x) << "\n";
		}
		else {
			std::cout << "f(" << x << ") is not defined \n";
		}
	}
}

void Calculate::userCalculation() const {
	int32_t curX = 0;
	while (true) {
		if (f->isDefined(curX)) {
			std::cout << "Should we generate the next defined value of the function? \n";
			MyString userResponse;
			std::cin >> userResponse;

			static const MyString yes = "yes";
			if (userResponse == yes) {
				std::cout << "f(" << curX << ") = " << f->getResult(curX) << "\n";
			}
			else {
				break;
			}
		}
		curX++;
	}
}




