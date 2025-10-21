#pragma once
#include <QObject>
#include <QThreadPool>
#include <QVector>
#include <QDateTime>
#include <QRunnable>
#include <QDebug>

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

    // Emit updates for initial dummy products
    void updateProducts();

public slots:
    // Add a new product in a separate thread
    void addProduct(const Product& product);

signals:
    // Emitted when a product is added or updated
    void productUpdated(const Product& product);

private:
    QThreadPool m_pool;
    QVector<Product> m_products; // store the initial dummy products
};
