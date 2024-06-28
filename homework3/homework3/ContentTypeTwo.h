#pragma once
#include "Content.h"
#include "Pair.hpp"

class ContentTypeTwo : public Content {
private:
	int getNumberAtIdx(int32_t x) const override;
public:
	ContentTypeTwo(int32_t* args, int16_t N);
	Pair<bool, int32_t> getResult(int32_t x) const override;
};