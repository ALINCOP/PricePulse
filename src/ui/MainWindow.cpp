#include "MainWindow.h"
#include "ui_MainWindow.h"  // Auto-generated from MainWindow.ui
#include "AddProductDialog.h"
#include "DatabaseManager.h"

#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_addDialog(new AddProductDialog(this))
{
    // Load UI elements from .ui file
    ui->setupUi(this);

    // Set default window size
    resize(1400, 900);

    // --- CREATE SQL MODEL ---
    m_model = new QSqlTableModel(this);
    m_model->setTable("products");
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->select();

    // Rename headers
    m_model->setHeaderData(1, Qt::Horizontal, "Product Name");
    m_model->setHeaderData(2, Qt::Horizontal, "Store URL");
    m_model->setHeaderData(3, Qt::Horizontal, "Price");
    m_model->setHeaderData(4, Qt::Horizontal, "Last Checked");

    // --- CREATE TABLE VIEW ---
    m_table = new QTableView(this);
    m_table->setModel(m_model);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Hide ID column
    m_table->hideColumn(0);

    // Styling
    m_table->setStyleSheet(
        "QTableView { background-color: rgba(30, 41, 59, 0.6); color: #e2e8f0; border: none; } "
        "QHeaderView::section { background-color: rgba(71, 85, 105, 0.4); font-weight: bold; }"
    );

    auto* layout = new QVBoxLayout(ui->categoriesContainer);
    layout->addWidget(m_table);

    // --- CONNECT SIGNALS ---
    connect(ui->refreshBtn,    &QPushButton::clicked, this, &MainWindow::onRefreshClicked);
    connect(ui->addItemBtn,    &QPushButton::clicked, this, &MainWindow::onAddItemClicked);
    connect(ui->deleteItemBtn, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    //connect(m_taskManager, &TaskManager::productUpdated, this, &MainWindow::onProductUpdated);

    // --- CONNECT AddProductDialog ---
    connect(m_addDialog, &AddProductDialog::productSubmitted,
        this, [this](const Product& p) {
            DatabaseManager::insertProduct(p);
            m_model->select(); // refresh automat
        });

    // PriceScraper to check price from the given URL
    m_scraper = new PriceScraper(this);

    // Connect semnalul la un slot pentru update UI și DB
    connect(m_scraper, &PriceScraper::productsUpdated,
        this, &MainWindow::onProductsScraped);

    QList<Product> products = DatabaseManager::loadProducts();
    // Start scraping each 60000 ms - 1minute
    m_scraper->startScraping(products, 60000);
}


MainWindow::~MainWindow() {
    delete ui;
}

// --- SLOT: Triggered when user clicks Refresh button ---
void MainWindow::onRefreshClicked() {
    qDebug() << "Refreshing product list...";

    //QList<Product> products = DatabaseManager::loadProducts();
    //m_scraper->startScraping(products, 30000);

    m_model->select();  // reload din SQLite
}

void MainWindow::onAddItemClicked() {
    // Just show the pre-created dialog
    m_addDialog->show();
    m_addDialog->raise();     // Bring dialog to front
    m_addDialog->activateWindow(); // Give it focus
}

void MainWindow::onDeleteClicked()
{
    auto rows = m_table->selectionModel()->selectedRows();

    for (const QModelIndex& index : rows) {
        m_model->removeRow(index.row());
    }

    m_model->submitAll();   // DELETE
}

void MainWindow::onProductsScraped(const QList<Product>& products)
{
    for (const auto& p : products)
    {
        DatabaseManager::updateProductPrice(
            p.id,
            p.price,
            p.lastChecked
        );
    }

    m_model->select();
}
