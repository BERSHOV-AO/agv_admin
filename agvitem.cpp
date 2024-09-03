#include "agvitem.h"

AgvItem::AgvItem(const QString &name, const QString &serialNumber, const QString &versionFW,
                 const QString &model, const QString &ePlan, const QString &dataLastTo)
    : name(name), serialNumber(serialNumber), versionFW(versionFW),
      model(model), ePlan(ePlan), dataLastTo(dataLastTo) {}

QString AgvItem::getName() const { return name; }
QString AgvItem::getSerialNumber() const { return serialNumber; }
QString AgvItem::getVersionFW() const { return versionFW; }
QString AgvItem::getModel() const { return model; }
QString AgvItem::getEPlan() const { return ePlan; }
QString AgvItem::getDataLastTo() const { return dataLastTo; }


