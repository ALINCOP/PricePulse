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
            store TEXT,
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
        INSERT INTO products(name, store, price, last_checked)
        VALUES (?, ?, ?, ?)
    )");

    // fill the placeholders "?"
    q.addBindValue(p.name); 
    q.addBindValue(p.store);
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

    QSqlQuery q("SELECT name, store, price, last_checked FROM products");

    while (q.next()) {
        Product p;
        p.name = q.value(0).toString();
        p.store = q.value(1).toString();
        p.price = q.value(2).toDouble();
        p.lastChecked = QDateTime::fromString(q.value(3).toString(), Qt::ISODate);
        list.push_back(p);
    }

    return list;
}
