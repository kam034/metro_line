#ifndef METRO_LINE_STATION_H
#define METRO_LINE_STATION_H
#include <iostream>

namespace Station_ns {

    //беспересадочная станция
    class Station {

    protected:
        std::string name;

    public:
        enum type_station {
            STATION = 0,
            STATION_TRANSITION = 1,
            TRANSFER_HUB = 2
        };

        //конструкторы
        Station(): name("None") {
        };
        explicit Station(std::string& name_x): name(name_x) {};
        Station(const Station& st): name(st.name) {};
        Station(Station&& st) noexcept {};

        //геттеры
        virtual const std::string& getName() const { return name; }; //вернуть название станции

        //методы
        Station& change_name(std::string& name_x);         //изменить название станции
        virtual type_station getType() const { return STATION; };  //вернуть тип станции
        friend std::ostream& operator<<(std::ostream& out, const Station& st); //вывод информации о странции
        virtual Station* changeType(int type);

    };


    //станция с переходом
    class Station_transition : public Station {

    public: static const int n = 3;
    protected:
        std::string name_line_tr[n];

    public:
        //контрукторы
        Station_transition() = default;
        explicit Station_transition(std::string& name_x) { name = name_x; };
        explicit Station_transition (std::string& name_x, std::string arr_str[n]);
        explicit Station_transition(const Station& st): Station(st) {

        };
        Station_transition(const Station_transition& st) {};

        //геттеры
        const std::string& getNameLine(int i) const { return name_line_tr[i]; }

        //методы
        virtual const std::string& getName(const Station_transition& st) const { return name; };
        Station* changeType (int type) override;
        std::string *getArrLine() { return name_line_tr; }  //вернуть перечень названий линий перехода
        Station_transition& addNameLine(std::string& name_x);   //добавить название линии перехода
        type_station getType() const override  { return STATION_TRANSITION; } //вернуть тип станции
        friend std::ostream& operator<<(std::ostream& out, const Station_transition& st);     //вывод информации о станции

    };


    //пересадочный узел
    class Transfer_hub : public Station_transition {

    public: static const int m = 3;

        struct Transition {
            std::string name_line_tr;
            std::string name_station_tr;
        };

    private:

        Transition arr[m];

    public:
        //конструкторы
        Transfer_hub() = default;
        explicit Transfer_hub(std::string& name_x) {name = name_x;};
        Transfer_hub(std::string & name_x, Transition* arr_st);
        explicit Transfer_hub(const Station& st) : Station_transition(st) {};

        //геттеры
        Transition getNames(int i) const { return arr[i]; }

        //методы
        virtual const std::string& getName(const Transfer_hub& st) const { return name; };
        Transition* getArrNames() { return arr; };   //вернуть в кач-ве результата перечень названий линий и станций переходов
        type_station getType() const final { return TRANSFER_HUB; }  //вернуть тип станции
        friend std::ostream& operator<<(std::ostream& out, const Transfer_hub& st);     //вывод информации о станции
        Transfer_hub &addNameTr(Transition& names);  //добавить название станции перехода и линии перехода
        Station* changeType(int type) final;
        virtual int gettype(Station* station) {
            if (dynamic_cast<Station*>(station))
                return STATION;
            else if (dynamic_cast<Station_transition*>(station))
                return STATION_TRANSITION;
            else return TRANSFER_HUB;
        }
    };

//    static int gettype(Station* station) {
//        if (station == nullptr)
//            return -1;
//        if (dynamic_cast<Transfer_hub*>(station))
//            return 2;
//        else if (dynamic_cast<Station_transition*>(station))
//            return 1;
//        else return 0;
//    }

    static int gettype(const Station* station) {
        if (station == nullptr)
            return -1;
        if (dynamic_cast<const Transfer_hub*>(station))
            return 2;
        else if (dynamic_cast<const Station_transition*>(station))
            return 1;
        else return 0;
    }
}

#endif //METRO_LINE_STATION_H
