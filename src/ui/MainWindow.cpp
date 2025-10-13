#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Test multithreading
    QThread* workerThread = QThread::create([]{
        qDebug() << "Hello from worker thread:" << QThread::currentThread();
    });
    workerThread->start();
}

MainWindow::~MainWindow() {
    delete ui;
}
