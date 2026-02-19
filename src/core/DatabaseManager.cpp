#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool DatabaseManager::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("products.db");

    if (!db.open()) {
        qDebug() << "DB open failed:" << db.lastError();
        return false;
    }

    QSqlQuery q;
    q.exec(R"(
        CREATE TABLE IF NOT EXISTS products (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            url TEXT,
            price REAL,
            last_checked TEXT
        )
    )");

    return true;
}

void DatabaseManager::insertProduct(const Product& p)
{
    QSqlQuery q;
    q.prepare(R"(
        INSERT INTO products(name, url, price, last_checked)
        VALUES (?, ?, ?, ?)
    )");

    // fill the placeholders "?"
    q.addBindValue(p.name); 
    q.addBindValue(p.url);
    q.addBindValue(p.price);
    q.addBindValue(p.lastChecked.toString(Qt::ISODate));

    if (!q.exec()) {
        qDebug() << "Failed to insert product:" << p.name << "-" << q.lastError().text();
    }
    else {
        qDebug() << "Successfully added product:" << p.name;
    }
    
}

QList<Product> DatabaseManager::loadProducts()
{
    QList<Product> list;

    QSqlQuery q("SELECT id, name, url, price, last_checked FROM products");

    while (q.next()) {
        Product p;
        p.id = q.value(0).toInt();
        p.name = q.value(1).toString();
        p.url = q.value(2).toString();
        p.price = q.value(3).toDouble();
        p.lastChecked = QDateTime::fromString(q.value(4).toString(), Qt::ISODate);
        list.push_back(p);
    }

    return list;
}

bool DatabaseManager::updateProductPrice(int id, double price, const QDateTime& lastChecked)
{
    QSqlQuery q;
    q.prepare(R"(
        UPDATE products
        SET price = ?, last_checked = ?
        WHERE id = ?
    )");

    q.addBindValue(price);
    q.addBindValue(lastChecked.toString(Qt::ISODate));
    q.addBindValue(id);

    if (!q.exec()) {
        qDebug() << "Failed to update product id:" << id
            << "-" << q.lastError().text();
        return false;
    }

    return true;
}

