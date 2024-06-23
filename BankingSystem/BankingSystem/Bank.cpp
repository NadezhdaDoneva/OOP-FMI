#include "Bank.h"
#include <fstream>
#include "UtilFuncs.h"

Bank::Bank(const MyString& name) : bankName(name){}

//const DynamicArray<Client>& Bank::getClients() const {
//    return this->clients;
//}

const DynamicArray<Employee>& Bank::getEmployees() const {
    return this->employees;
}

//void Bank::addClient(const Client& client) {
//    clients.pushBack(client);
//}
//
//void Bank::addClient(Client&& client){
//    clients.pushBack(std::move(client));
//}

void Bank::addEmployee(const Employee& employee) {
    employees.pushBack(employee);
}

void Bank::addEmployee(Employee&& employee) {
    employees.pushBack(std::move(employee));
}

void Bank::saveToFile(std::ofstream& ofs) const {
    bankName.saveToFile(ofs);
    int employeesInCurBankCount = employees.getSize();
    ofs.write((const char*)&employeesInCurBankCount, sizeof employeesInCurBankCount);
    for (int i = 0; i < employeesInCurBankCount; i++)
        employees[i].saveToFile(ofs);
    int bankAccountsCount = bankAccounts.getSize();
    ofs.write((const char*)&bankAccountsCount, sizeof bankAccountsCount);
    for (int i = 0; i < bankAccountsCount; i++) {
        bankAccounts[i].getLhs().saveToFile(ofs);
        bankAccounts[i].getRhs().saveToFile(ofs);
    }
    ofs.close();
}

void Bank::readFromFile(std::ifstream& ifs) {
    bankName.readFromFile(ifs);
    int employeesInCurBankCount = 0;
    ifs.read((char*)&employeesInCurBankCount, sizeof employeesInCurBankCount);
    for (size_t i = 0; i < employeesInCurBankCount; i++) {
        employees[i].readFromFile(ifs);
    }
    int bankAccountsCount = 0;
    ifs.read((char*)&bankAccountsCount, sizeof bankAccountsCount);
    for (int i = 0; i < bankAccountsCount; i++) {
        ifs.read((char*)&bankAccounts[i].getLhs(), sizeof bankAccounts[i].getLhs());
        bankAccounts[i].getRhs().readFromFile(ifs);
    }
    ifs.close();
}

void Bank::assignTask(const Task& task) {
    Employee* leastBusiest = getLeastBusiestEmployee();
    leastBusiest->addTask(task);
}

double Bank::getBalanceByAccountNumber(unsigned accNum) const{
    int idx = getIdxOfAccountByAccNum(accNum);
    double balance = bankAccounts[idx].getRhs().getBalance();
    return balance;
}

MyString Bank::openAccount(const MyString& username) {
    Account newAcc;
	Pair<MyString, Account> newBankAcc(username, newAcc);
	bankAccounts.pushBack(newBankAcc);
    MyString newMess = "You opened an account in " + bankName + " ! Your account id is " + toString(newAcc.getAccountNumber()) + "\n";
    return newMess;
}

MyString Bank::closeAccount(const MyString& username, unsigned accNum) {
    int idx = getIdxOfAccountByAccNum(accNum);
    bankAccounts.removeAt(idx);
    MyString newMess = "You closed an account in " + bankName + " with " + toString(accNum) + " account number " + "\n";
    return newMess;
}

void Bank::list(const MyString& username) const {
    int bankAccCount = bankAccounts.getSize();
    for (int i = 0; i < bankAccCount; i++) {
        if (bankAccounts[i].getLhs() == username) {
            std::cout << bankName << " " << bankAccounts[i].getRhs().getAccountNumber();
        }
    }
}

void Bank::addMoneyToBankAcc(int accNum, const MyString& username, int moneyToAdd) {
    int idx = getIdxOfAccountByAccNumAndUsername(accNum, username);
    bankAccounts[idx].getRhs().addMoney(moneyToAdd);
}

MyString Bank::removeBankAcc(const MyString& username, const MyString& curBankName, unsigned accountNumber) {
    int idx = getIdxOfAccountByAccNumAndUsername(accountNumber, username);
    bankAccounts.removeAt(idx);
    MyString newMess = "You removed an acc from bank " + bankName + " with account number " + toString(accountNumber);
    return newMess;
}

MyString Bank::addBankAcc(const MyString& username, const MyString& curBankName) {
    Account newAcc;
    Pair<MyString, Account> newPair(username, newAcc);
    bankAccounts.pushBack(newPair);
    MyString newMess = "You added an acc in bank " + bankName + " with account number " + toString(newAcc.getAccountNumber());
    return newMess;
}


int Bank::getIdxOfAccountByAccNum(unsigned accNum) const{
    int bankAccountsCount = bankAccounts.getSize();
    if (bankAccountsCount == 0) {
        throw std::runtime_error("there are no acconts existing in that bank.");
    }
    for (size_t i = 0; i < bankAccountsCount; i++) {
        if (bankAccounts[i].getRhs().getAccountNumber() == accNum) {
            return i;
        }
    }
    throw std::runtime_error("There is no account with that acc num.");
}

int Bank::getIdxOfAccountByAccNumAndUsername(unsigned accNum, const MyString& username) const {
    int bankAccountsCount = bankAccounts.getSize();
    if (bankAccountsCount == 0) {
        throw std::runtime_error("there are no acconts existing in that bank.");
    }
    for (size_t i = 0; i < bankAccountsCount; i++) {
        if (bankAccounts[i].getRhs().getAccountNumber() == accNum && bankAccounts[i].getLhs() == username) {
            return i;
        }
    }
    throw std::runtime_error("There is no account with that acc num and username.");
}

Employee* Bank::searchEmployeeByUsername(const MyString& username)
{
    int employeesCount = employees.getSize();
    Employee* searchedEmployee = nullptr;
    for (int i = 0; i < employeesCount; i++) {
        if (employees[i].getUsername() == username) {
            return searchedEmployee;
        }
    }
    return nullptr;
}

Employee* Bank::getLeastBusiestEmployee() {
    int employeesCount = employees.getSize();
    if (employeesCount == 0) {
        throw std::runtime_error("No emplyees available.");
    }

    Employee* leastBusiest = &employees[0];
    for (int i = 0; i < employeesCount; i++) {
        if (employees[i].getTasksCount() < leastBusiest->getTasksCount()) {
            leastBusiest = &employees[i];
        }
    }
    return leastBusiest;
}

const MyString& Bank::getBankName() const {
    return bankName;
}
