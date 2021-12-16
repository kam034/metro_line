#include "dialog.h"


void printMenu() {
    std::cout << "=====This is a program for working with the metro line=====" << std::endl;
    std::cout << "0. Quit" << std::endl;
    std::cout << "1. Add a new station" << std::endl;
    std::cout << "2. Find a station by name" << std::endl;
    std::cout << "3. Change the station description" << std::endl;
    std::cout << "4. Delete a station" << std::endl;
    std::cout << "5. Show the list of stations" << std::endl;
}


void addStation(Line_ns::Line& line) {
    std::cout << "What type of station do you want to add?" << std::endl;
    std::cout << "0 - non-stop station" << std::endl;
    std::cout << "1 - station with transition" << std::endl;
    std::cout << "2 - transfer hub" << std::endl;
    std::cout << "Please, enter the number -> " << std::endl;
    int c, t; std::string name;
    Station_ns::Transfer_hub::Transition tr;
    getNum(c);
    switch (c) {
        case 0: {
            std::cout << "Enter the name of station -> " << std::endl;
            std::cin >> name;
            auto *a = new Station_ns::Station;
            a->change_name(name);
            line.set(a);
            break;
        }
        case 1: {
            std::cout << "Enter the name of station -> " << std::endl;
            std::cin >> name;
            auto* b = new Station_ns::Station_transition;
            b->change_name(name);
            std::cout << "How many transition lines do you want to add? (max - " << Station_ns::Station_transition::n <<  ")" << std::endl;
            getNum(t);
            while (t > Station_ns::Station_transition::n) {
                std::cout << "Enter the correct number of transition lines" << std::endl;
                getNum(t);
            }
            for (int i = 0; i < t; i++) {
                std::cin >> name;
                b->addNameLine(name);
            }
            line.set(b);
            break;
        }
        case 2: {
            std::cout << "Enter the name of station -> " << std::endl;
            std::cin >> name;
            auto* r = new Station_ns::Transfer_hub;
            r->change_name(name);
            std::cout << "How many transitions do you want to add? (max - " << Station_ns::Transfer_hub::m <<  ")" << std::endl;
            getNum(t);
            while (t > Station_ns::Station_transition::n) {
                std::cout << "Enter the correct number of transition lines" << std::endl;
                getNum(t);
            }
            for (int i = 0; i < t; i++) {
                std::cin >> tr.name_line_tr >> tr.name_station_tr;
                try {
                    r->addNameTr(tr);
                }
                catch (std::out_of_range &outOfRange) {
                    std::cout << outOfRange.what() << std::endl;
                }
            }
            line.set(r);
            break;
        }
        default:
            std::cout << "There is no such types" << std::endl;
    }
}


void show(Line_ns::Line& line) {
    std::cout << "The list of stations: " << std::endl;
    std::cout << line;
}

void find(Line_ns::Line& line) {
    std::string str;
    std::cout << "Enter the name of the station -> " ;
    std::cin >> str;

    if (gettype(line.getStation(str)) == -1) {
        std::cout << "There is NO such element" << std::endl;
        return;
    }

    if (gettype(line.getStation(str)) == 0) {
        auto *a = line.getStation(str);
        std::cout << *a;
    }
    else if (gettype(line.getStation(str)) == 1) {
        auto *a = dynamic_cast<Station_ns::Station_transition *>(line.getStation(str));
        std::cout << *a;
    }
    else {
        auto* a = dynamic_cast<Station_ns::Transfer_hub *>(line.getStation(str));
        std::cout << *a;
    }
}

