#pragma once
#include "MyString.h"
#include "DynamicArray.hpp"
#include "Employee.h"
//#include "Client.h"

class Bank {
private:
	MyString bankName = "Unknown";
	DynamicArray<Employee> employees;
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

	Employee* getLeastBusiestEmployee();
	const MyString& getBankName() const;
};