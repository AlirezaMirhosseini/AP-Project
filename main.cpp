#include "login.h"
#include <QApplication>
#include "time_thread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    w.show();

    time_thread time;
    time.start();

    a.exec();
    return 0;
}
