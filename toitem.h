#ifndef TOITEM_H
#define TOITEM_H

#include <QString>

class TOItem
{
public:
    TOItem(const QString &nameTo, const QString &frequencyTo);

    QString getNameTo() const;
    QString getFrequencyTo() const;

private:
    QString nameTo;
    QString frequencyTo;
};

#endif // TOITEM_H
