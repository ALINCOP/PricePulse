#pragma once
#include <QString>
#include <QDateTime>

struct Product {
    int id = -1;
    QString name;
    QString url;
    double price = 0.0;
    QDateTime lastChecked;
};
