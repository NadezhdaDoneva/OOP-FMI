#pragma once
#include "Pair.hpp"
constexpr unsigned MAX_OF_N = 32;

class Content {
public:
	Content(int32_t* arguments, int16_t N);
	virtual Pair<bool, int32_t> getResult(int32_t x) const = 0;
	virtual ~Content() = default;
protected:
	int16_t N;
	int32_t arguments[MAX_OF_N];
	virtual int getNumberAtIdx(int32_t x) const = 0;
};
