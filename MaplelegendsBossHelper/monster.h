#ifndef MONSTER_H
#define MONSTER_H

class Monster
{
public:
    Monster();

public:
    //Name, spawn time, spawn maps, link, listMapsshowOnScreen
    QVector<std::tuple <QString, QList<int>, QStringList, QString, bool> > monsterList;
    int numCC;
};

#endif // MONSTER_H
