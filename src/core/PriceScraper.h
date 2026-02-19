#pragma once

#include <QObject>
#include <QTimer>
#include <QWebEnginePage>
#include <QDateTime>
#include "Product.h"

class PriceScraper : public QObject
{
    Q_OBJECT

public:
    explicit PriceScraper(QObject* parent = nullptr);

    void startScraping(const QList<Product>& products, int intervalMs);
    void stopScraping();

signals:
    void productsUpdated(const QList<Product>& products);

private slots:
    void onTimeout();
    void onPageLoaded(bool ok);

private:
    void loadNext();

    QList<Product> m_products;
    int m_currentIndex = 0;

    QTimer m_timer;
    QWebEnginePage* m_page;
};
