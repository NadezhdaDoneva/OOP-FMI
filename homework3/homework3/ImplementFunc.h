#pragma once
#include "FunctionBase.h"
#include "Pair.hpp"

template <class T>
class ImplementFunc : public FunctionBase {
public:
	ImplementFunc(const T& t);
	Pair<bool, int32_t> result(int32_t x) const override;
	FunctionBase* clone() const override;
private:
	T t;
};

template <class T>
ImplementFunc<T>::ImplementFunc(const T& t) : t(t) { }

template<class T>
Pair<bool, int32_t> ImplementFunc<T>::result(int32_t x) const
{
	try {
		return Pair(true, t(x));
	}
	catch (...) {
		return Pair(false, 0);
	}
}

template<class T>
FunctionBase* ImplementFunc<T>::clone() const
{
	return new ImplementFunc(*this);
}

