#include "toitem.h"

TOItem::TOItem(const QString &nameTo,
               const QString &frequencyTo)
    : nameTo(nameTo),
      frequencyTo(frequencyTo)
{}
QString TOItem::getNameTo() const { return nameTo; }
QString TOItem::getFrequencyTo() const { return frequencyTo; }

