#pragma once
#include "Content.h"
#include "Pair.hpp"

class ContentTypeZero : public Content {
private:
	int getNumberAtIdx(int32_t x) const override;
	int32_t resultsArr[MAX_OF_N];
public:
	ContentTypeZero(int32_t* args, int32_t* results, int16_t N);
	Pair<bool, int32_t> getResult(int32_t x) const override;
};