#pragma once
#include <QString>
#include <QDateTime>

struct Product {
    QString name;
    QString store;
    double price = 0.0;
    QDateTime lastChecked;
};
