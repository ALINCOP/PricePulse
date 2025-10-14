#include "TaskManager.h"
#include <QDebug>

TaskManager::TaskManager(QObject* parent)
    : QObject(parent)
{
    m_pool.setMaxThreadCount(QThread::idealThreadCount());
}

void TaskManager::updateProducts()
{
    QVector<Product> dummyProducts = {
        {"Laptop XYZ", "Store A", 999.99, QDateTime::currentDateTime()},
        {"Smartphone ABC", "Store B", 499.50, QDateTime::currentDateTime()},
        {"Headphones 123", "Store C", 79.99, QDateTime::currentDateTime()}
    };

    for (const auto& prod : dummyProducts) {
        // Each product update runs in its own QRunnable
        m_pool.start([this, prod]() {
            QThread::sleep(1); // simulate delay
            emit productUpdated(prod);
        });
    }
}
