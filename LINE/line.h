#ifndef METRO_LINE_LINE_H
#define METRO_LINE_LINE_H
#include "../STATION/station.h"
#include <list>
#include "../LIST/list.h"

namespace Line_ns {
    using namespace templateClass;

    class Line {
    private:
        std::string name;           //название линии
        List<Station_ns::Station*> list{};
        List<Station_ns::Station*>::Iterator i;  //итератор


    public:
        Line(): name("None") {};
        Line(const Line& line) {};
        Line(Line&& line) noexcept {};


        const std::string& getName() const { return name; };    //получить название линии

        Line& set(Station_ns::Station* station) noexcept;            //включить новый элемент

        Station_ns::Station* getStation(std::string& name_x) noexcept;    //вернуть элемент по названию станции

        friend std::ostream& operator<<(std::ostream& out, Line& line) noexcept;     //показать содержимое таблицы

        Line& remove(std::string& name_x) noexcept;

        ~Line();
    };

}

#endif //METRO_LINE_LINE_H
