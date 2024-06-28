#include "ContentTypeZero.h"

int ContentTypeZero::getNumberAtIdx(int32_t x) const {
	for (size_t i = 0; i < N; i++) {
		if (x == arguments[i])
			return i;
	}
	throw std::invalid_argument("there is no such point in this function");
}

ContentTypeZero::ContentTypeZero(int32_t* args, int32_t* results, int16_t N) : Content(args, N){
	for (size_t i = 0; i < N; i++) {
		resultsArr[i] = results[i];
	}
}

Pair<bool, int32_t> ContentTypeZero::getResult(int32_t x) const {
	Pair<bool, int32_t> pair;
	pair.setLhs(true);
	pair.setRhs(resultsArr[getNumberAtIdx(x)]);
	return pair;
}

