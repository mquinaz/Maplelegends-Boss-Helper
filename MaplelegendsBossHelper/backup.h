#ifndef BACKUP_H
#define BACKUP_H

class Backup
{
public:
    Backup(int numCC, QVector<std::tuple <QString, QList<int>, QStringList, QString> > &monsterList);

    void writeTimerBackup(int monsterListSize, int bossIndex, int ccIndex, int mapIndex, QString time = "");

private:
    void formatTimerBackup(int bossIndex, int ccIndex, int mapIndex, QString time = "");

public:
    QVector< std::tuple<QDateTime, QDateTime, QDateTime, int, int, int>> backupTimerToProcess;

private:
    QFile file;
    QString filename;
    QVector<QString> backupTimer;

};

#endif // BACKUP_H
