#include <QFile>
#include <QString>
#include <QDateTime>

#include "monster.h"

Monster::Monster()
{
    numCC = 6;

    //missing bigfoot, headless horseman

    //Name, spawn time, link, showOnScreen
    monsterList =
        {
            {"Black Crow", 23 * 60, "https://maplelegends.com/lib/monster?id=9400014", true},
            {"Blue Mushmom", 4 * 60, "https://maplelegends.com/lib/monster?id=9400205", true},
            {"Deo", 60, "https://maplelegends.com/lib/monster?id=3220001", true},
            {"Dodo", 4 * 60, "https://maplelegends.com/lib/monster?id=8220004", true},
            {"Dyle", 2 * 60, "https://maplelegends.com/lib/monster?id=6220000", true},
            {"Eliza", 3 * 60, "https://maplelegends.com/lib/monster?id=8220000", true},
            {"Faust", 2 * 60, "https://maplelegends.com/lib/monster?id=5220002", true},
            {"Female Boss", 8 * 60, "https://maplelegends.com/lib/monster?id=9400121", true},
            {"Griffey", 1 * 60 + 30, "https://maplelegends.com/lib/monster?id=8180001", true},
            {"Jr. Balrog", 3 * 60, "https://maplelegends.com/lib/monster?id=8130100", true},
            {"Kacchuu Musha", 11 * 60, "https://maplelegends.com/lib/monster?id=9400405", true},
            {"Kimera", 3 * 60, "https://maplelegends.com/lib/monster?id=8220002", true},
            {"King Clang", 2 * 60, "https://maplelegends.com/lib/monster?id=5220000", true},
            {"King Sage Cat", 3 * 60, "https://maplelegends.com/lib/monster?id=7220002", true},
            {"Leviathan", 4 * 60, "https://maplelegends.com/lib/monster?id=8220003", true},
            {"Lilynouch", 4 * 60, "https://maplelegends.com/lib/monster?id=8220005", true},
            {"Lyka", 4 * 60, "https://maplelegends.com/lib/monster?id=8220006", true},
            {"Mano", 60, "https://maplelegends.com/lib/monster?id=2220000", true},
            {"Manon", 1 * 60 + 30, "https://maplelegends.com/lib/monster?id=8180000", true},
            {"Mushmom", 2 * 60, "https://maplelegends.com/lib/monster?id=6130101", true},
            {"Pianus(R)", 4 * 60, "https://maplelegends.com/lib/monster?id=8510000", true},
            {"Seruf", 60, "https://maplelegends.com/lib/monster?id=4220000", true},
            {"Snack Bar", 2 * 60, "https://maplelegends.com/lib/monster?id=9410015", true},
            {"Snowman", 3 * 60, "https://maplelegends.com/lib/monster?id=8220001", true},
            {"Spirit of Rock", 12 * 60, "https://maplelegends.com/lib/monster?id=9410035", true},
            {"Stompy", 1 * 60, "https://maplelegends.com/lib/monster?id=3220000", true},
            {"Tae Roon", 3 * 60, "https://maplelegends.com/lib/monster?id=7220000", true},
            {"Timer", 2 * 60, "https://maplelegends.com/lib/monster?id=5220003", true},
            {"Zeno", 2 * 60, "https://maplelegends.com/lib/monster?id=6220001", true},
            {"Zombie Mushmom", 2 * 60, "https://maplelegends.com/lib/monster?id=6300005", true}
        };
}


