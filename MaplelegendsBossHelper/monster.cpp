#include <QFile>
#include <QString>
#include <QDateTime>

#include "monster.h"

Monster::Monster()
{
    numCC = 6;

    monsterList =
        {
            {"Bigfoot", {14 * 60 + 30, 15 * 60 + 30, 17 * 60 + 30, 12 * 60, 16 * 60 + 30, 17 * 60, 15 * 60, 16 * 60},
                {"Phantom Forest: Forgotten Path", "Phantom Forest: Evil Rising", "Phantom Forest: The Evil Dead", "Phantom Forest: Twisted Paths", "Phantom Forest: Twisted Paths 2", "Phantom Forest: Twisted Paths 3",
                    "Phantom Forest: Twisted Paths 4", "Phantom Forest: Twisted Paths 5"}, "https://maplelegends.com/lib/monster?id=9400575", true},
            {"Black Crow", {23 * 60}, {"Zipangu: Encounter with the Buddha"}, "https://maplelegends.com/lib/monster?id=9400014", true},
            {"Blue Mushmom", {4 * 60}, {"Zipangu: Hall of Mushroom"}, "https://maplelegends.com/lib/monster?id=9400205", true},
            {"Deo", {1 * 60}, {"Hidden Street: Royal Cactus Desert"}, "https://maplelegends.com/lib/monster?id=3220001", true},
            {"Dodo", {4 * 60}, {"Time Lane: Memory Lane 5"}, "https://maplelegends.com/lib/monster?id=8220004", true},
            {"Dyle", {2 * 60}, {"Warning Street: Dangerous Croko I"}, "https://maplelegends.com/lib/monster?id=6220000", true},
            {"Eliza", {3 * 60}, {"Orbis: Stairway to the Sky II"}, "https://maplelegends.com/lib/monster?id=8220000", true},
            {"Faust", {2 * 60}, {"Hidden Street: The Forest of Evil I"}, "https://maplelegends.com/lib/monster?id=5220002", true},
            {"Female Boss", {8 * 60}, {"Zipangu: Parlor"}, "https://maplelegends.com/lib/monster?id=9400121", true},
            {"Griffey", {1 * 60 + 30}, {"Leafre: Griffey Forest"}, "https://maplelegends.com/lib/monster?id=8180001", true},
            {"Headless Horseman", {10 * 60 + 30, 13 * 60, 13 * 60 + 30, 11 * 60 + 30, 12 * 60 +  30, 13 * 60, 11 * 60, 12 * 60},
                {"Phantom Forest: Forgotten Path", "Phantom Forest: Hidden Evil", "Phantom Forest: Creeping Evil", "Phantom Forest: The Evil Dead", "Phantom Forest: Crossroads", "Phantom Forest: Crossroads 2",
                    "Phantom Forest: Crossroads 3", "Phantom Forest: Hollowed Ground"}, "https://maplelegends.com/lib/monster?id=9400549", true},
            {"Jr. Balrog", {3 * 60}, {"Dungeon: The Cursed Sanctuary"}, "https://maplelegends.com/lib/monster?id=8130100", true},
            {"Kacchuu Musha", {11 * 60}, {"Zipangu: Ninja Castle Hallway"}, "https://maplelegends.com/lib/monster?id=9400405", true},
            {"Kimera", {3 * 60}, {"Hidden Street: Lab - Secret Basement Path"}, "https://maplelegends.com/lib/monster?id=8220002", true},
            {"King Clang", {2 * 60}, {"Florina Road: Hot Sand"}, "https://maplelegends.com/lib/monster?id=5220000", true},
            {"King Sage Cat", {3 * 60}, {"Mu Lung: Goblin Forest 2"}, "https://maplelegends.com/lib/monster?id=7220002", true},
            {"Leviathan", {4 * 60}, {"Hidden Street: Leviathan's Canyon"}, "https://maplelegends.com/lib/monster?id=8220003", true},
            {"Lilynouch", {4 * 60}, {"Time Lane: Road of Regrets 5"}, "https://maplelegends.com/lib/monster?id=8220005", true},
            {"Lyka", {4 * 60}, {"Time Lane: Road to Oblivion 5"}, "https://maplelegends.com/lib/monster?id=8220006", true},
            {"Mano", {1 * 60}, {"Victoria Road: Thicket Around the Beach III"}, "https://maplelegends.com/lib/monster?id=2220000", true},
            {"Manon", {1 * 60 + 30}, {"Leafre: Manon's Forest"}, "https://maplelegends.com/lib/monster?id=8180000", true},
            {"Mushmom", {2 * 60}, {"Hidden Street: Someone Else's House"}, "https://maplelegends.com/lib/monster?id=6130101", true},
            {"Pianus(R)", {4 * 60}, {"Aqua Road: The Cave of Pianus"}, "https://maplelegends.com/lib/monster?id=8510000", true},
            {"Seruf", {1 * 60}, {"Aqua Road: The Seaweed Tower"}, "https://maplelegends.com/lib/monster?id=4220000", true},
            {"Snack Bar", {2 * 60}, {"Taiwan: Night Market Alley 6"}, "https://maplelegends.com/lib/monster?id=9410015", true},
            {"Snowman", {3 * 60}, {"Hidden Street: Valley of Snowman"}, "https://maplelegends.com/lib/monster?id=8220001", true},
            {"Spirit of Rock", {12 * 60}, {"Taiwan: Star Avenue West Section"}, "https://maplelegends.com/lib/monster?id=9410035", true},
            {"Stompy", {1 * 60}, {"Victoria Road: East Rocky Mountain V"}, "https://maplelegends.com/lib/monster?id=3220000", true},
            {"Tae Roon", {3 * 60}, {"Mu Lung: Territory of Wandering Bear"}, "https://maplelegends.com/lib/monster?id=7220000", true},
            {"Timer", {2 * 60}, {"Ludibrium: Whirlpool of Time"}, "https://maplelegends.com/lib/monster?id=5220003", true},
            {"Zeno", {2 * 60}, {"Hidden Street: Gray's Prairie"}, "https://maplelegends.com/lib/monster?id=6220001", true},
            {"Zombie Mushmom", {2 * 60}, {"Dungeon: The Grave of Mushmom"}, "https://maplelegends.com/lib/monster?id=6300005", true}
        };
}


