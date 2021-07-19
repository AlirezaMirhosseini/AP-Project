#include "serverClass.h"

#include <QDebug>

serverClass::serverClass(QObject * parent) :QObject(parent)
{

}
void serverClass::setServer(){
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 1030); //1024
    qDebug() << "listening....";
    connect(server, SIGNAL(newConnection()), this, SLOT(serverNewConnection()));
}

serverClass::~serverClass()

{

}

void serverClass::serverNewConnection(){
    QTcpSocket * s = server->nextPendingConnection();
    qDebug() << "new client connection id: " << s->socketDescriptor();
    socketConnections *ss = new socketConnections(s->socketDescriptor());
        connections.push_back(ss);
}
