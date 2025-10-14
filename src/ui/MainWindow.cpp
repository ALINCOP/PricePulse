#include "MainWindow.h"
#include "ui_MainWindow.h"  // Auto-generated from MainWindow.ui
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_taskManager(new TaskManager(this))
{
    // Load UI elements from .ui file
    ui->setupUi(this);

    // Set default window size
    resize(1400, 900);

    // --- CREATE TABLE DYNAMICALLY ---
    m_table = new QTableWidget(this);
    m_table->setObjectName("productsTable"); // Needed for findChild
    m_table->setColumnCount(4);
    m_table->setHorizontalHeaderLabels({ "Product Name", "Store", "Price", "Last Checked" });
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Styling
    m_table->setStyleSheet(
        "QTableWidget { background-color: rgba(30, 41, 59, 0.6); color: #e2e8f0; border: none; } "
        "QHeaderView::section { background-color: rgba(71, 85, 105, 0.4); font-weight: bold; }"
    );

    // Add table to the scroll area layout from UI
    auto* layout = new QVBoxLayout(ui->categoriesContainer);
    layout->addWidget(m_table);

    // --- CONNECT SIGNALS ---
    connect(ui->refreshBtn, &QPushButton::clicked, this, &MainWindow::onRefreshClicked);
    connect(ui->addItemBtn, &QPushButton::clicked, this, &MainWindow::onAddItemClicked);
    connect(m_taskManager, &TaskManager::productUpdated, this, &MainWindow::onProductUpdated);

    // --- POPULATE TABLE AT START ---
    m_taskManager->updateProducts(); // Emit signals for all initial dummy products
}

MainWindow::~MainWindow() {
    delete ui;
}

// --- SLOT: Triggered when user clicks Refresh button ---
void MainWindow::onRefreshClicked() {
    qDebug() << "Refreshing product list...";

    // Clear existing rows before updating
    if (m_table) m_table->setRowCount(0);

    // Ask TaskManager to emit updates again
    m_taskManager->updateProducts();
}

void MainWindow::onAddItemClicked() {
    qDebug() << "Add product list...";

    // Ask TaskManager to emit Add Product
    m_taskManager->addProduct();
}
// --- SLOT: Receives product updates from TaskManager ---
void MainWindow::onProductUpdated(const Product& product) {
    if (!m_table) return;

    int row = m_table->rowCount();
    m_table->insertRow(row);
    m_table->setItem(row, 0, new QTableWidgetItem(product.name));
    m_table->setItem(row, 1, new QTableWidgetItem(product.store));
    m_table->setItem(row, 2, new QTableWidgetItem(QString::number(product.price, 'f', 2)));
    m_table->setItem(row, 3, new QTableWidgetItem(product.lastChecked.toString("yyyy-MM-dd hh:mm:ss")));
}
