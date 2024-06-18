#pragma once
#include "MyString.h"

class Check {
public:
	Check(const MyString& code, unsigned money, const MyString& nameOfThirdParty);
	void setCode(const MyString& code);
private:
	MyString code;
	unsigned money;
	MyString nameOfThirdParty;
};