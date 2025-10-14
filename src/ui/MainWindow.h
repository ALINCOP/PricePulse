#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include "TaskManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onProductUpdated(const Product& product);
    void onRefreshClicked();

private:
    QTableWidget* m_table;
    TaskManager* m_taskManager;
};
