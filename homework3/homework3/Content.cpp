#include "Content.h"

Content::Content(int32_t* arguments, int16_t N) {
	this->N = N;
	for (size_t i = 0; i < N; i++) {
		this->arguments[i] = arguments[i];
	}
}
