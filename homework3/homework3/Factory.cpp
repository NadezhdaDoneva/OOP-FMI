#include "Factory.h"
#include "ContentTypeZero.h"
#include "ContentTypeOne.h"
#include "ContentTypeTwo.h"
#include "FunctionContainer.h"
#include "CriteriaFunction.hpp"
#include "MinimumFunc.hpp"
#include "MaximumFunc.hpp"

PartialFunction* Factory::createFromFile(const MyString& fileName) {
    std::ifstream ifs(fileName.c_str(), std::ios::binary);
	if (!ifs.is_open()) {
		throw std::runtime_error("the file could not be opened");
	}
	int16_t N, T;
	ifs.read((char*)&N, sizeof(N));
	ifs.read((char*)&T, sizeof(T));
	
	if (N < 0 || N > MAX_OF_N) {
		throw std::invalid_argument("N should be between 0 and 32");
	}

	switch (T)
	{
	case 0:
		return handleContentTypeZero(ifs, N);
		break;
	case 1:
		return handleContentTypeOne(ifs, N);
		break;
	case 2:
		return handleContentTypeTwo(ifs, N);
		break;
	case 3:
		return handleContentTypeThree(ifs, N);
		break;
	case 4:
		return handleContentTypeFour(ifs, N);
		break;
	default:
		throw std::invalid_argument("T should be between 0 and 4");
		break;
	}
}

PartialFunction* Factory::handleContentTypeZero(std::ifstream& ifs, int16_t N) {
	int32_t arguments[MAX_OF_N];
	int32_t results[MAX_OF_N];

	ifs.read((char*)arguments, sizeof(int32_t) * N);
	ifs.read((char*)results, sizeof(int32_t) * N);

	ContentTypeZero f(arguments, results, N);
	return new CriteriaFunction<ContentTypeZero>(f);
}

PartialFunction* Factory::handleContentTypeOne(std::ifstream& ifs, int16_t N) {
	int32_t arguments[MAX_OF_N];
	ifs.read((char*)arguments, sizeof(int32_t) * N);
	ContentTypeOne f(arguments, N);
	return new CriteriaFunction<ContentTypeOne>(f);
}

PartialFunction* Factory::handleContentTypeTwo(std::ifstream& ifs, int16_t N) {
	int32_t arguments[MAX_OF_N];
	ifs.read((char*)arguments, sizeof(int32_t) * N);
	ContentTypeTwo f(arguments, N);
	return new CriteriaFunction<ContentTypeTwo>(f);
}

PartialFunction* Factory::handleContentTypeThree(std::ifstream& ifs, int16_t N) {
	MyString fileNames[MAX_OF_N];
	FunctionContainer container;
	for (size_t i = 0; i < N; i++) {
		char ch = ' ';
		while (ch != '\0') {
			ifs.read((char*)&ch, sizeof(ch));
			fileNames[i] += MyString(&ch);
		}
		container.add(createFromFile(fileNames[i].c_str()));
	}

	return new MaximumFunc(container);
}

PartialFunction* Factory::handleContentTypeFour(std::ifstream& ifs, int16_t N) {
	MyString fileNames[MAX_OF_N];
	FunctionContainer container;
	for (size_t i = 0; i < N; i++) {
		char ch = ' ';
		while (ch != '\0') {
			ifs.read((char*)&ch, sizeof(ch));
			fileNames[i] += MyString(&ch);
		}
		container.add(createFromFile(fileNames[i].c_str()));
	}

	return new MinimumFunc(container);
}