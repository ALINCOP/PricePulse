#pragma once

#include <QObject>
#include <QRunnable>
#include <QThreadPool>

class TaskManager : public QObject
{
    Q_OBJECT
public:
    explicit TaskManager(QObject* parent = nullptr);

    void runTestTask();

private:
    QThreadPool* m_threadPool;
};

//testTask
class TestTask : public QRunnable
{
public:
    void run() override {
        qDebug("Running task in thread");
    }
};
