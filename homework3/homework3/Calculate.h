#pragma once
#include "PartialFunction.h"
#include "FunctionContainer.h"

class Calculate {
public:
	Calculate(const char* fileName);
	~Calculate();

	//delete copy constr(move constr) and copy op=(move op=) 
	Calculate(const Calculate& other) = delete;
	Calculate& operator=(const Calculate& other) = delete;

	void IntervalCalculation(int a, int b) const;
	void userCalculation() const;

private:
	PartialFunction* f;
};