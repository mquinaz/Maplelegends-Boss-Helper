#ifndef BACKUP_H
#define BACKUP_H

class Backup
{
public:
    Backup(int numCC, QVector<std::tuple <QString, QList<int>, QStringList, QString, bool> > &monsterList);

    QFile file;
    QString filename;
    QVector<QString> backupTimer;
    QVector< std::tuple<QDateTime, QDateTime, QDateTime, int, int>> backupTimerToProcess;

    void writeTimerBackup(int monsterListSize);
    void formatTimerBackup(int bossIndex, int ccIndex, int mapIndex, QString time = "");
};

#endif // BACKUP_H
