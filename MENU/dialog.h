#ifndef METRO_LINE_DIALOG_H
#define METRO_LINE_DIALOG_H
#include <limits>
#include "../LINE/line.h"


template <class T>
int getNum(T &a)
{
    while (true) {
        std::cin >> a;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR! Invalid data! Try again please: ->";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 1;
        }
    }
}


void printMenu();
void addStation(Line_ns::Line& line);
void show(Line_ns::Line& line);
void find(Line_ns::Line& line);
void change(Line_ns::Line& line);
void deleteElement(Line_ns::Line& line);







#endif //METRO_LINE_DIALOG_H
