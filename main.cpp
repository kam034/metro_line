#include <iostream>
#include "LINE/line.h"
#include "MENU/dialog.h"

int main()
{
    int command;
    Line_ns::Line tmp;

    printMenu();

    do {
        std::cout << "Make a choice, please ->";
        getNum(command);
        switch(command)
        {
            case 0:
                std::cout << "EXIT!" << std::endl;
                break;
            case 1:
                addStation(tmp);
                break;
            case 2:
                find(tmp);
                break;
            case 3:
                change(tmp);
                break;
            case 4:
                deleteElement(tmp);
                break;
            case 5:
                show(tmp);
                break;
            default:
                std::cout << "ERROR! There is no such point." << std::endl;
        }
    } while (command != 0);

    return 0;
}