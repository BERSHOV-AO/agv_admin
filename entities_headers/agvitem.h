#ifndef AGVITEM_H
#define AGVITEM_H

#include <QString>

class AgvItem
{
public:
    AgvItem(const QString &name, const QString &serialNumber, const QString &versionFW,
            const QString &model, const QString &ePlan, const QString &dataLastTo);

    QString getName() const;
    QString getSerialNumber() const;
    QString getVersionFW() const;
    QString getModel() const;
    QString getEPlan() const;
    QString getDataLastTo() const;
    QString getStatusReadyTo() const;
    void setStatusReadyTo(QString statusTO);

private:
    QString name;
    QString serialNumber;
    QString versionFW;
    QString model;
    QString ePlan;
    QString dataLastTo;
    QString statusReadyTo;
};

#endif // AGVITEM_H
