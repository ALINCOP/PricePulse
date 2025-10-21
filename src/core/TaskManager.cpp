#include "TaskManager.h"
#include <QThread>

TaskManager::TaskManager(QObject* parent)
    : QObject(parent)
{
    m_pool.setMaxThreadCount(QThread::idealThreadCount());

    // Initialize dummy products
    m_products = {
        {"iPhone 15 Pro", "eMAG", 5999.99, QDateTime::currentDateTime()},
        {"Samsung Galaxy S24", "Altex", 4799.50, QDateTime::currentDateTime()},
        {"PlayStation 5", "Flanco", 2999.00, QDateTime::currentDateTime()},
        {"NVIDIA RTX 4080", "PC Garage", 7999.00, QDateTime::currentDateTime()}
    };
}

void TaskManager::updateProducts()
{
    for (const auto& product : m_products) {
        // Run each update in a separate thread
        m_pool.start([this, product]() {
            QThread::sleep(1); // simulate delay
            emit productUpdated(product); // Notify UI
            });
    }
}

void TaskManager::addProduct(const Product& product)
{
    m_pool.start([this, product]() {
        QThread::sleep(1); // simulate some processing
        emit productUpdated(product); // Notify UI
        });
}
