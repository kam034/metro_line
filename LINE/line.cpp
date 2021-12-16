#include "line.h"
namespace Line_ns {

    Station_ns::Station* Line::getStation(std::string &name_x) noexcept {
        for (auto n = list.begin(); n != list.end(); n++) {
            if ((*n)->getName() == name_x) {
                return (*n);
            }
        }
        return nullptr;
    }


    Line& Line::set(Station_ns::Station* station) noexcept {            //включить новый элемент
        list.push_back(station);
        return *this;
    }

    std::ostream& operator<<(std::ostream& out, Line& line) noexcept {
        int i = 1;
        for (auto n = line.list.begin(); n != line.list.end(); n++) {
            if (gettype(*n) == 0) {
                out << "==========" << i << "==========" << std::endl << **n << std::endl;
                i++;
            }
            if (gettype(*n) == 1) {
                auto *st = dynamic_cast<Station_ns::Station_transition*>(*n);
                out << "=========="<< i << "==========" << std::endl << *st << std::endl;
                i++;
            }
            if (gettype(*n) == 2) {
                auto *st = dynamic_cast<Station_ns::Transfer_hub*>(*n);
                out << "=========="<< i << "=========="<< std::endl << *st << std::endl;
                i++;
            }
        }
        return out;
    }


    Line& Line::remove(std::string &name_x) noexcept {

        for (auto n = list.begin(); n != list.end(); n++) {
            if ((*n)->getName() == name_x) {
                list.erase(n);
                return *this;
            }
        }
        return *this;
    }

    Line::~Line() {
        for (auto & n : list) {
            delete n;
            }
        }
    }

