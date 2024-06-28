#pragma once
#include "Pair.hpp"
#include "PartialFunction.h"

template <class T>
class CriteriaFunction : public PartialFunction {
public:
	CriteriaFunction(const T& t);
	const Pair<bool, int32_t>& pair(int32_t x) const;

	bool isDefined(int32_t x) const override;
	int32_t getResult(int32_t x) const override;
	PartialFunction* clone() const override;

private:
	T function;
};


template<class T>
CriteriaFunction<T>::CriteriaFunction(const T& t) : function(t) {}

template<class T>
const Pair<bool, int32_t>& CriteriaFunction<T>::pair(int32_t x) const {
	Pair<bool, int> pair = function.getResult(x);
	return pair;
}

template<class T>
bool CriteriaFunction<T>::isDefined(int32_t x) const {
	Pair<bool, int> pair = function.getResult(x);
	return pair.getLhs();
}

template<class T>
int32_t CriteriaFunction<T>::getResult(int32_t x) const {
	Pair<bool, int> pair = function.getResult(x);

	if (!isDefined(x)) {
		throw std::invalid_argument("The function is not defined in that point");
	}

	return pair.getRhs();
}

template<class T>
PartialFunction* CriteriaFunction<T>::clone() const {
	return new CriteriaFunction<T>(*this);
}



