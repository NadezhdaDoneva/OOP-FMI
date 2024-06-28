#pragma once
#include <iostream>

class PartialFunction {
public:
	virtual bool isDefined(int32_t x) const = 0;
	virtual int32_t getResult(int32_t x) const = 0;
	virtual PartialFunction* clone() const = 0;
	virtual ~PartialFunction() = default;
};