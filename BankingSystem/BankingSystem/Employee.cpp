#include "Employee.h"

Employee::Employee(const MyString& username, const MyString& egn, unsigned age, const MyString& password, const MyString& bankName)
	: User(username, egn, age, password), bankName(bankName) {}
