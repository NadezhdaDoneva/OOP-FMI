#pragma once
#include <fstream>
#include "MyString.h"

class Account {
public:
	Account();
	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
	unsigned getAccountNumber() const;
	double getBalance() const;
	const MyString& getAccountNumAsStr() const;
	void addMoney(unsigned money);
private:
	unsigned accountNumber = 0;
	double balance = 0;
};