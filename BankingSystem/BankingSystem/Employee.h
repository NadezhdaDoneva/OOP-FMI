#pragma once
#include "DynamicArray.hpp" 
#include "MyString.h"
#include "Task.h"
#include "User.h"


class Employee : public User {
public:
	Employee() = default;
	Employee(const MyString& username, const MyString& egn, unsigned age, const MyString& password, const MyString& bankName);
private:
	MyString bankName;
	DynamicArray<Task> tasks;
};