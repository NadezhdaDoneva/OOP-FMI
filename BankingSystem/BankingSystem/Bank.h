#pragma once
#include "MyString.h"
#include "DynamicArray.hpp"
#include "Employee.h"
#include "Pair.hpp"
#include "Account.h"
//#include "Client.h"

class Bank {
private:
	MyString bankName = "Unknown";
	DynamicArray<Employee> employees;
	DynamicArray<Pair<MyString, Account>> bankAccounts; //format: {ClientName: Account[account number, ballance]}
	//DynamicArray<Employee>& employees;
	//DynamicArray<Client> clients;
public:
	Bank() = default;
	Bank(const MyString& name);

	/*const DynamicArray<Client>& getClients() const;*/
	const DynamicArray<Employee>& getEmployees() const;

	/*void addClient(const Client& client);
	void addClient(Client&& client);*/
	void addEmployee(const Employee& employee);
	void addEmployee(Employee&& employee);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

	void assignTask(const Task& task);

	double getBalanceByAccountNumber(unsigned accNum) const;
	MyString openAccount(const MyString& username);
	MyString closeAccount(const MyString& username, unsigned accNum);
	void list(const MyString& username) const;
	void addMoneyToBankAcc(int accNum, const MyString& username, int moneyToAdd);
	MyString removeBankAcc(const MyString& username, const MyString& curBankName, unsigned accountNumber);
	MyString addBankAcc(const MyString& username, const MyString& curBankName);

	int getIdxOfAccountByAccNum(unsigned accNum) const;
	int getIdxOfAccountByAccNumAndUsername(unsigned accNum, const MyString& username) const;


	Employee* searchEmployeeByUsername(const MyString& username);
	Employee* getLeastBusiestEmployee();
	const MyString& getBankName() const;
};