// Exercise 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>;

//PRAKTIKUM
//Задача 1:
void printSumFromFile(const char* fileName)
    {
    // Създайте предвително текстов файл, 
    // съдържащ 2 цели числа, разделени с
    // интервал (на един ред)
    //TO DO

    std::ifstream file;
    file.open(fileName);
    if (!file.is_open())
    {
        std::cout << "Can't open file" << std::endl;
    }

    int a;
    int sum = 0;
    while (!file.eof())
    {
        file >> a;
        sum += a;
    }
    std::cout << sum << std::endl;
    file.close();
}

//Задача 2:
unsigned findMaxNumFromFile(const char* fileName) {
    // Създайте предвително текстов файл, 
    // съдържащ няколко цели числа, разделени
    // с интервал (на един ред)
    //TO DO

    std::ifstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        std::cout << "Can't open file" << std::endl;
    }
    int max = INT32_MIN;
    while (!file.eof())
    {
        int a;
        file >> a;
        if (a > max)
        {
            max = a;
        }
    }
    return max;
    file.close();
}

   
unsigned findOcurances(const char*& fileName, char symbol) {
    std::ifstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        std::cout << "Can't open file" << std::endl;
        return 0;
    }
    unsigned counter = 0;
    char ch;
    while (!file.eof())
    {
        file.get(ch);
        if (ch == symbol)
        {
            counter++;
        }
    }
    return counter + 1;
}

//Задача 3:
unsigned getLinesCount(const char* fileName) {
    //TO DO
    // Упътване: Използвайте допълнителна функция
    std::ifstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        std::cout << "Can't open file" << std::endl;
        return 0;
    }

    unsigned res = findOcurances(fileName, '\n');
    return res;
}

int main()
{
    //PRAKTIKUM
    //zad 1
    printSumFromFile("text1.txt");
    //zad2
    std::cout << findMaxNumFromFile("text2.txt") << std::endl;
    //zad3
    std::cout << getLinesCount("text3.txt");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
