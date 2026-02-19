#include "PriceScraper.h"
#include <QDebug>
#include <QRegularExpression>

PriceScraper::PriceScraper(QObject* parent)
    : QObject(parent),
    m_page(new QWebEnginePage(this))
{
    connect(&m_timer, &QTimer::timeout,
        this, &PriceScraper::onTimeout);

    connect(m_page, &QWebEnginePage::loadFinished,
        this, &PriceScraper::onPageLoaded);
}

void PriceScraper::startScraping(const QList<Product>& products, int intervalMs)
{
    m_products = products;

    if (m_products.isEmpty()) {
        qDebug() << "PriceScraper: No products to scrape!";
        return;
    }

    m_timer.start(intervalMs);
    onTimeout(); // start
}

void PriceScraper::stopScraping()
{
    m_timer.stop();
}

void PriceScraper::onTimeout()
{
    if (m_products.isEmpty())
        return;

    m_currentIndex = 0;
    loadNext();
}

void PriceScraper::loadNext()
{
    if (m_currentIndex >= m_products.size()) {
        emit productsUpdated(m_products);
        return;
    }

    const Product& p = m_products[m_currentIndex];

    qDebug() << "Loading:" << p.url;
    m_page->load(QUrl(p.url));
}

void PriceScraper::onPageLoaded(bool ok)
{
    if (!ok) {
        qDebug() << "Failed to load page";
        m_currentIndex++;
        loadNext();
        return;
    }

    // JS
    QString js = R"(
        (() => {
            let selectors = [
                '.product-new-price',
                '.price',
                '[class*=price]',
                '[data-testid*=price]'
            ];

            for (let sel of selectors) {
                let el = document.querySelector(sel);
                if (el && el.innerText)
                    return el.innerText;
            }

            return "";
        })();
    )";

    m_page->runJavaScript(js, [this](const QVariant& result)
        {
            QString priceText = result.toString().trimmed();
            Product& product = m_products[m_currentIndex];

            if (!priceText.isEmpty())
            {
                qDebug() << "Raw price text:" << priceText;

                priceText.remove(QRegularExpression("[^0-9,.]"));
                priceText.replace(",", ".");

                bool ok = false;
                double price = priceText.toDouble(&ok);

                if (ok) {
                    product.price = price;
                    product.lastChecked = QDateTime::currentDateTime();
                    qDebug() << "Updated:" << product.name << "Price:" << price;
                }
                else {
                    qDebug() << "Failed to parse price for:" << product.name;
                }
            }
            else
            {
                qDebug() << "Price not found for:" << product.name;
            }

            m_currentIndex++;
            loadNext();
        });
}
