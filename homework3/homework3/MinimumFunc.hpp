#pragma once
#include "PartialFunction.h"
#include "Container.h"
#include "FunctionContainer.h"

class MinimumFunc : public Container {
public:
	MinimumFunc(const FunctionContainer& functions);
	PartialFunction* clone() const override;
	bool isDefined(int32_t x) const override;
	int32_t getResult(int32_t x) const override;

private:
	FunctionContainer container;
	size_t size = 0;
};


MinimumFunc::MinimumFunc(const FunctionContainer& functions) : Container(container) {
	size = container.getSize();
}


PartialFunction* MinimumFunc::clone() const {
	return new MinimumFunc(*this);
}

bool MinimumFunc::isDefined(int32_t x) const {
	for (size_t i = 0; i < size; i++) {
		if (!(container[i]->isDefined(x))) {
			return false;
		}
	}
	return true;
}

int32_t MinimumFunc::getResult(int32_t x) const
{
	if (!isDefined(x)) {
		throw std::invalid_argument("The function is not defined in that point");
	}

	int32_t min = container[0]->getResult(x);
	for (size_t i = 0; i < size; i++) {
		int32_t temp = container[i]->getResult(x);
		if (temp < min) {
			min = temp;
		}
	}
	return min;
}


