#pragma once
#include "PartialFunction.h"
#include "MyString.h"
#include <fstream>

class Factory {
public:
	static PartialFunction* createFromFile(const MyString& fileName);
private:
	static PartialFunction* handleContentTypeZero(std::ifstream& ifs, int16_t N);
	static PartialFunction* handleContentTypeOne(std::ifstream& ifs, int16_t N);
	static PartialFunction* handleContentTypeTwo(std::ifstream& ifs, int16_t N);
	static PartialFunction* handleContentTypeThree(std::ifstream& ifs, int16_t N);
	static PartialFunction* handleContentTypeFour(std::ifstream& ifs, int16_t N);
	/*static int16_t N;
	static int16_t T;*/
};
