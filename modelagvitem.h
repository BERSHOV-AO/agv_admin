#ifndef MODELAGVITEM_H
#define MODELAGVITEM_H

#include <QString>

class ModelAgvItem
{
public:
    ModelAgvItem(const QString &model);
    QString getModel() const;

private:
    QString model;
};

#endif // MODELAGVITEM_H
