#pragma once
#include <fstream>

class Account {
public:
	Account();
	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
	unsigned getAccountNumber() const;
	double getBalance() const;
	void addMoney(unsigned money);
private:
	unsigned accountNumber = 0;
	double balance = 0;
};