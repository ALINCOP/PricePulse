#pragma once
#include <QSqlDatabase>
#include "Product.h"

class DatabaseManager {
public:
    static bool init();
    static void insertProduct(const Product& p);
    static QList<Product> loadProducts();
};
