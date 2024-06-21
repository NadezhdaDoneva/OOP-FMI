#include "Bank.h"
#include <fstream>

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
    ofs.close();
}

void Bank::readFromFile(std::ifstream& ifs) {
    bankName.readFromFile(ifs);
    int employeesInCurBankCount = 0;
    ifs.read((char*)&employeesInCurBankCount, sizeof employeesInCurBankCount);
    for (size_t i = 0; i < employeesInCurBankCount; i++) {
        employees[i].readFromFile(ifs);
    }
    ifs.close();
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
