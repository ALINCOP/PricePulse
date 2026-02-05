#include "TaskManager.h"
//#include <QThread>

TaskManager::TaskManager(QObject* parent)
    : QObject(parent)
{
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
        emit productUpdated(product);
    }
}

void TaskManager::addProduct(const Product& product)
{
    m_products.push_back(product); // keep in memory for now, db soon
    emit productUpdated(product); // update UI
}
