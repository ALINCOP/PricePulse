#pragma once
#include <QObject>
#include <QThreadPool>
#include <QVector>
#include <QDateTime>

struct Product {
    QString name;
    QString store;
    double price;
    QDateTime lastChecked;
};

class TaskManager : public QObject {
    Q_OBJECT
public:
    explicit TaskManager(QObject* parent = nullptr);

    void updateProducts();
    void addProduct();

signals:
    void productUpdated(const Product& product);

private:
    QThreadPool m_pool;
    QVector<Product> m_products; // store the initial dummy products
};
