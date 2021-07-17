#ifndef TIME_THREAD_H
#define TIME_THREAD_H

#include <QThread>

class time_thread : public QThread
{
public:
    explicit time_thread(QObject *parent = nullptr);
    void run();
signals:
    void refreshing(void);
};

#endif // TIME_THREAD_H
