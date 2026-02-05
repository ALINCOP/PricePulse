#include <QApplication>
#include <QDebug>
#include "MainWindow.h"
#include "DatabaseManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qDebug() << "Available SQL drivers:" << QSqlDatabase::drivers();

    if (!DatabaseManager::init()) {
        qDebug() << "Database initialization failed!";
        return -1;  // stop application -> DB cannot be open
    }
    else {
        qDebug() << "Database initialization succeeded!";
    }

    MainWindow w;
    //w.resize(600, 400);
    w.show();

    return app.exec();
}
