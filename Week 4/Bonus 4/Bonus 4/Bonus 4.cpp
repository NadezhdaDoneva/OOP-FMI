// Bonus 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
const int MAX_COUNT_NIGHTCLUB = 1000;
const int MAX_SIZE_NARGA_BRAND = 1024;


enum class Color {
    white,
    green,
    red,
    unknown
};

enum class Taste
{
    blueberry,
    queen,
    mango,
    strawberry,
    gum,
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

    void setColor(const Color& color) {
        this->color = color;
    }
};

class Narga {
private:
    unsigned price;
    char brand[MAX_SIZE_NARGA_BRAND];
    Taste taste;

public:
    Narga() {
        price = 0;
        strcpy(brand, "");
        taste = Taste::unknown;
    }

    Narga(unsigned price, char* brand, Taste taste) {
        this->price = price;
        strcpy(this->brand, brand);
        this->taste = taste;
    }

    unsigned getPrice() const {
        return price;
    }

    const char* getBrand() const {
        return brand;
    }

    Taste getTaste() const {
        return taste;
    }

    void setPrice(unsigned price) {
        this->price = price;
    }

    void setBrand(char* brand) {
        strcpy(this->brand, brand);
    }

    void setTaste(const Taste& taste) {
        this->taste = taste;
    }

    void readInput() {
        std::cin >> this->price;
        std::cin.getline(this->brand, MAX_SIZE_NARGA_BRAND);
        unsigned t;
        std::cin >> t;
        this->taste = Taste(t);
    }

    void print() const {
        std::cout << this->price;
        std::cout << this->brand;
        std::cout << (int)this->taste;
    }
};

class NightClub {
    
};


int main()
{
    std::cout << "Hello World!\n";
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
