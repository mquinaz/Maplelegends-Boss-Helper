#ifndef MONSTER_H
#define MONSTER_H

#include <QList>
#include <QString>

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
