#ifndef MONSTER_H
#define MONSTER_H

class Monster
{
public:
    Monster();

    int numCC;

    QVector<std::tuple <QString, int, QString, bool> > monsterList;
};

#endif // MONSTER_H
