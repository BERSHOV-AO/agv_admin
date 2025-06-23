#include "entities_headers/toitem.h"

TOItem::TOItem(const QString &nameTo,
               const QString &frequencyTo,
               const QString &timeTo)
    : nameTo(nameTo),
      frequencyTo(frequencyTo),
      timeTo(timeTo)
{}
QString TOItem::getNameTo() const { return nameTo; }
QString TOItem::getFrequencyTo() const { return frequencyTo; }
QString TOItem::getTimeTo() const {return timeTo; }
