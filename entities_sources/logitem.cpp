#include "entities_headers/logitem.h"

LogItem::LogItem(const QString &typeLog,
                 const QString &tabelNum,
                 const QString &timeOpenApp,
                 const QString &serialNumberAgv,
                 const QString &nameTO,
                 const QString &timeToAgv)
    : typeLog(typeLog),
      tabelNum(tabelNum),
      timeOpenApp(timeOpenApp),
      serialNumberAgv(serialNumberAgv),
      nameTO(nameTO),
      timeToAgv(timeToAgv) {}

QString LogItem::getTypeLog() const { return typeLog; }
QString LogItem::getTabelNum() const { return tabelNum; }
QString LogItem::getTimeOpenApp() const { return timeOpenApp; }
QString LogItem::getSerialNumberAgv() const { return serialNumberAgv; }
QString LogItem::getNameTO() const { return nameTO; }
QString LogItem::getTimeToAgv() const { return timeToAgv; }
