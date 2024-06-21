#pragma once
#include "MyString.h"

class Check {
public:
	Check() = default;
	Check(const MyString& code, unsigned money, const MyString& nameOfThirdParty);
	void setCode(const MyString& code);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
	const MyString& getCode() const;
	unsigned getMoney() const;
private:
	MyString code;
	unsigned money = 0;
	MyString nameOfThirdParty;
};