#include <QFile>
#include <QVector>
#include <QString>
#include <QList>
#include <QDateTime>
#include <QTextStream>

#include "backup.h"

Backup::Backup(int numCC, QVector<std::tuple <QString, QList<int>, QStringList, QString> > &monsterList)
{
    filename = "time.txt";

    file.setFileName(filename);
    if (file.exists())
    {
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);

        int bossIndex = 0;
        while (!in.atEnd())
        {
            QString line = in.readLine();
            backupTimer.push_back(line);
            backupTimer[backupTimer.size() - 1] += "\n";

            QString lineWithoutName = line.mid( line.indexOf(':') + 1, line.indexOf('\n'));

            for(int m=0;m<std::get<2>(monsterList[bossIndex]).size();m++)
            {
                QString lineMap = lineWithoutName.left(  lineWithoutName.indexOf('|'));
                for(int c=0;c<numCC;c++)
                {
                    QString lineCC = lineMap.left( lineMap.indexOf(','));
                    lineMap = lineMap.mid(lineMap.indexOf(',') + 1, lineMap.size());

                    if(lineCC != "")
                    {

                        QDateTime boundTime = QDateTime::fromString(lineCC);
                        int timerValue = std::get<1>(monsterList[bossIndex])[0];
                        QDateTime lowerBoundTime = boundTime.addSecs(timerValue * 0.9 * 60);
                        QDateTime upperBoundTime = boundTime.addSecs(timerValue * 1.1 * 60);
                        backupTimerToProcess.push_back({boundTime, lowerBoundTime, upperBoundTime, bossIndex, c, m});
                    }
                }

                lineWithoutName = lineWithoutName.mid( lineWithoutName.indexOf('|') + 1, lineWithoutName.indexOf('\n'));
            }

            bossIndex++;
        }
    }
    else
    {
        file.open(QIODevice::ReadWrite);
        QTextStream in( &file );
        for(int i=0;i<(int) monsterList.size();i++)
        {
            QString line = std::get<0>(monsterList[i]) + ":";

            for(int m=0;m<std::get<2>(monsterList[i]).size();m++)
            {
                for(int i=0;i<numCC;i++)
                    line += ",";
                line += "|";
            }

            line += "\n";
            in << line;
            backupTimer.push_back(line);
        }
    }
    file.close();
}

void Backup::writeTimerBackup(int monsterListSize, int bossIndex, int ccIndex, int mapIndex, QString time)
{
    formatTimerBackup(bossIndex, ccIndex, mapIndex, time);

    if ( file.open(QIODevice::WriteOnly) )
    {
        QTextStream in( &file );

        for(int i=0;i<monsterListSize;i++)
        {
            in << backupTimer[i];
        }

        file.close();
    }
}

void Backup::formatTimerBackup(int bossIndex, int ccIndex, int mapIndex, QString time)
{
    QString backupString = backupTimer[bossIndex].mid( backupTimer[bossIndex].indexOf(':') + 1, backupTimer[bossIndex].indexOf('\n'));
    QString final = backupTimer[bossIndex].left( backupTimer[bossIndex].indexOf(':') + 1);

    for(int m=0;m<=mapIndex;m++)
    {
        if(m == mapIndex)
        {
            for(int i=1;i<=ccIndex;i++)
            {
                final += backupString.left( backupString.indexOf(',') + 1);
                backupString = backupString.mid(backupString.indexOf(',') + 1, backupString.size());
            }
        }
        else
        {
            final += backupString.left( backupString.indexOf('|') + 1);
            backupString = backupString.mid(backupString.indexOf('|') + 1, backupString.size());
        }

    }

    backupTimer[bossIndex] = final + time + "," + backupString.mid(backupString.indexOf(',') + 1, backupString.size());
}

