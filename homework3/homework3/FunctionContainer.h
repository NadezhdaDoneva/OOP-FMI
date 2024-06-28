#pragma once
#include "PolymorphicPtr.hpp"
#include "MyVector.hpp"
#include "PartialFunction.h"

class FunctionContainer {
public:
	void add(PartialFunction* f);
	void add(const PartialFunction& f);
	void execute(size_t index, void (*func)(PartialFunction*));
	void execute(size_t index, void (*func)(const PartialFunction*)) const;
	PolymorphicPtr<PartialFunction>& operator[] (size_t index);
	const PolymorphicPtr<PartialFunction>& operator[] (size_t index) const;
	size_t getSize() const;
private:
	MyVector<PolymorphicPtr<PartialFunction>> functions;
};

