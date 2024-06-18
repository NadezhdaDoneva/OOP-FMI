#include "Check.h"
#include <exception> 
static const int CODE_SIZE = 3;

Check::Check(const MyString& code, unsigned money, const MyString& nameOfThirdParty) : money(money), nameOfThirdParty(nameOfThirdParty) {
	setCode(code);
}

void Check::setCode(const MyString& newCode) {
	if (newCode.getSize() == CODE_SIZE) {
		code = newCode;
	}
	throw std::length_error("The code should have length = 3");
}
