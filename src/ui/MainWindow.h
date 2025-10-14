#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include "TaskManager.h"

// Forward declaration of the auto-generated Ui::MainWindow class.
// This class is created by Qt's UIC (User Interface Compiler) from MainWindow.ui
// and contains all the widgets and layouts designed in Qt Designer.
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// The MainWindow class controls the main UI and handles interactions
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    // Triggered when the "Refresh" button is clicked
    void onRefreshClicked();

    // Called when TaskManager emits a new product update
    void onProductUpdated(const Product& product);

private:
    Ui::MainWindow* ui;          // Pointer to the auto-generated UI from MainWindow.ui
    TaskManager* m_taskManager;  // Handles background data fetching
    QTableWidget* m_table;       // Table to display products

    // Can remove if using TaskManager
    void loadDummyProducts();
};
