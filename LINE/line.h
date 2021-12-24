#ifndef METRO_LINE_LINE_H
#define METRO_LINE_LINE_H
#include "../STATION/station.h"
//#include <list>
#include "../LIST/list.h"

namespace Line_ns {
    using namespace templateClass;

    /**
     * Metro Line Descriptor
     */
    class Line {
    private:
        /**
         * Name of the station
         */
        std::string name;

        /// List of pointers at the station
        List<Station_ns::Station*> list{};

        /// Iterator for the list
        List<Station_ns::Station*>::Iterator i;


    public:
        /**
         * Empty constructor
         */
        Line(): name("None") {};

        /// Getter - get the private value - name of the station
        /// \return station name
        const std::string& getName() const { return name; };

        /// Add the new element in the list with the station.
        /// \param station pointer to the station
        /// \return object reference
        Line& set(Station_ns::Station* station) noexcept;

        /// Find and return element by station name
        /// \param name_x name of the station to be returned
        /// \return pointer to the station
        Station_ns::Station* getStation(std::string& name_x) noexcept;

        /// Friendly method output overload
        /*!
         *  @details Works with overloads for station types
         */
        /// \param out output stream
        /// \param line a reference to the object to be output
        /// \return output stream
        friend std::ostream& operator<<(std::ostream& out, Line& line) noexcept;

        /// Deletes an object from the list by station name
        /// \param name_x
        /// \return
        Line& remove(std::string& name_x) noexcept;

        /// Destructor - deletes the list of stations
        ~Line();
    };

}

#endif //METRO_LINE_LINE_H
