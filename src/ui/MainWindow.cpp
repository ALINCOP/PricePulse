#include "MainWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout* layout = new QVBoxLayout(central);

    m_table = new QTableWidget(0, 4, this);
    QStringList headers = {"Product Name", "Store", "Price", "Last Checked"};
    m_table->setHorizontalHeaderLabels(headers);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(m_table);

    QPushButton* refreshBtn = new QPushButton("Refresh", this);
    layout->addWidget(refreshBtn);

    m_taskManager = new TaskManager(this);

    connect(refreshBtn, &QPushButton::clicked, this, &MainWindow::onRefreshClicked);
    connect(m_taskManager, &TaskManager::productUpdated, this, &MainWindow::onProductUpdated);
}

void MainWindow::onRefreshClicked()
{
    m_table->setRowCount(0); // clear table
    m_taskManager->updateProducts();
}

void MainWindow::onProductUpdated(const Product& product)
{
    int row = m_table->rowCount();
    m_table->insertRow(row);
    m_table->setItem(row, 0, new QTableWidgetItem(product.name));
    m_table->setItem(row, 1, new QTableWidgetItem(product.store));
    m_table->setItem(row, 2, new QTableWidgetItem(QString::number(product.price, 'f', 2)));
    m_table->setItem(row, 3, new QTableWidgetItem(product.lastChecked.toString()));
}
