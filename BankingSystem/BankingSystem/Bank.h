#pragma once
#include "MyString.h"
#include "DynamicArray.hpp"
#include "Employee.h"

class Bank {
private:
	MyString bankName = "Unknown";
	DynamicArray<Employee> employees;
	//masiv ot clienti
public:
	Bank() = default;
	Bank(const MyString& name);
};