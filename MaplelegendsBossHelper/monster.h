#ifndef MONSTER_H
#define MONSTER_H


//Name, spawn time, link, showOnScreen
std::vector <std::tuple <std::string, int, std::string, bool> > monsterList =
{
    {"Deo", 60, "https://maplelegends.com/lib/monster?id=3220001", true},
    {"Faust", 2*60, "https://maplelegends.com/lib/monster?id=5220002", true},
    {"Mano", 60, "https://maplelegends.com/lib/monster?id=2220000", true},
    {"Seruf", 60, "https://maplelegends.com/lib/monster?id=4220000", true}

};

#endif // MONSTER_H
