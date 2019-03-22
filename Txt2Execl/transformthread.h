#ifndef TRANSFORMTHREAD_H
#define TRANSFORMTHREAD_H

#include <QThread>
#include <QMutex>
#include "qexecl.h"

class TransformThread : public QThread
{
    Q_OBJECT
public:
    explicit TransformThread(QObject *parent = nullptr, QString txtFile = QString(), QString execlFile = QString());
    ~TransformThread();
    bool isRun() const
    {        
        return run_flag;
    }
signals:
    void current(int num);
    void total(int num);
protected:
    void run();
private:
    QString m_txtFile;
    QString m_execlFile;
    QExcel *execl;
    bool run_flag;
    QMutex m_mutex;
};

#endif // TRANSFORMTHREAD_H
