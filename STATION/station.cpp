#include "station.h"


namespace Station_ns {

    // БЕСПЕРЕСАДОЧНАЯ СТАНЦИЯ - БАЗОВЫЙ КЛАСС


    Station &Station::change_name(std::string &name_x) {          //изменить название станции
        this->name = name_x;
        return *this;
    }

    std::ostream &operator<<(std::ostream &out, const Station &st) {      //вывод информации о странции
        out << "The name of the station: ";
        out << st.getName() << std::endl;
        return out;
    };

    // вирт функция зависит от типа, к которому применяется объект
    // i - тип станции, на которую нужно изменить существующий

    Station* Station::changeType(int type) {//st - объект истинно базового класса
        if (type == STATION_TRANSITION) {
            auto* a = new Station_transition(*this);
            a->change_name(this->name);
            return a;
        }
        if (type == TRANSFER_HUB) {
            auto* a = new Transfer_hub(*this);
            a->change_name(this->name);
            return a;
        }
        return this;
    }


        // СТАНЦИЯ С ПЕРЕХОДОМ

        Station_transition::Station_transition(std::string & name_x, std::string
        arr_str[n]) {
            name = name_x;
            for (int i = 0; i < n; i++) {
                name_line_tr[i] = arr_str[i];
            }
        }

        Station_transition &Station_transition::addNameLine(std::string &name_x) {   //добавить название линии перехода
        if (!name_line_tr[n-1].empty())
            throw std::out_of_range("Maximum number of transition lines");
        for (auto &i : name_line_tr) {
                if (i.empty()) {
                    i = name_x;
                    return *this;
                }
            }
        }

        std::ostream &operator<<(std::ostream &out, const Station_transition &st) {
            out << "The name of the station with transition: ";
            out << st.getName(st) << std::endl;
            out << "Tne names of transition lines: " << std::endl;
            for (int i = 0; i < Station_transition::n; i++) {
                if (!st.getNameLine(i).empty())
                    out << " - " << st.getNameLine(i) << std::endl;
            }
            return out;
        }


    Station* Station_transition::changeType (int type) {
        if (type == STATION) {
            auto* a = new Station;
            a->change_name(this->name);
            return a;
        }
        if (type == TRANSFER_HUB) {
            auto* a = new Transfer_hub(*this);
            a->change_name(this->name);
            return a;
        }
        return this;
    }



        // ПЕРЕСАДОЧНЫЙ УЗЕЛ

        Transfer_hub::Transfer_hub(std::string & name_x, Transition* arr_st) : Station_transition(name_x) {
            for (int i = 0; i < n; i++)
                arr[i] = arr_st[i];
        }



        Transfer_hub &Transfer_hub::addNameTr(Transition& names) {
            if (!arr[m-1].name_line_tr.empty())
                throw std::out_of_range("Maximum number of transitions");
            for (auto & i : arr) {
                if (i.name_line_tr.empty()) {
                    i = names;
                    return *this;
                }
            }
            return *this;
        }

        std::ostream &operator<<(std::ostream &out, const Transfer_hub &st) {
            out << "The name of the transfer hub: ";
            out << st.getName(st) << std::endl;
            out << "Tne names of transition lines and stations:" << std::endl;
            for (int i = 0; i < Transfer_hub::m; i++) {
                if (!st.getNames(i).name_line_tr.empty())
                    out << " - " << st.getNames(i).name_line_tr << ": " << st.getNames(i).name_station_tr << std::endl;
            }
            return out;
        }

    Station* Transfer_hub::changeType(int type) {
        if (type == STATION) {
            auto* a = new Station;
            a->change_name(this->name);
            return a;
        }
        if (type == STATION_TRANSITION) {
            auto* a = new Station_transition;
            a->change_name(this->name);
            for (int i = 0; i < n; i++) {
                if (!this->getNames(i).name_line_tr.empty()) {
                    std::string w = this->getNames(i).name_line_tr;
                    a->addNameLine(w);
                }
            }
            return a;
        }
//        if (type == TRANSFER_HUB) {
            return this;
//        }
    }
    }


