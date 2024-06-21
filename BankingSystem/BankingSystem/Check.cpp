#include "Check.h"
#include <exception> 
#include <fstream>
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

void Check::saveToFile(std::ofstream& ofs) const {
	code.saveToFile(ofs);
	ofs.write((const char*)&money, sizeof money);
	nameOfThirdParty.saveToFile(ofs);
}

void Check::readFromFile(std::ifstream& ifs) {
	code.readFromFile(ifs);
	ifs.read((char*)&money, sizeof money);
	nameOfThirdParty.readFromFile(ifs);
}

const MyString& Check::getCode() const {
	return code;
}

unsigned Check::getMoney() const {
	return money;
}
