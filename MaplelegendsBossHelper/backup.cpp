#include <QFile>
#include <QString>
#include <QDateTime>

#include "backup.h"

Backup::Backup(int numCC, QVector<std::tuple <QString, int, QString, bool> > &monsterList)
{
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

            QString lineWithoutName = line.mid( line.indexOf(':') + 1, line.indexOf('\n'));
            for(int c=0;c<numCC;c++)
            {
                QString lineCC = lineWithoutName.left( lineWithoutName.indexOf(','));
                lineWithoutName = lineWithoutName.mid(lineWithoutName.indexOf(',') + 1, lineWithoutName.size());

                if(lineCC != "")
                {
                    backupTimerToProcess.push_back({QDateTime::fromString(lineCC), bossIndex, c});
                }
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
            for(int i=0;i<numCC;i++)
                line += ",";
            line += "\n";
            in << line;
            backupTimer.push_back(line);
        }
    }
    file.close();
}

void Backup::writeTimerBackup(int monsterListSize)
{
    if ( file.open(QIODevice::WriteOnly) )
    {
        QTextStream in( &file );

        for(int i=0;i<monsterListSize;i++)
        {
            in << backupTimer[i] + "\n";
        }

        file.close();
    }
}

void Backup::formatTimerBackup(int bossIndex, int ccIndex, QString time)
{
    QString backupString = backupTimer[bossIndex].mid( backupTimer[bossIndex].indexOf(':') + 1, backupTimer[bossIndex].indexOf('\n'));
    QString final = backupTimer[bossIndex].left( backupTimer[bossIndex].indexOf(':') + 1);
    for(int i=1;i<=ccIndex;i++)
    {
        final += backupString.left( backupString.indexOf(',') + 1);
        backupString = backupString.mid(backupString.indexOf(',') + 1, backupString.size());
    }
    backupString = backupString.mid(backupString.indexOf(',') + 1, backupString.size());
    backupTimer[bossIndex] = final + time + "," + backupString;
}

