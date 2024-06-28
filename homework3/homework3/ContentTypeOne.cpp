#include "ContentTypeOne.h"

int ContentTypeOne::getNumberAtIdx(int32_t x) const {
	for (size_t i = 0; i < N; i++) {
		if (x == arguments[i])
			return i;
	}
	return -1;
}

ContentTypeOne::ContentTypeOne(int32_t* args, int16_t N) : Content(args, N){ }

Pair<bool, int32_t> ContentTypeOne::getResult(int32_t x) const {
	Pair<bool, int32_t> pair;
	int idx = getNumberAtIdx(x);

	if (idx != -1) {
		pair.setLhs(false);
	}
	else {
		pair.setLhs(true);
		pair.setRhs(x);
	}

	return pair;
}

