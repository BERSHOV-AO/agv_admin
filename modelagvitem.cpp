#include "modelagvitem.h"

ModelAgvItem::ModelAgvItem(const QString &model) : model(model)
{}

QString ModelAgvItem::getModel() const { return model; }