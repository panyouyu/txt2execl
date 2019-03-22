#include "transformthread.h"
#include "Windows.h"
#include "qfile.h"
#include "qtextstream.h"

TransformThread::TransformThread(QObject *parent, QString txtFile, QString execlFile)
    : QThread(parent),
      m_txtFile(txtFile),
      m_execlFile(execlFile),
      run_flag(false)
{

}

TransformThread::~TransformThread()
{
    if(isRun())
    {
        m_mutex.lock();
        run_flag = false;   //�����߳�
        m_mutex.unlock();
        wait();
    }
}

void TransformThread::run()
{
    int row = 0;
    int column = 0;
    int row_count = 0;
    //Ϊ��ǰ�̳߳�ʼ��COM�Ⲣ���ò���ģʽ
    ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
    execl = new QExcel(m_execlFile,this);
    execl->selectSheet(1);
    QFile file(m_txtFile);
    if(!file.open(QIODevice::ReadOnly))
    {
        execl->deleteLater();
        return ;
    }
    //ͳ��������
    while(!file.atEnd())
    {
        file.readLine();
        row_count++;
    }
    emit total(row_count);

    file.seek(0);
    //��ʼ�߳�ѭ��
    m_mutex.lock();
    run_flag = true;
    m_mutex.unlock();

    QTextStream in(&file);
    QString line = in.readLine();
    while(!line.isNull() && isRun())
    {
        QStringList list=line.split(":");
        for(column = 0; column < list.size(); ++column)
        {
            execl->setCellString(row + 1, column + 1, list.at(column));
        }
        line = in.readLine();
        row++;
        emit current(row);
    }
    file.close();
    execl->save();
    execl->deleteLater();
    //�����߳�ѭ��
    m_mutex.lock();
    run_flag = false;
    m_mutex.unlock();
}
