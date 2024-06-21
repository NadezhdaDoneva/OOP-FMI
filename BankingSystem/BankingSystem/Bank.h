#pragma once
#include "MyString.h"
#include "DynamicArray.hpp"
#include "Employee.h"
//#include "Client.h"

class Bank {
private:
	MyString bankName = "Unknown";
	DynamicArray<Employee> employees;
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

	Employee* searchEmployeeByUsername(const MyString& username);
	Employee* getLeastBusiestEmployee();
	const MyString& getBankName() const;
};