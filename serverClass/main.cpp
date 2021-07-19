#include "serverClass.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serverClass w;
    w.setServer();
    return a.exec();
}


//#include <QtCore/QCoreApplication>
//#include "serverClass.h"
//int main(int argc, char *argv[])
//{
//	QCoreApplication a(argc, argv);
//	serverClass s;
//	s.setServer();
//	return a.exec();
//}
