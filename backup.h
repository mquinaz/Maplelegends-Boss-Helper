#ifndef BACKUP_H
#define BACKUP_H

#include <QVector>
#include <QString>
#include <QList>

/**
 * A backup file in case you close app it can restore your active timers
 * and ability to share amongst people
 *
 * the constructor creates the initial file or reads the existent one
 * into backupTimerToProcess, which is processed later in mainwindow constructor
 *
 * writeTimerBackup() either writes a new time in the .txt or removes it
 */
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
