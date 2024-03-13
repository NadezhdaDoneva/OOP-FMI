// Exercise 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

enum class Color {
    white,
    green,
    red,
    unknown
};


class Baloon {
private:
    unsigned price;
    Color color;


public:
    Baloon() {
        price = 0;
        color = Color::unknown;
    }

    Baloon(unsigned price, Color color = Color::unknown) {
        this->price = price;
        this->color = color;
    }

    unsigned getPrice() const {
        return price;
    }

    Color getColor() const {
        return color;
    }

    void setPrice(int price) {
        this->price = price;
    }

    void setColor(Color color) {
        this->color = color;
    }
};

int main()
{

}