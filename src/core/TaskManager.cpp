#include "TaskManager.h"
#include <QThread>

TaskManager::TaskManager(QObject* parent)
    : QObject(parent)
{
    m_pool.setMaxThreadCount(QThread::idealThreadCount());

    // Initialize the dummy products here
    m_products = {
        {"iPhone 15 Pro", "eMAG", 5999.99, QDateTime::currentDateTime()},
        {"Samsung Galaxy S24", "Altex", 4799.50, QDateTime::currentDateTime()},
        {"PlayStation 5", "Flanco", 2999.00, QDateTime::currentDateTime()},
        {"NVIDIA RTX 4080", "PC Garage", 7999.00, QDateTime::currentDateTime()}
    };
}

void TaskManager::updateProducts()
{
    for (const auto& prod : m_products) {
        // Each product update runs in its own thread
        m_pool.start([this, prod]() {
            QThread::sleep(1); // simulate delay
            emit productUpdated(prod);
            });
    }
}

void TaskManager::addProduct()
{
    // TO DO
}