void change(Line_ns::Line& line) {
    int c;
    std::cout << "Enter the name of the station you want to change - > ";
    std::string str, strNew;
    std::cin >> str;
    if (gettype(line.getStation(str)) == -1) {
        std::cout << "There is NO such element" << std::endl;
        return;
    }

    if (gettype(line.getStation(str)) == 0) {
        auto *a = line.getStation(str);
        std::cout << "What exactly do you want to change?" << std::endl;
        std::cout << "0 - nothing" << std::endl;
        std::cout << "1 - name" << std::endl;
        std::cout << "2 - type" << std::endl;
        std::cout << "Please, enter the number -> " << std::endl;
        getNum(c);
        switch (c) {
            case 0:
                break;
            case 1: {
                std::cout << "Enter the new name -> ";
                std::cin >> strNew;
                a->change_name(strNew);
                break;
            }
            case 2: {
                std::cout << "0 - non-stop station" << std::endl;
                std::cout << "1 - station with transition" << std::endl;
                std::cout << "2 - transfer hub" << std::endl;
                std::cout << "Enter the new type -> ";
                getNum(c);
                while (c > 3 || c < 0) {
                    std::cout << "Enter the correct number -> " << std::endl;
                    getNum(c);
                }
                auto *b = a->changeType(c);
                line.remove(str);
                line.set(b);
                break;
            }
        }
    }
    else if (gettype(line.getStation(str)) == 1) {
        auto *a = dynamic_cast<Station_ns::Station_transition *>(line.getStation(str));
        std::cout << "What exactly do you want to change?" << std::endl;
        std::cout << "0 - nothing" << std::endl;
        std::cout << "1 - name" << std::endl;
        std::cout << "2 - type" << std::endl;
        std::cout << "3 - name of transition line" << std::endl;
        std::cout << "Please, enter the number -> " << std::endl;
        getNum(c);
        switch (c) {
            case 0:
                break;
            case 1: {
                std::cout << "Enter the new name -> ";
                std::cin >> strNew;
                a->change_name(strNew);
                break;
            }
            case 2: {
                std::cout << "0 - non-stop station" << std::endl;
                std::cout << "1 - station with transition" << std::endl;
                std::cout << "2 - transfer hub" << std::endl;
                std::cout << "Enter the new type -> ";
                getNum(c);
                while (c > 2 || c < 0) {
                    std::cout << "Enter the correct number -> " << std::endl;
                    getNum(c);
                }
                auto *b = a->changeType(c);
                line.remove(str);
                line.set(b);
                break;
            }
            case 3: {
                std::cout << "Enter the name of new transition line - >";
                std::cin >> strNew;
                try {
                    a->addNameLine(strNew);
                }
                catch (std::out_of_range& a) {
                    std::cout << a.what() << std::endl;
                }
            }
        }
    }
    else {
        auto* a = dynamic_cast<Station_ns::Transfer_hub *>(line.getStation(str));
        std::cout << "What exactly do you want to change?" << std::endl;
        std::cout << "0 - nothing" << std::endl;
        std::cout << "1 - name" << std::endl;
        std::cout << "2 - type" << std::endl;
        std::cout << "3 - name of transition(line + station)" << std::endl;
        std::cout << "Please, enter the number -> " << std::endl;
        getNum(c);
        switch (c) {
            case 0:
                break;
            case 1: {
                std::cout << "Enter the new name -> ";
                std::cin >> strNew;
                a->change_name(strNew);
                break;
            }
            case 2: {
                std::cout << "0 - non-stop station" << std::endl;
                std::cout << "1 - station with transition" << std::endl;
                std::cout << "2 - transfer hub" << std::endl;
                std::cout << "Enter the new type -> ";
                getNum(c);
                while (c > 2 || c < 0) {
                    std::cout << "Enter the correct number -> " << std::endl;
                    getNum(c);
                }
                auto *b = a->changeType(c);
                line.remove(str);
                line.set(b);
                break;
            }
            case 3: {
                std::cout << "Enter the name of new transition line - >";
                std::cin >> strNew;
                std::cin >> str;
                Station_ns::Transfer_hub::Transition tr = {strNew, str};
                try {
                    a->addNameTr(tr);
                }
                catch (std::out_of_range& a) {
                    std::cout << a.what() << std::endl;
                }
            }
        }
    }
}

void deleteElement(Line_ns::Line& line) {
    std::cout << "Enter the name of station you want remove - >";
    std::string a;
    std::cin >> a;
    if (line.getStation(a) == nullptr) {
        std::cout << "There is no such element" << std::endl;
        return;
    }
    line.remove(a);
}
