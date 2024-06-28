#pragma once
#include "PartialFunction.h"
#include "Container.h"
#include "FunctionContainer.h"

class MaximumFunc : public Container {
public:
	MaximumFunc(const FunctionContainer& functions);
	PartialFunction* clone() const override;
	bool isDefined(int32_t x) const override;
	int32_t getResult(int32_t x) const override;

private:
	FunctionContainer container;
	size_t size;
};

MaximumFunc::MaximumFunc(const FunctionContainer& functions) : Container(container) {
	size = container.getSize();
}

PartialFunction* MaximumFunc::clone() const {
	return new MaximumFunc(*this);
}

bool MaximumFunc::isDefined(int32_t x) const {
	for (size_t i = 0; i < size; i++) {
		if (!(container[i]->isDefined(x))) {
			return false;
		}
	}
	return true;
}

int32_t MaximumFunc::getResult(int32_t x) const
{
	if (!isDefined(x)) {
		throw std::invalid_argument("The function is not defined in that point");
	}

	int32_t max = container[0]->getResult(x);
	for (size_t i = 0; i < size; i++) {
		int32_t temp = container[i]->getResult(x);
		if (temp > max) {
			max = temp;
		}
	}
	return max;
}


