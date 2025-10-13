#include "TaskManager.h"
#include <QDebug>

TaskManager::TaskManager(QObject* parent)
    : QObject(parent)
{
    m_threadPool = QThreadPool::globalInstance();
}

void TaskManager::runTestTask()
{
    TestTask* task = new TestTask();
    task->setAutoDelete(true);
    m_threadPool->start(task);
}
