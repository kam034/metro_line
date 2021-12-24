#ifndef METRO_LINE_STATION_H
#define METRO_LINE_STATION_H
#include <iostream>

namespace Station_ns {

    /**
     * Station Descriptor - base class
     */
    class Station {

    protected:
        /**
         * station name
         */
        std::string name;

    public:
        /**
         * type of the station
         */
        enum type_station {
            STATION = 0,
            STATION_TRANSITION = 1,
            TRANSFER_HUB = 2
        };

        /**
         * Empty constructor
         */
        Station(): name("None") {};

        /**
         * Initializing constructor
         * @param name_x station name
         */
        explicit Station(std::string& name_x): name(name_x) {};

        /**
         * Getter - get the private value - name of the station
         * @return station name
         */
        virtual const std::string& getName() const { return name; };

        /**
         * Setter - change the station name
         * @param name_x the name of the station to change
         * @return object reference
         */
        Station& change_name(std::string& name_x);

        /**
         * Virtual method - returns the object type
         * @return station type
         */
        virtual type_station getType() const { return STATION; };

        /// Friendly method output overload
        /// \param out output stream
        /// \param st a reference to the object to be output
        /// \return output stream
        friend std::ostream& operator<<(std::ostream& out, const Station& st);

        /**
         * Virtual method - changes the type of an existing object
         * @details Creates a new object and returns a pointer to it
         * @param type type of the station
         * @return pointer to the object
         */
        virtual Station* changeType(int type);

    };



    /**
     * Station with transition descriptor
     */
    class Station_transition : public Station {

    public:
        /**
         * Number of transition line
         */
        static const int n = 3;
    protected:
        /**
         * Array of transition line names
         */
        std::string name_line_tr[n];

    public:
        /**
         * Empty constructor
         */
        Station_transition() = default;

        /**
         * Initializing constructor
         * @param name_x station name
         */
        explicit Station_transition(std::string& name_x) { name = name_x; };

        /**
         * Initializing constructor - full
         * @param name_x station name
         * @param arr_str array of transition line names
         */
        explicit Station_transition (std::string& name_x, std::string arr_str[n]);

        /**
         * Copy constructor
         * @details copies only the station name
         * @param st object reference
         */
        explicit Station_transition(const Station& st): Station(st) {};


        /**
         * Getter - get the private value - name of the transition line
         * @param i index of array
         * @return name of the transition line
         */
        const std::string& getNameLine(int i) const { return name_line_tr[i]; }

        /**
         * Virtual method - returns the station name
         * @return station name
         */
        virtual const std::string& getName(const Station_transition& st) const { return name; };

        /**
         * Virtual method - changes the type of an existing object
         * @details Creates a new object and returns a pointer to it
         * @param type type of the station
         * @return pointer to the object
         */
        Station* changeType (int type) override;

        /**
         * Getter - get the private value - name of the transition line
         * @return array of name of the transition line
         */
        std::string *getArrLine() { return name_line_tr; }

        /**
         * Setter - adds the name of the transition line
         * @param name_x name of the transition line
         * @return reference object
         */
        Station_transition& addNameLine(std::string& name_x);

        /**
         * Virtual method - returns the object type
         * @return station type
         */
        type_station getType() const override  { return STATION_TRANSITION; }

        /// Friendly method output overload
        /// \param out output stream
        /// \param st a reference to the object to be output
        /// \return output stream
        friend std::ostream& operator<<(std::ostream& out, const Station_transition& st);     //вывод информации о станции

    };


    /**
     * Transfer hub descriptor
     */
    class Transfer_hub : public Station_transition {

    public:
        /**
         * Number of transition
         */
        static const int m = 3;

        /**
         * structure for describing lines and transfer stations
         */
        struct Transition {
            std::string name_line_tr;
            std::string name_station_tr;
        };

    private:
        /**
         * array of names lines and transfer stations
         */
        Transition arr[m];

    public:
        /**
         * Empty constructor
         */
        Transfer_hub() = default;

        /**
         * Initializing constructor
         * @param name_x station name
         */
        explicit Transfer_hub(std::string& name_x) {name = name_x;};

        /**
         * Initializing constructor - full
         * @param name_x station name
         * @param arr_st array of transition
         */
        Transfer_hub(std::string & name_x, Transition* arr_st);

        /**
         * Copy constructor
         * @details use constructor from class Station_transition
         * @param st object reference
         */
        explicit Transfer_hub(const Station& st) : Station_transition(st) {};

        /**
         * Getter - get the private value - name of the transition
         * @param i - index of array of the transition
         * @return transition - station and line name
         */
        Transition getNames(int i) const { return arr[i]; }

        /**
         * Virtual method - returns the station name
         * @return station name
         */
        virtual const std::string& getName(const Transfer_hub& st) const { return name; };

        /**
         * Getter - get the array of transition
         * @return array
         */
        Transition* getArrNames() { return arr; };

        /**
         * Virtual method - returns the object type
         * @return station type
         */
        type_station getType() const final { return TRANSFER_HUB; }

        /// Friendly method output overload
        /// \param out output stream
        /// \param st a reference to the object to be output
        /// \return output stream
        friend std::ostream& operator<<(std::ostream& out, const Transfer_hub& st);

        /**
         * Setter - adds the name of the transition
         * @param name_x name of the transition
         * @return reference object
         */
        Transfer_hub &addNameTr(Transition& names);

        /**
         * Virtual method - changes the type of an existing object
         * @details Creates a new object and returns a pointer to it
         * @param type type of the station
         * @return pointer to the object
         */
        Station* changeType(int type) final;
    };

    /**
     * function - return real station type
     * @param station pointer to the station
     * @return station type
     */
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
