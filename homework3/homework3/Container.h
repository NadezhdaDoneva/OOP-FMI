#pragma once
#include "PartialFunction.h"
#include "FunctionContainer.h"

class Container : public PartialFunction {
private:
	FunctionContainer container;

public:
	Container(const FunctionContainer& container) : container(container){ }
};