#include "FunctionContainer.h"

void FunctionContainer::add(PartialFunction* f) {
	functions.pushBack(PolymorphicPtr<PartialFunction>(f));
}

void FunctionContainer::add(const PartialFunction& f) {
	functions.pushBack(PolymorphicPtr<PartialFunction>(f.clone()));
}

void FunctionContainer::execute(size_t index, void (*f)(PartialFunction*)) {
	f(functions[index].get());
}

void FunctionContainer::execute(size_t index, void (*f)(const PartialFunction*)) const {
	f(functions[index].get());
}

size_t FunctionContainer::getSize() const {
	return functions.getSize();
}

PolymorphicPtr<PartialFunction>& FunctionContainer::operator[](size_t index) {
	return functions[index];
}

const PolymorphicPtr<PartialFunction>& FunctionContainer::operator[](size_t index) const {
	return functions[index];
}