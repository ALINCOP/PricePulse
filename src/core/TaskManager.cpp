#include "TaskManager.h"
#include "DatabaseManager.h"
//#include <QThread>

TaskManager::TaskManager(QObject* parent)
    : QObject(parent)
{
    m_products = DatabaseManager::loadProducts();
    for (const auto& product : m_products) {
        emit productUpdated(product);
    }
}

void TaskManager::updateProducts()
{
    // load products from db
    m_products = DatabaseManager::loadProducts();
    for (const auto& product : m_products) {
        emit productUpdated(product);
    }
}

void TaskManager::addProduct(const Product& product)
{
    m_products.push_back(product);

    // insert data into database
    DatabaseManager::insertProduct(product);

    emit productUpdated(product); // update UI
}
