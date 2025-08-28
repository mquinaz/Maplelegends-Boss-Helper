#ifndef MONSTER_H
#define MONSTER_H

class Monster
{
public:
    Monster();

public:
    //Name, spawn time, spawn maps, link
    QVector<std::tuple <QString, QList<int>, QStringList, QString> > monsterList;
    int numCC;
};

#endif // MONSTER_H
