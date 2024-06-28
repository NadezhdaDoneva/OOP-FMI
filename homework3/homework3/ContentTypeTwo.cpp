#include "ContentTypeTwo.h"

int ContentTypeTwo::getNumberAtIdx(int32_t x) const {
	for (size_t i = 0; i < N; i++) {
		if (x == arguments[i])
			return i;
	}
	return -1;
}

ContentTypeTwo::ContentTypeTwo(int32_t* args, int16_t N) : Content(args, N){ }

Pair<bool, int32_t> ContentTypeTwo::getResult(int32_t x) const {
	Pair<bool, int> pair;
	pair.setLhs(true);
	if (getNumberAtIdx(x) != -1) {
		pair.setRhs(1);
	}
	else {
		pair.setRhs(0);
	}
	return pair;
}


