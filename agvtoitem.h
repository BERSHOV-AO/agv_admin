#ifndef AGVTOITEM_H
#define AGVTOITEM_H

#include <QString>

class AGVTOItem
{
public:
    AGVTOItem(const QString &nameTo, const QString &serialNumberAGV, const QString &frequencyOfTo,
              const QString &statusTo, const QString &dataTo);

    QString getNameTo() const;
    QString getSerialNumberAGV() const;
    QString getFrequencyOfTo() const;
    QString getStatusTo() const;
    QString getDataTo() const;

private:
    QString nameTo;
    QString serialNumberAGV;
    QString frequencyOfTo;
    QString statusTo;
    QString dataTo;
};

#endif // AGVTOITEM_H
