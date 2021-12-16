#include "../STATION/station.h"
//#include "..\..\metro_line\line.h"
#include "lib\googletest-master\googletest\include\gtest\gtest.h"

using namespace Station_ns;

TEST(StationsConstructors, Constructor) {

    std::string b = {"hello_it's_me"};
    Station a(b);
    ASSERT_EQ(b, a.getName());

    Station_transition c(b);
    ASSERT_EQ(b, c.Station::getName());

    std::string str[Station_transition::n] = {"abc", "def", "ghi"};
    Station_transition d(b, str);
    ASSERT_EQ(d.getName(d), b);
    ASSERT_EQ(d.getNameLine(0), str[0]);
    ASSERT_EQ(d.getNameLine(1), str[1]);
    ASSERT_EQ(d.getNameLine(2), str[2]);

    Transfer_hub::Transition names[Transfer_hub::m] = {"Zelenaya", "Kashirskaya",
                                                       "Krasnaya", "Lublino",
                                                       "Sinaya", "Baumanskaya"};
    Transfer_hub f(b, names);
    ASSERT_EQ(f.getNames(2).name_station_tr, "Baumanskaya");
    ASSERT_EQ(f.getNames(1).name_line_tr, "Krasnaya");
}


TEST(StationsMethods, Method) {
    Station a;
    ASSERT_EQ(0, a.getType());
    Station_transition b;
    ASSERT_EQ(1, b.getType());
    Transfer_hub c;
    ASSERT_EQ(2, c.getType());

    std::string string = {"how_are_you"};
    a.change_name(string);
    ASSERT_EQ(string, a.getName());
    b.change_name(string);
    ASSERT_EQ(string, a.getName());
    c.change_name(string);
    ASSERT_EQ(string, a.getName());
}

TEST(StationsMethods, ChangeTypeFunction) {
    std::string str = {"MetroLublino"};
    Station a(str);
    auto b = a.changeType(1);
    ASSERT_EQ(b->getType(), 1);
    ASSERT_EQ(b->getName(), str);

    std::string rr[3] = {"sdf", "sdfg", "wert"};
    Station_transition st(str, rr);
    b = st.changeType(0);
    ASSERT_EQ(b->getType(), 0);
    b = st.changeType(1);
    ASSERT_EQ(b->getType(), 1);
    ASSERT_EQ(b->getName(), str);

    Transfer_hub::Transition names[Transfer_hub::m] = {"Zelenaya", "Kashirskaya",
                                                       "Krasnaya", "Lublino",
                                                       "Sinaya", "Baumanskaya"};
    Transfer_hub tr(str, names);
    b = tr.changeType(1);
    ASSERT_EQ(b->getType(), 1);
    ASSERT_EQ(b->getName(), str);
    b = tr.changeType(0);
    ASSERT_EQ(b->getName(), str);
    ASSERT_EQ(b->getType(), 0);
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}