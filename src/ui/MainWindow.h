#pragma once

#include <QMainWindow>
#include <QTableView>
#include <QSqlTableModel>
#include "PriceScraper.h"
//#include "TaskManager.h"

// Forward declaration of the auto-generated Ui::MainWindow class.
// This class is created by Qt's UIC (User Interface Compiler) from MainWindow.ui
// and contains all the widgets and layouts designed in Qt Designer.
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Forward declaration; To check if this solution is nice to have
class AddProductDialog;

// The MainWindow class controls the main UI and handles interactions
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    // Triggered when the "Refresh" button is clicked
    void onRefreshClicked();

    // Triggered when the "Add Item" button is clicked
    void onAddItemClicked();

    // Called when TaskManager emits a new product update
    //void onProductUpdated(const Product& product);

    // Triggered when the "Delete" button is clicked
    void onDeleteClicked();

    // Called when PriceScraper finishes updating product prices
    // Updates the UI and synchronizes the database
    void onProductsScraped(const QList<Product>& products);

private:
    Ui::MainWindow* ui;            // Pointer to the auto-generated UI from MainWindow.ui
    //TaskManager* m_taskManager;  // Handles background data fetching
    QTableView* m_table;           // Table to display products
    QSqlTableModel* m_model;       // Table to display products
    AddProductDialog* m_addDialog; // Dialog for adding a new product
    PriceScraper* m_scraper;       // Web scrapper to check the price

    // Can remove if using TaskManager
    void loadDummyProducts();
};
