#include "agvtoitem.h"

AGVTOItem::AGVTOItem(const QString &nameTo,
                     const QString &serialNumberAGV,
                     const QString &frequencyOfTo,
                     const QString &statusTo,
                     const QString &dataTo)
    : nameTo(nameTo),
      serialNumberAGV(serialNumberAGV),
      frequencyOfTo(frequencyOfTo),
      statusTo(statusTo),
      dataTo(dataTo) {}

QString AGVTOItem::getNameTo() const { return nameTo; }
QString AGVTOItem::getSerialNumberAGV() const { return serialNumberAGV; }
QString AGVTOItem::getFrequencyOfTo() const { return frequencyOfTo; }
QString AGVTOItem::getStatusTo() const { return statusTo; }
QString AGVTOItem::getDataTo() const { return dataTo; }
