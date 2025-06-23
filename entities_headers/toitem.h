#ifndef TOITEM_H
#define TOITEM_H

#include <QString>

class TOItem
{
public:
    TOItem(const QString &nameTo, const QString &frequencyTo, const QString &timeTo);

    QString getNameTo() const;
    QString getFrequencyTo() const;
    QString getTimeTo() const;

private:
    QString nameTo;
    QString frequencyTo;
    QString timeTo;
};

#endif // TOITEM_H
