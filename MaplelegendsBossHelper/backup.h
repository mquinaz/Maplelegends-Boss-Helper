#ifndef BACKUP_H
#define BACKUP_H

class Backup
{
public:
    Backup(int numCC, QVector<std::tuple <QString, int, QString, bool> > &monsterList);

    QFile file;
    QString filename = "time.txt";
    QVector<QString> backupTimer;
    QVector< std::tuple<QDateTime, QDateTime, QDateTime, int, int>> backupTimerToProcess;

    void writeTimerBackup(int monsterListSize);
    void formatTimerBackup(int bossIndex, int ccIndex, QString time = "");
};

#endif // BACKUP_H
