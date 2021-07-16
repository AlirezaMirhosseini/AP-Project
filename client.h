#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets/QWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
class client : public QWidget
{
    Q_OBJECT

public:
    client(QWidget *parent = 0 , int = 0);
    ~client();

private:
    QTcpSocket *socket;
    int id;
public slots:
    //for socket signals
    void	connected();
    void	disconnected();
    void	bytesWritten(qint64 bytes);
    void	readyRead();

};
#endif // CLIENT_H
