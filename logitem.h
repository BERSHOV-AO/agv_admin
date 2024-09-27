#ifndef LOGITEM_H
#define LOGITEM_H

#include <QString>


class LogItem
{
public:
    LogItem(const QString &typeLog, const QString &tabelNum, const QString &timeOpenApp,
            const QString &serialNumberAgv, const QString &nameTO, const QString &timeToAgv);


    QString getTypeLog() const;
    QString getTabelNum() const;
    QString getTimeOpenApp() const;
    QString getSerialNumberAgv() const;
    QString getNameTO() const;
    QString getTimeToAgv() const;

private:
    QString typeLog;
    QString tabelNum;
    QString timeOpenApp;
    QString serialNumberAgv;
    QString nameTO;
    QString timeToAgv;
};

#endif // LOGITEM_H
