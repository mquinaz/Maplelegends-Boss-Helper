#ifndef MONSTER_H
#define MONSTER_H

class Monster
{
public:
    Monster();

    int numCC;

    //Name, spawn time, spawn maps, link, listMapsshowOnScreen
    QVector<std::tuple <QString, QList<int>, QStringList, QString, bool> > monsterList;
};

#endif // MONSTER_H
