#include "Account.h"
#include <cstdlib> 
#include <time.h>
#include <fstream>

Account::Account() {
	srand(time(NULL));
	accountNumber = rand();
}

void Account::saveToFile(std::ofstream& ofs) const {
	ofs.write((const char*)&accountNumber, sizeof accountNumber);
	ofs.write((const char*)&balance, sizeof balance);
}

void Account::readFromFile(std::ifstream& ifs) {
	ifs.read((char*)&accountNumber, sizeof accountNumber);
	ifs.read((char*)&balance, sizeof balance);
}

unsigned Account::getAccountNumber() const {
	return accountNumber;
}

double Account::getBalance() const {
	return balance;
}

void Account::addMoney(unsigned money) {
	balance += money;
}
