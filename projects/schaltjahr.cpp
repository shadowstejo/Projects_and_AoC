#include <iostream>
#include <cmath>

int count_digit(int number) {
    return int(log10(number) + 1);
}

int main() {
    int year;

    std::cout << "Which year do you want to know wether it's a leapyear or not of? \n";
    std::cin >> year;
    system("cls");
    if (count_digit(year) == 4) {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                if (year % 400 == 0) {
                    std::cout << year << " is a leapyear \n";
                } else {
                    std::cout << year << " is divisible by 100 but not by 400 so not a leapyear \n";
                }
            } else {
                std::cout << year << " is a leapyear \n";
            }
        } else {
            std::cout << year << " is not divisible by 4 so it's not a leapyear \n";
        }
    } else {
        std::cout << "Year has to be 4 numbers please \n";
    }
    system("pause");
    return 0;
}
